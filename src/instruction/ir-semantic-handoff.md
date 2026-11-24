# SemanticCheck 如何向 IR 交付结果

本文针对当前仓库的 `AST.h`、`Semantic.h/.cpp`、`IR.h/.cpp` 和 `main.cpp`。这里是**设计方案**，不是已经实现的接口。目标是让 IR 阶段只负责按已确认的语义生成指令，不再重新做名字查找、类型推导和方法选择。

## 1. 先确定交接边界

建议流程：

```text
源文件 → AST → SemanticCheck → SemanticResult → IRBuilder → IR
                         │                 ▲
                         └── 仍读取同一棵 AST ──┘
```

`SemanticResult` 是**一次编译的只读快照**。它保存 IR 必需的结论；AST 保存语法结构；IRBuilder 自己维护基本块、临时值、栈槽和布局信息。检查失败时不调用 IRBuilder。

当前 `SemanticCheck` 的 `functions_table`、`structs_table`、`constants_table` 和 `scopes` 都是私有的内部工作状态；`call_path`、`current_impl_type`、`cycles_stack` 等只是遍历过程中的临时变量。不要把整个 `SemanticCheck&` 当作长期的 IR 接口。目前已改成 `BuildIR(CrateNode*, SemanticResult&)`，但结果表还需填充，IR 构造仍是空实现。

## 2. 应该保存哪些结果

按“IR 是否需要重新推断”来选。建议最小集合如下：

| 结果 | 存储位置 | IR 用途 |
| --- | --- | --- |
| 每个表达式的**最终类型**，包括 `Unit`、`Never`、数组长度、引用可变性、`Box/Vec` 元素类型 | `exprs[ASTNode*]` | 决定值类型、指令及分支合流类型 |
| 每个 `let`、函数参数的唯一 `SymbolId`、类型和可变性 | `bindings`、`declarations[ASTNode*]` | 分配存储、处理同名遮蔽 |
| 每个值路径的解析目标：局部变量、参数、全局常量、函数、关联常量等 | 可选的 `paths[PathExprNode*]`，或 IR 自己维护作用域 | 确定实际要读取/调用的对象；类型本身不包含对象身份 |
| 每个调用的确定目标、完整函数签名、实参到形参的调整 | `calls[ASTNode*]` | 生成普通调用、内建函数或内建容器操作；处理 `self` |
| 每个投影的基类型、目标成员/下标类型及自动解引用步骤 | `projections[ASTNode*]` | 计算字段地址、数组/Vec 元素地址 |
| 每处隐式转换的**具体步骤**及目标类型 | `adjustments[ASTNode*]` 或放在使用边上 | 生成重借用、引用弱化、解引用、整数定型等；避免 IR 猜测 |
| 全局函数/方法签名、结构体**按声明顺序**排列的字段、全局常量的已解析值 | `functions`、`structs`、`constants` | 发射函数、调用、结构体布局和常量 |

这里的“最终类型”必须能指导 IR：无后缀整数字面量当前可能仍是 `TypeInfo::Default`，但落到一个要求 `u32` 的参数或 `i32` 的局部变量时，IR 需要知道这次使用的目标类型。建议记录**表达式本身的推导类型**和**使用位置的目标类型/调整**，不要把一个共享节点的类型记录覆盖成调用方类型。`Never` 表示控制流终止，不是实际可装入寄存器的值。

### 建议暂时不保存

- `scopes`、`top_params`、`layer`、`in_scope`：检查过程中的查找状态，用 `SymbolId` 和路径解析结果替代。
- `call_path`：当前只是 `VisitPathExpr` 与 `VisitCallExpr` 之间的临时通信；把最终 `FunctionId` 或内建操作种类记录在**调用节点**上。
- `PlaceInfo` 的全部检查细节、`CanCopy/CanClone` 的中间判断：合法性由语义阶段保证；IR 只需要最终的地址计算步骤及确实影响发射的 Copy/Clone/Move 策略。
- `TypeInfo::int_val/bool_val` 作为通用类型字段：字面量值和类型是不同概念。常量值另存；运行期表达式不能被误当成编译期常量。
- IR 的 `IRType`、栈槽编号、SSA 值编号和字段字节偏移：这些属于 IR/布局阶段，不应写回语义结果。

## 3. 推荐的数据形状

下面是**示意接口**，需要按现有代码逐步落地；字段名可调整。重点是保存稳定的 ID 和语义结论，而不是保存指向 `SemanticCheck` 私有对象的裸指针。

