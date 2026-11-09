# 语义检查（Semantic）实现教程

> 本文档面向下一阶段：语义检查。

## 0. 现状盘点

### 测试契约

- `config.mk`：`SEMANTIC = ./target/build/rx {source}`，**退出 0 = 接受，退出 1 = 拒绝**。
- `scripts/test.py` 读取 `tests/official/semantic/<主题>/manifest.json`，按每条用例的
  `compilation_success`（true/false）判定你的退出码是否正确。
- 共 44 个主题目录、236 个用例。**所有用例都以 `use rx::core::*;` 开头**，并会使用
  内建设施：`println_i32(x)`、`Box::<i32>::new(x)`、`*box`、`arr.len()` 等。

### AST 层的缺口与对策

1. **`useDeclaration` 被 `CrateNode` 跳过**（AST 里根本没有 use 节点）。
   对策：语义阶段自己维护一张**内建符号表（prelude）**，启动时把 `println_i32`、
   `Box`、`Vec` 等按名字预注册进去；源文件里的 `use rx::core::*;` 继续忽略即可。
2. **路径泛型被丢弃**：`Box::<i32>::new(5)` 在 AST 里是 `PathExprNode{segments=["Box","new"]}`。
   对策：内建类型按名字特判（看到 `Box::new` 就知道返回 `Box<T>`，T 取实参类型）。

### AST 的隐式契约（语义层必读）

- `BinaryExprNode`：**单子也包层**。`1 + 2` 的 `1` 外面套着约 10 层 BinaryExpr/CastExpr/
  UnaryExpr/AssignExpr。恒定满足 `op.size() == operands.size() - 1`；`op` 为空且只有一个
  operand 时表示"直通"，递归 unwrap 即可。
- `AssignExprNode`：`op` 为空字符串 = 不是赋值（只有左值）；`op` 非空且 `right != nullptr`
  才是赋值。
- 家族形状不一致：普通家族的块表达式会包一层 `ExprStmtNode`，而 condition 家族是裸的
  `BlockExprNode`/`IfExprNode`/...。写表达式遍历时建议先统一剥壳（见第 5 节）。
- `()`（空括号）在 AST 里是 `nullptr`，所有表达式遍历入口先判空。
- 负数字面量以 `uint64_t` 回绕存储（`-5` → 2⁶⁴-5），符号信息只剩 `suffix` 之外的文本
  已丢失；常量检查需要做值域判断时注意。
- AST 全部 `new` 出来、靠析构链释放；语义阶段**只读**，不要改树。

## 1. Visitor 模式到底怎么用

### 不要用 ANTLR 生成的 Visitor

`src/ParserVisitor.h` 里的 `ParserVisitor` 是给 **CST**（`rx::Parser::XxxContext`，
ANTLR 语法树）用的。你的语义检查对象是**自己手写的 AST**（`ASTNode` 及其派生类），
两者完全无关。在 CST 上跑 visitor 等于把 AST 阶段的工作推倒重来，不要走这条路。

### 推荐做法：kind switch 分发

你的每个 AST 节点都带 `const ASTNodeType kind`，这就是天然的分发标签。在
`SemanticCheck` 类里写一个总入口 `visit(ASTNode*)`，按 kind switch 到各个
`visitXxx`，效果和经典 Visitor 一模一样，但不需要动 30 多个 AST 类：

```cpp
// Semantic.h
#pragma once
#include "AST.h"
#include <string>
#include <unordered_map>
#include <vector>

class SemanticCheck {
public:
    // 入口：检查整个 crate，发现错误返回 false
    bool run(CrateNode* crate);

private:
    // ---- 总分发 ----
    void visit(ASTNode* node);            // 按 kind switch
    // ---- items ----
    void visitFnItem(FnItemNode* node);
    void visitStructItem(StructItemNode* node);
    void visitConstItem(ConstItemNode* node);
    void visitImplItem(ImplItemNode* node);
    // ---- statements ----
    void visitLetStmt(LetStmtNode* node);
    void visitBlock(BlockExprNode* node);
    // ---- expressions（每个返回表达式的类型，见第 2 节 TypeInfo）----
    // TypeInfo visitExpr(ASTNode* node); ...
};
```

```cpp
// Semantic.cpp
void SemanticCheck::visit(ASTNode* node) {
    if (node == nullptr) return;          // () 空括号是 nullptr
    switch (node->kind) {
        case FnItem:    visitFnItem(static_cast<FnItemNode*>(node)); break;
        case StructItem: visitStructItem(static_cast<StructItemNode*>(node)); break;
        case ConstItem: visitConstItem(static_cast<ConstItemNode*>(node)); break;
        case ImplItem:  visitImplItem(static_cast<ImplItemNode*>(node)); break;
        case LetStmt:   visitLetStmt(static_cast<LetStmtNode*>(node)); break;
        case BlockExpr: visitBlock(static_cast<BlockExprNode*>(node)); break;
        // ... 每个枚举值一行
        default: break;
    }
}
```

要点：

- `node->kind` 是基类字段，`static_cast` 下行转换是安全的（kind 与类一一对应）。
- 表达式类节点的 visit 需要**返回类型**（`TypeInfo`），语句/声明类返回 void 即可。
  所以实践中你会写两套：`visitStmt(ASTNode*)` 和 `TypeInfo visitExpr(ASTNode*)`，
  各自内部再 switch。
- 经典 Visitor（给 ASTNode 加 `virtual void accept(...)`）也能做，但要改所有节点类，
  收益只是少写一个 switch，不推荐。

## 2. 总体架构：两遍扫描

Rust 允许前向引用（函数可以调用后面定义的函数），所以必须先把所有声明收集完，
再检查函数体。

```
run(crate):
    Pass 1: 遍历 crate.items
        - fn     → 全局函数表：名字 → (参数类型列表, 返回类型)
        - struct → 全局结构体表：名字 → (字段名 → 类型, derives)
        - const  → 全局常量表：名字 → (类型, 值)
        - impl   → 把方法挂到对应结构体名下：类型名 → (方法名 → 签名)
        - 同时注册内建 prelude（println_i32 / Box / Vec / ...）
        - 本 pass 就检查"重复定义"
    Pass 2: 再次遍历 crate.items，逐个进入函数体/常量初始化式
        - 带作用域栈做名称解析 + 类型检查 + 可变性/控制流检查
```

### 需要新增的基础设施

```cpp
// 类型表示（最小可用版）
struct TypeInfo {
    enum Kind { I32, Bool, Unit, Struct, Array, Ref, Never, Unknown } kind = Unknown;
    std::string name;                 // Struct 时填结构体名
    TypeInfo* elem = nullptr;         // Array 的元素 / Ref 的指向
    uint64_t len = 0;                 // Array 的长度
    bool is_mut = false;              // Ref 是否可变
    // Unknown 是"出错后的占位"，与任何类型相等，避免级联报错
};
bool typeEquals(const TypeInfo& a, const TypeInfo& b);

// 符号表项
struct Symbol {
    TypeInfo type;
    bool mut = false;
    bool is_const = false;            // const 常量不可赋值、可做常量求值
};

// 作用域栈：vector 当栈用，lookup 从尾往头找 → 天然支持 shadowing
std::vector<std::unordered_map<std::string, Symbol>> scopes;
void enterScope() { scopes.emplace_back(); }
void exitScope()  { scopes.pop_back(); }
// declare：往 scopes.back() 插入；若已存在 → "重复定义" 错误
// lookup：从 scopes.rbegin() 往 rend() 逐层找；找不到再查全局表 → "未声明" 错误
```

类型从 AST 类型节点转换：`PathTypeNode{segments=["i32"]}` → `TypeInfo{I32}`，
`ArrayTypeNode` → `TypeInfo{Array, elem, len}`，以此类推。写一个
`TypeInfo resolveType(ASTNode* typeNode)` 统一转换。

## 3. 检查清单（按测试主题分组）

每组给出要查的规则和对应的测试目录。建议按此顺序实现——前面的主题依赖最少。

### 3.1 入口与名字 — `entry` / `names-and-shadowing` / `protected-names` / `namespace-errors`

- `main` 必须存在、无参数、无显式返回类型（或返回 Unit）。
- 同一作用域重复定义同名 fn/struct/const/let → 拒绝。
- 使用未声明的变量/函数 → 拒绝。
- 内层 `let` 遮蔽外层同名变量是**允许**的（shadowing），但类型可以不同。
- `self`/`Self`/内建名被当普通标识符占用 → 拒绝。