```cpp
using SymbolId   = uint32_t;
using FunctionId = uint32_t;
using StructId   = uint32_t;
using ConstId    = uint32_t;

// 从 SemanticCheck::TypeInfo 拆出公开、可独立持有的类型描述。
// 可用递归 value/共享的不可变类型对象表示 element；不要浅拷贝
// 当前 TypeInfo::element 裸指针并依赖 checker 的寿命。
struct ResolvedType { /* kind, struct_id, element, length, is_mut */ };

struct BindingInfo {
    SymbolId id;
    ResolvedType type;
    bool is_mut;
};

struct ResolvedPath {
    enum class Kind { Local, Parameter, GlobalConst, Function,
                      AssociatedConst, AssociatedFunction, TypeName, Builtin };
    Kind kind;
    uint32_t target_id; // 按 kind 解释；内建项可另配 enum
};

struct Adjustment {
    enum class Kind { IntegerDefault, DerefRef, DerefBox,
                      BorrowShared, BorrowMut, Reborrow, MutToShared };
    Kind kind;
    ResolvedType output_type;
};

struct ExprInfo {
    ResolvedType type;
    // 可选：Value / Place / Diverges；只有确实影响 lowering 时才加。
};

struct SemanticResult {
    std::unordered_map<const ASTNode*, ExprInfo> exprs;
    std::unordered_map<const ASTNode*, SymbolId> declarations;
    std::unordered_map<const PathExprNode*, ResolvedPath> paths;
    std::unordered_map<const ASTNode*, ResolvedCall> calls;
    std::unordered_map<const ASTNode*, ProjectionInfo> projections;
    // 调整发生在“使用边”上：例如 (call node, arg index) 或 let 的初始化边。
    std::unordered_map<UseSite, std::vector<Adjustment>> adjustments;
    std::unordered_map<SymbolId, BindingInfo> bindings;
    std::unordered_map<FunctionId, FunctionSignature> functions;
    std::unordered_map<StructId, StructDefinition> structs;
    std::unordered_map<ConstId, ConstantValue> constants;
};
```

`ResolvedCall` 至少应包含：确定的目标函数/内建操作、返回类型、按顺序排列的参数类型、是否存在隐式 `self`、接收者的自动解引用/借用方案。`ProjectionInfo` 对字段应包含所属结构体及字段序号，对下标应包含容器类型和元素类型。结构体字段必须依 AST 声明顺序保存：当前 `StructInfo::fields` 是 `unordered_map`，不能用它的遍历顺序决定内存布局。

如果先做小版本，可从 `exprs + declarations + IR 自己的作用域查找 + 全局定义` 开始；`paths` 是省去 IR 重复查找的可选索引。实现字段、索引、隐式借用时再添加 `projections/adjustments`。但遇到需要调整的表达式时，**先补语义记录，再写 IR lowering**。

## 4. 当前代码中必须先处理的两个坑

### 节点身份与重复遍历

当前 `SemanticResult` 已用 `ASTNode*` 作表键，`ASTNode` 不再带 `node_id`。这适合当前进程内的交接：`AnalyzePlace()` 即使重复调用 `VisitAndGetType()`，同一个节点的地址仍不变。`ImplItem` 中的方法直接调用 `VisitFnItem()` 也不会影响节点键。

继续用节点指针作键即可，前提是 AST 在 IR 生成结束前保持存活。接口成熟后可将键改为 `const ASTNode*` 以表达只读；只有需要序列化结果或跨进程传递时，才考虑统一分配节点 ID。

重复检查同一节点时，写入 `ExprInfo` 应检查与已有结果是否一致；若类型会受上下文影响，应该把该差异记录在使用边的 `Adjustment`，不能让“最后一次访问”覆盖先前结论。尤其不要为了缓存直接跳过 visitor：当前 visitor 除返回类型外还会修改 `error`、`call_path` 等状态。

### AST 的生存期

`main.cpp` 目前在 `// IR` 之前 `delete ASTtree`。若 `SemanticResult` 用节点指针作键，且 IRBuilder 还要遍历 AST，必须改为：

```cpp
auto ast = std::unique_ptr<CrateNode>(new CrateNode(Crate, tree));
SemanticResult result;
SemanticCheck checker;
if (checker.hasSemanticError(ast.get(), result)) return 1;

IRBuilder ir;
ir.BuildIR(ast.get(), result); // 当前接口：AST + 语义结果
ir.PrintIR();
// ast 与 result 在 BuildIR 返回后再析构
```