### 3.2 类型与字面量 — `casts-and-literals` / `integer-arithmetic` / `shifts` / `expected-types`

- 算术/比较/位运算两侧必须是 `i32`（比较运算结果是 `Bool`）。
- 逻辑运算 `&&`/`||`/`!` 两侧必须是 `Bool`。
- `as` cast：只允许数值↔数值（i32 之间的宽度变化）。`IntLitNode.suffix` 非空时
  检查后缀合法性。
- 移位 `<<`/`>>`：左右都是 i32。

### 3.3 数组 — `arrays` / `nested-containers` / `vec-operations` / `vec-index-mutability`

- `ArrayExprNode`：所有元素类型一致；声明了 `[T; N]` 时个数必须等于 N
  （rej 例：`let a: [i32; 2] = [1, 2, 3];`）。
- `ArrayRepeatNode`（`[x; N]`）：N > 1 时 x 的类型必须是 Copy（i32/bool/数组的 Copy
  组合）；N 来自常量求值。
- `IndexExprNode`：受体必须是数组，`index` 必须是 i32（rej 例：i32 不能索引数组、
  整数不能被索引——注意方向：受体不是数组就报错）。
- 对不可变数组的元素赋值 → 拒绝。

### 3.4 结构体 — `structs-and-fields` / `aggregate-arguments-and-reference-fields` / `recursive-layout`

- `StructExprNode`：结构体已定义；字段名都存在；字段类型匹配；不能多/少字段。
- `FieldExprNode`：受体是结构体且字段存在。
- **递归布局**：结构体直接/间接包含自己而中间没有 `Box`（或数组长度 0 之外的间接层）
  → 拒绝（无限大小）。
- 需要先补 AST：给 `StructItemNode` 加 `derives`（见第 0 节）。

### 3.5 引用与可变性 — `references-and-mutability` / `scalar-reference-operators` / `reference-coercions` / `reference-lub` / `lifetimes-and-use`

- `&x`：x 是左值 → `Ref{x, false}`；`&mut x`：x 必须是**可变**左值 → `Ref{x, true}`。
- `*r`：r 是引用 → 解引用得到内层类型；`*r = v` 需要 r 是 `&mut`。
- 赋值左值检查（`AssignExprNode.op` 非空时）：left 必须是 PathExpr/FieldExpr/IndexExpr/
  UnaryExpr(`*`) 之一，且整条链路上没有不可变约束（rej 例：不可变数组元素赋值）。
- `&&T` 现在是两层 `RefTypeNode`，注意类型相等的递归比较。

### 3.6 控制流 — `loops-and-jumps` / `blocks-if-and-never` / `unreachable-checks` / `loop-state-merges`

- `break`/`continue` 只能出现在循环内（维护循环深度计数器）。
- `loop { break v; }`：loop 表达式的类型 = 所有 `break` 值类型的汇合；`while` 的
  break 值只能是 `()`。
- `return v`：v 的类型必须匹配函数声明的返回类型；无返回类型的函数只能 `return;`。
- 块尾表达式（`BlockExprNode.return_expression`）的类型 = 块的类型；无块尾则块是 Unit。
- **never 类型**：`break`/`continue`/`return`/无限 `loop` 之后的语句不可达
  （`unreachable-checks` 主题）；发散表达式的类型记为 `Never`，它与任何类型兼容。

### 3.7 常量 — `constants-and-paths` / `constant-errors`

- const 的初始化式必须是常量表达式（字面量、其他常量、负号——正好对应
  `CheckConstValue` 覆盖的语法子集）。
- const 不可被赋值、不可取 `&mut`。
- 数组长度里的常量路径要能做常量求值（维护 const 名字 → 值的表）。

### 3.8 函数与方法 — `calls-recursion-and-abi` / `methods-and-self` / `source-main-calls` / `trait-dispatch-and-reference-equality`

- `CallExprNode`：callee 是已声明函数；实参个数/类型匹配。
- `MethodCallExprNode`：receiver 类型 → 找到对应结构体的 impl 方法；`self`/`&self`/
  `&mut self` 与 receiver 的可变性匹配。
- 递归调用合法（Pass 1 已收集签名，天然支持）。

### 3.9 内建 — `builtin-io` / `box-and-moves`

预注册即可，按名字特判：

| 名字 | 签名 | 备注 |
|---|---|---|
| `println_i32` | `(i32) -> Unit` | |
| `Box::new` | `(T) -> Box<T>` | 泛型被 AST 丢弃，按名字特判 |
| `*box` | `Box<T> -> T` | 解引用特判 |
| `arr.len()` | `() -> i32` | 方法名 `len` 特判（注意真实语义是 usize，本课程按 i32） |

## 4. 落地步骤

1. **`Semantic.h` / `Semantic.cpp`**：实现 `SemanticCheck`——TypeInfo/Symbol/作用域栈 +
   visit 骨架。先只做 Pass 1 + main 存在性检查。
2. **`main.cpp`**：AST 构建之后、返回之前接入：
   ```cpp
   CrateNode* ASTtree = new CrateNode(Crate, tree);
   SemanticCheck sema;
   bool ok = sema.run(ASTtree);
   delete ASTtree;
   return ok ? 0 : 1;
   ```
   语法错误仍然在前面 `getNumberOfSyntaxErrors() > 0` 处拦截，语义阶段看到的树一定是
   完整的，不需要防御性格式检查。
3. **先绿后红**：先让一个主题的 acc 用例通过，再逐步点亮 rej 用例。推荐推进顺序：
   `entry` → `names-and-shadowing` → `constants-and-paths` → `integer-arithmetic` →
   `arrays` → `structs-and-fields` → 控制流 → 引用 → 其余。
4. **跑测试**：
   ```bash
   # 全量
   python3 scripts/test.py
   # 按主题过滤（FILTER 语法：目录名用冒号连接）
   python3 scripts/test.py semantic:arrays
   ```
   每个用例的结果与 manifest 的 `compilation_success` 对照。

## 5. 常见坑（FAQ）

**Q：表达式外面套了太多层，怎么拿到底层节点？**
写 unwrap 辅助函数，利用 `op` 为空的直通契约：

```cpp
// 剥掉 AssignExpr/BinaryExpr/CastExpr/UnaryExpr 的"直通"层
ASTNode* unwrap(ASTNode* node) {
    while (node != nullptr) {
        if (node->kind == AssignExpr) {
            auto* n = static_cast<AssignExprNode*>(node);
            if (n->op.empty() && n->right == nullptr) { node = n->left; continue; }
        }
        if (node->kind == BinaryExpr) {
            auto* n = static_cast<BinaryExprNode*>(node);
            if (n->op.empty() && n->operands.size() == 1) { node = n->operands[0]; continue; }
        }
        if (node->kind == CastExpr) {
            auto* n = static_cast<CastExprNode*>(node);
            if (n->types.empty()) { node = n->expr; continue; }
        }
        if (node->kind == UnaryExpr) {
            auto* n = static_cast<UnaryExprNode*>(node);
            if (n->op.empty()) { node = n->expr; continue; }
        }
        break;
    }
    return node;
}
```

**Q：`op` 为空的 `AssignExprNode` 是不是赋值？**
不是。`op.empty() && right == nullptr` 表示纯表达式直通。

**Q：块表达式一会儿包 `ExprStmtNode` 一会儿是裸的，怎么统一？**
入口处剥壳：

```cpp
ASTNode* peel(ASTNode* node) {
    if (node != nullptr && node->kind == ExprStmt)
        return static_cast<ExprStmtNode*>(node)->expr;
    return node;
}
```

**Q：遍历表达式遇到 `nullptr`？**
那是 `()` 空括号。所有表达式入口先 `if (node == nullptr) return TypeInfo{Unit};`
（或按上下文处理）。

**Q：负数常量怎么判断？**
`IntLitNode.value` 是回绕后的 `uint64_t`。语义上如果课程只要求 i32 常量，
检查 `value` 落在 `[0, 2^31]` 或 `[2^64 - 2^31, 2^64)` 即对应正/负范围。

**Q：语义阶段能不能顺手改 AST（比如标注类型）？**
不建议。只读遍历，错误信息收进 `std::vector<std::string> errors`，
最后 `errors.empty()` 决定退出码。需要标注信息就放 `SemanticCheck` 自己的
`unordered_map<ASTNode*, TypeInfo>` 里。