这里沿用现有的 `hasSemanticError(CrateNode*, SemanticResult&)` 和 `BuildIR(CrateNode*, SemanticResult&)` 接口，只改变 AST 的持有方式。之后可逐步给 IR 参数加 `const`，表达 IR 不修改 AST 和语义结果。

## 5. 逐个节点在哪里记录

| 现有处理位置 | 检查结束后应能查询到什么 |
| --- | --- |
| `VisitLetStmt`、函数参数预扫描 | 给每次定义分配新 `SymbolId`；保存最终变量/参数类型；遮蔽不复用 ID |
| `VisitPathExpr` | 保存究竟绑定到哪个局部/参数/常量/函数/类型；`Self` 解析为确定结构体 |
| `VisitAndGetType` 的统一出口 | 保存表达式类型。当前 switch 直接 `return`，可先取局部结果、统一记录后返回 |
| `VisitCallExpr`、`VisitMethodCallExpr` | 保存调用目标、内建操作、`self` 传递方式、每个实参调整 |
| `VisitFieldExpr`、`VisitIndexExpr` | 保存接收者自动解引用步骤、字段序号或元素类型 |
| `VisitAssignExpr`、`VisitUnaryExpr`、`VisitLetStmt` | 保存赋值/取引用的 place 方案，以及右值或初始化的转换 |
| `VisitArrayType`、常量预扫描 | 保存已确定的数组长度、常量值；保留字面量值与类型的区别 |
| `VisitBlockExpr`、`VisitIfExpr`、`VisitLoopExpr` | 保存最终 `Unit/Never/值类型`；`break` 有值的循环须有统一结果类型 |

遇到 `BinaryExprNode` 等语法包装层，保持每个实际 AST 节点都有类型记录；IR 可对单子包装层直接透传。逻辑 `&&` / `||` 必须在 IR 中生成短路控制流，不能因为两个操作数都是 `bool` 就直接计算两侧。`Never` 分支不向合流块提供普通值。

## 6. 两个具体例子

**遮蔽：**

```rust
let x: i32 = 1;
let x: i32 = x + 1;
print_i32(x);
```

两个 `let` 分别得到 `SymbolId 1` 和 `SymbolId 2`。第二个初始化表达式里的 `x` 指向 1；最后调用里的 `x` 指向 2。可以在语义阶段保存每个 `PathExpr` 的目标 ID；也可以让 IRBuilder 自己维护作用域栈，在遍历到路径时查出对应绑定。第二个绑定要在其初始化式求值之后才进入当前作用域，符合现有 `VisitLetStmt` 的顺序。无论选哪种，`expressions_table[x] == i32` 都不能单独决定要读取哪个绑定。

**字段自动解引用：** `p.field` 若 `p` 类型是 `&Box<S>`，且 `S` 有字段 `field`，语义结果应写明 `p` 的解析目标、`DerefRef → DerefBox` 两步、最终的 `StructId` 和字段序号。IRBuilder 据此逐步求地址，结构体布局阶段再把字段序号换成字节偏移。只存“整个表达式类型为 i32”不足以生成正确地址。

## 7. 推荐落地顺序与验收

1. 新建独立 `SemanticResult` 与公开的 `ResolvedType`；确定类型对象所有权，避免结果中保存悬空的 `TypeInfo*`、`Symbol*`、`FunctionInfo*`。
2. 先记录全局函数/结构体/常量定义和 `let`/参数的 `SymbolId`，再记录路径解析、表达式类型和调用目标。对重复访问的节点加一致性检查。
3. 修改 `main.cpp` 的 AST 生存期，确保 AST 与结果活到 IR 构造完成；语义检查失败时没有部分结果被 IR 使用。
4. 从“字面量 → let → 路径读取 → 算术 → print_i32 → return”做第一条端到端路径，再接入分支/循环、字段/下标、引用、方法、Box/Vec。
5. 用包含**同名遮蔽**、**方法自动借用/解引用**、**不同分支类型与 Never**、**短路副作用**的实际代码生成用例验收：IR 能准确找到每个路径的目标，调用目标确定，运行结果符合预期。

实现时还要区分“语义检查通过”与“IR 支持该特性”。当前 `IR.h` 只列出少量算术、内存和跳转指令，调用、聚合类型、字段访问、Vec/Box 等还需要继续设计；结果交接完成本身不会自动补齐这些 IR 能力。

## 8. 对当前 `SemanticResult` 草稿的直接改法

现在的 `SemanticResult` 已有 `expressions_table`、`bindings_table`、`functions_table` 和 `symbol_id_counter`，可以沿着这个设计继续，不必先重写整个语义检查器。当前实际只有 `VisitLetStmt` 向 `bindings_table` 写入；另外两张表尚未写入。建议按以下顺序补：

1. **给 `Symbol` 加 `symbol_id`，并记录参数。** 预扫描函数/方法参数时分配 ID，把 `FnParamNode*`、`FnSelfParamNode*` 映射到 `BindingInfo`；`VisitLetStmt` 创建 `Symbol` 时也分配同一个 ID 并写入 `bindings_table`。如果选择保存 `paths_table`，`VisitPathExpr` 找到 `Symbol*` 后还要能取得对应 ID。`symbol_id_counter` 最简单的语义是“一次编译中唯一”：删除 `VisitCrate` 对它的重置，方法和普通函数都从同一计数器取号。
2. **路径目标有两种交付方式，选一种即可。** A：增加 `paths_table[PathExprNode*]`，语义检查时记录 `Local/Parameter/Const/Function` 等目标，IR 直接查表。B：不加表，IRBuilder 按 AST 的块结构维护自己的作用域栈，在每个 `let` 的初始化式之后才放入新绑定，遍历 `PathExpr` 时按名字查当前栈，并单独处理全局项。B 更省结果字段，但需要在 IR 中实现一次名字查找。`expressions_table` 只能回答类型，不能回答同名遮蔽后的目标绑定。
3. **在 `VisitAndGetType` 统一保存类型。** 当前 switch 每个分支直接返回；可以把现有 switch 移到 `VisitAndGetTypeImpl`，由薄包装 `VisitAndGetType` 调用它、记录 `expressions_table[node]`，再返回。也可把各分支改成赋局部 `type`，在函数末尾统一写入。表的注释应改为“表达式/类型节点的解析类型”，因为键是实际 AST 节点，不限 `ExprStmtNode`。重复访问同一节点时允许重复检查，但应校验记录类型一致；不要靠缓存跳过 visitor 的副作用。
4. **在调用节点记目标。** 增加 `calls_table[CallExprNode*/MethodCallExprNode*]`，记录最终函数或内建操作、返回类型、参数类型、`self` 的传入方式。`call_path` 只是当前 visitor 的临时状态，必须在 `VisitCallExpr`/`VisitMethodCallExpr` 确认目标时转成结果。`functions_table` 可保存所有函数签名，方法用 `结构体名::方法名` 或稳定 ID 区分。
5. **补全结构体/常量和隐式调整。** 结构体保存按 AST 声明顺序的字段；常量保存已解析的值；自动解引用、借用、类型定型等保存在使用位置或调用/投影记录中。IR 需要的是确定的操作序列，不能仅凭 `CanCoerce(...) == true` 复原它。

一个最小字段增量可以长这样（类型仅示意）：

```cpp
struct PathResolution {
    enum class Kind { Local, Parameter, GlobalConst, AssociatedConst,
                      Function, AssociatedFunction, StructType, Builtin } kind;
    uint32_t symbol_id = 0;       // Local / Parameter 时有效
    std::string qualified_name;   // 全局项时有效，例如 "S::f"
};

// 添加到 SemanticResult：
std::unordered_map<PathExprNode*, PathResolution> paths_table;
std::unordered_map<ASTNode*, ResolvedCall> calls_table;
```

`BindingInfo` 目前按值存 `SemanticCheck::TypeInfo`，但 `TypeInfo::element` 是裸指针；`functions_table` 若按值复制 `FunctionInfo`，其参数和返回类型也仍指向 checker 内部对象。这是**浅拷贝**，不构成独立快照。先跑通简单 `i32/bool` IR 可以暂时共用 checker 的生存期；开始支持 `Ref/Array/Box/Vec` 时应做递归深拷贝，或改为有明确所有权的公开类型表示，并让函数签名也使用它。`friend SemanticResult` 只解决访问权限，不解决指针所有权。

最后先修正 `main.cpp`：现在 `delete ASTtree` 在 `ir.BuildIR(ASTtree, result)` **之前**，传入的是悬空指针。把删除移到 `BuildIR` 之后，最好直接用 `std::unique_ptr<CrateNode>` 管理 AST。`SemanticResult` 以节点指针作键时，AST 必须在整个 IR 构造过程保持存活。
