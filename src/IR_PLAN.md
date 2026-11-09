# Rx 编译器 IR / Codegen 实施计划

## Context：当前进度与最终目标

当前流水线是：

```text
.rx 源码
  → ANTLR Lexer / Parser
  → CST
  → 手写 AST
  → SemanticCheck
  → 退出码 0 / 1
```

入口在 `src/main.cpp:16-38`。语义检查目前只返回 `bool`，类型、符号和调用信息都留在 `SemanticCheck` 的私有临时状态中（`src/Semantic.h:13-108`），所以还不能直接开始遍历 AST 输出 IR。

本阶段最终要得到：

```text
.rx 源码
  → AST + 完整语义标注
  → LLVM 文本 IR（.ll / .ir）
  → clang 18 的 RV32IM 后端
  → RV32IM 汇编（.s）
  → REIMU 执行
  → stdout 与官方 expected output 逐字节一致
```

这里的“IR 部分”不是单独写一个 IR 打印器就结束，而是打通完整可执行链路。最终验收目标是：

1. 原有 236 个 official semantic 测试继续全部通过。
2. 58 个 official codegen 测试全部编译、运行并输出正确结果。
3. 13 个 official optimization 测试先做到正确执行；性能优化放到正确性完成之后。
4. `make test FILTER=official:codegen` 和 `make test FILTER=official:optimization` 能通过统一测试入口，而不是依赖手工命令。

## 推荐方案：直接生成 LLVM 文本 IR，不写自有后端

采用：

```text
AST + SemanticResult → IRGenerator → LLVM textual IR → clang → RV32IM
```

理由：

- `config.mk.ref:14-16` 已给出 LLVM IR 转 RV32IM 的参考命令。
- 环境中的 clang 18 已确认支持 `riscv32`。
- 不必现在实现 RV32 指令选择、寄存器分配、调用约定和汇编打印。
- 不需要引入 LLVM C++ API；先用字符串流生成 LLVM IR，更容易学习和调试。
- 第一版不设计复杂的自有 SSA IR，不做优化，不手写 phi 优化；通过局部变量内存和结果槽降低控制流难度。

暂不做：寄存器分配、指令选择、通用优化框架、复杂 SSA 构造器。这些会显著增加工作量，却不是打通 codegen 的前提。

## 先建立最少的 IR 概念

LLVM IR 中需要掌握的概念只有：

- **类型**：如 `i32`、`i8`、`ptr`、数组类型、结构体类型。
- **值**：常量、函数参数、指令产生的临时结果，如 `%t0`。
- **指令**：`add`、`icmp`、`load`、`store`、`call` 等。
- **基本块**：一段顺序执行的指令，末尾必须是 `br` 或 `ret` 等 terminator。
- **栈存储**：`alloca` 创建本地存储，`load/store` 读写。第一版变量都用它，避免立即处理完整 SSA。
- **函数与控制流**：`if/while/loop` 被拆成多个基本块，不再保留 AST 的树形结构。

例如 `a + b` 的核心 IR 只是：

```llvm
%t0 = add i32 %a, %b
```

而 `if` 需要条件分支、then/else 块和汇合块。第一版可用一个临时 `alloca` 保存分支结果，从而暂时避免手动构造 `phi`。

## Key changes：分阶段实施

### 阶段 0：固定调试闭环与测试基线

1. 保留当前 `rx <source>` 的语义检查行为。
2. 增加独立的 IR 输出模式，例如 `rx --emit-ir <source> -o <file>`，方便只检查 IR。
3. 最终由 `config.mk` 串联：生成 `{output}.ir`、调用 clang 生成 `{output}`、运行 `scripts/strip_asm_debug.py`。
4. 每完成一个阶段都重新跑 `make test FILTER=official:semantic`，确保 236 个测试不回归。
5. 在 `tests/custom` 增加最小用例，每个用例只验证一个特性；复杂官方案例失败时先缩小到最小复现。

**完成标准**：能手工生成一个最小 `.ll`，经 clang 变为 `.s`，再由 REIMU 执行并打印结果；此后每次新增 AST lowering 都走同一闭环。

### 阶段 1：把语义分析结果保存下来（最重要的前置工作）

建议新增公共的 `SemanticResult` / 语义信息接口，并调整 `src/Semantic.h`、`src/Semantic.cpp`。不要在 IRGenerator 中重新按名字猜类型或重新做名称解析。

至少保存以下信息，map 可以暂以 `ASTNode*` 为键，AST 必须存活到 IR 生成结束：

1. **表达式最终类型**
   - `typeOf(ASTNode*)`。
   - 整数字面量的 `Default` 必须在这里根据上下文落成 `i32/u32/isize/usize`，不能留到 IR 猜测。
   - 记录 `Never`、单位类型及隐式强制转换后的目标类型。
2. **唯一的变量绑定**
   - 每个 `PathExprNode` 指向具体的局部变量、参数、常量或函数符号，而不是只保存变量名。
   - 每个 `LetStmtNode` 和参数有稳定 Symbol ID。
   - 这样 shadowing 后旧引用仍指向旧存储，符合 `names-and-shadowing` 测试。
3. **函数、方法和常量解析结果**
   - 每个 `CallExprNode` / `MethodCallExprNode` 的唯一调用目标。
   - 函数签名、参数顺序、返回类型、所属结构体、receiver 类型。
   - 全局常量与关联常量的最终常量值。
4. **隐式调整**
   - 自动解引用、自动借用、`&mut T → &T` 等。
   - 尤其要处理方法 receiver 和 clone 的特殊查找顺序。
5. **结构体与派生信息**
   - 字段声明顺序、字段类型、字段编号。
   - `Clone/Copy/PartialEq/Eq` 能力，供后续生成深拷贝和结构相等逻辑。

实现时尽量在现有 `VisitAndGetType`、`VisitPathExpr`、`VisitCallExpr`、`VisitMethodCallExpr`、`VisitLetStmt` 已作出决定的位置记录结果，避免第二套语义规则。

另需修正一个已确认的接入障碍：`src/Semantic.cpp:458-479` 当前没有遍历 `impl` 方法体，`VisitFnItem` 又只从全局函数表取签名（`src/Semantic.cpp:481-496`）。应让函数体检查接收显式的当前函数/方法签名，并覆盖普通函数和方法。

`src/Types.h` 是未使用且与当前语义类型不一致的另一套类型，不要直接拿它做 IR 基础。可将现有 `TypeInfo` 整理为可安全保存的公共值类型，或提供深拷贝/稳定所有权，避免导出悬空的内部裸指针。

**完成标准**：对任意已接受程序，IR 生成器可以查询每个表达式的最终类型、每个名字的唯一绑定和每个调用的目标；全部 semantic 测试仍通过。

### 阶段 2：实现类型映射、内存布局和 LLVM 模块骨架

建议新增 `src/IR.h`、`src/IR.cpp`；若布局逻辑较大，再拆 `Layout.h/.cpp`。现有 CMake 只自动收集 `src/*.cpp`（`CMakeLists.txt:7-13`），根目录新文件无需修改 glob，子目录则需要调整。

定义统一的 Rx → LLVM 映射：

- `i32/u32/isize/usize`：RV32 上均为 `i32`，signedness 由指令决定。
- `bool`：建议统一用 `i8` 存储和传参；比较结果是 `i1` 时再 `zext` 为 `i8`，分支前转为 `i1`。
- 引用、`Box<T>`：`ptr`。
- `[T; N]`：LLVM 数组，按元素布局计算大小。
- 用户结构体：按 AST 中字段声明顺序生成 LLVM struct；不要依赖 `unordered_map` 的迭代顺序。
- `Vec<T>`：统一运行时布局 `{ ptr data, i32 len, i32 cap }`。
- `()`：无返回值函数用 `void`；需要物化单位值时使用零大小表示。
- `Never`：不生成正常值，表达式之后当前控制流必须已经终止或不可达。

实现 `sizeOf/alignOf` 和字段偏移查询，并用 `bool` 邻近字段、嵌套数组、递归 Box 等例子检查布局。模块打印器负责：类型声明、全局字符串、函数声明/定义、基本块标签、临时寄存器编号和 terminator 状态。

**完成标准**：最小 `main` 能生成合法 LLVM IR、汇编并返回；所有生成函数都有合法基本块结尾，clang 不再报 IR 语法或 terminator 错误。

### 阶段 3：先打通标量、函数和控制流

实现两个核心入口：

```text
emitExpr(node, expectedType) → 值
emitPlace(node)              → 地址
```

先让 `emitExpr` 支持标量，`emitPlace` 后续扩展。所有局部变量第一版都使用独立 `alloca`；函数入口把参数保存到各自本地存储中。无操作的 `BinaryExpr/CastExpr/UnaryExpr/AssignExpr` 包装层要统一剥离，可参考 `src/Semantic.cpp:1801-1836`。

按以下顺序实现：

1. 整数/布尔字面量、路径读取、`let`、赋值、单位表达式。
2. 一元和二元运算，按 `BinaryExprNode::{operands,op,level}` 保持左结合。
3. signed/unsigned 运算差异：`sdiv/udiv`、`srem/urem`、`ashr/lshr`、有符号/无符号比较。
4. shift 数量按语言规则掩码为低 5 位；整数类型间 cast 保持 32 位，bool cast 做显式扩展。
5. `&&` / `||` 必须用控制流实现短路，不能先计算两边再 `and/or`。
6. block 尾值、`if/else` 表达式、提前 `return`、`Never` 与不可达代码。
7. `while`、带值的 `loop`、`break value`、`continue`；维护循环上下文栈，记录 break 块、continue 块和 loop 结果槽。
8. 普通赋值遵守官方测试要求的右操作数先求值；复合赋值确保目标 place 只计算一次。
9. 普通函数、递归、参数和返回值；全局/关联常量直接使用语义阶段求出的常量值。
10. 内建 I/O：声明 REIMU 提供的 `printf/scanf`，生成 `"%d"`、`"%d\n"` 格式串，实现 `get_i32/print_i32/println_i32`。
11. 入口包装：Rx 的 `main` 改名为如 `@rx_main`，额外生成全局 `i32 @main()`，调用 `@rx_main` 后返回 0。这样源码递归调用 `main` 时仍调用 Rx 函数，而不会错误调用包装器。

每个函数生成时维护“当前块是否已终止”，不要在 `ret/br` 后继续向同一块追加普通指令。

**建议验收顺序**：`builtin-io` → `casts-and-literals` → `integer-arithmetic` → `shifts` → `boolean-and-short-circuit` → `blocks-if-and-never` → `loops-and-jumps` → `names-and-shadowing` → `constants-and-paths` → `calls-recursion-and-abi` → `live-state-calls` → `source-main-calls`。

**完成标准**：纯标量程序、递归、短路、复杂控制流均在 REIMU 中输出正确结果。

### 阶段 4：实现 place、数组、结构体、引用和方法

这一阶段的核心不是更多运算，而是正确区分“值”和“地址”。

1. `emitPlace` 支持变量、解引用、字段和索引。
2. 数组索引使用元素布局计算地址；嵌套 place 逐层计算，不临时复制整个外层对象。
3. 结构体字面量按字段声明位置写入；字段访问使用语义结果中的字段编号。
4. 数组和结构体作为值传递/返回时物化到存储；通过 `llvm.memcpy` 或逐字段复制完成 by-value 语义。
5. `Copy` 聚合赋值产生独立存储；非 Copy 的 owner 移动可以转移内部指针，但运行时不能因源对象残留而重复释放。
6. `[expr; N]` 只求值一次；`N > 1` 时按 Copy 规则复制，`N == 1` 时支持非 Copy 值。
7. `&`、`&mut`、`*`、自动解引用和自动借用严格使用阶段 1 保存的语义调整。
8. 实现关联函数和 `self/&self/&mut self` 方法，receiver 在调用约定中作为第一个参数。
9. 聚合临时值要有足够长的存储生命周期，尤其覆盖 if 分支结果、函数返回聚合和“临时对象上的引用/字段访问”。

**建议验收顺序**：`arrays` → `structs-and-fields` → `aggregate-arguments-and-reference-fields` → `references-and-mutability` → `reference-coercions` → `scalar-reference-operators` → `compound-assignment` → `methods-and-self` → `runtime-value-merges` → `loop-state-merges`。

**完成标准**：聚合参数/返回、整个数组赋值、嵌套字段索引、引用字段和复杂 place 都正确，且 Copy 对象之间不共享可写存储。

### 阶段 5：实现 Box、Vec、Clone 与结构相等

不要把这些内建功能留到最后，因为它们涉及 IR 的值表示和运行时布局。

1. **Box**
   - `Box::new` 调用 REIMU libc 的 `malloc`，按元素大小分配并写入值。
   - 解引用返回堆对象地址。
   - `clone` 是深拷贝，不能只复制指针。
2. **Vec**
   - 采用 `{data,len,cap}` 布局。
   - 实现 `new/len/is_empty/push/remove/index/clone`。
   - 扩容可生成通用运行时 IR：按元素字节大小分配新存储、复制旧字节、更新 data/len/cap。
   - `remove` 先移出目标元素，再移动后续字节并更新 len。
   - 下标语义与 place 规则一致，不能为读取而复制整个 Vec。
3. **derive Clone / Copy**
   - Copy 只做值存储复制。
   - Clone 递归处理数组、结构体、Box、Vec；owner 容器必须得到独立存储。
4. **PartialEq / Eq**
   - 标量直接比较，聚合逐元素/字段比较，忽略 padding。
   - Box/Vec 比较内容，不比较堆地址。
   - 递归类型通过生成具体类型的辅助函数处理，避免无限内联展开。

可让 IRGenerator 按需发出 `rx_box_*`、`rx_vec_*`、`rx_clone_Type`、`rx_eq_Type` 等内部函数，并做名称去重。第一版优先保证所有权不双重释放和结果正确，暂不做复杂析构优化。

**建议验收顺序**：`box-and-moves` → `vec-operations` → `vec-index-mutability` → `nested-containers` → `copy-clone-and-equality` → `trait-dispatch-and-reference-equality` → `recursive-traits` → `recursive-layout`。

**完成标准**：堆对象深拷贝、Vec 扩容/删除、嵌套容器、递归 Clone 和结构相等全部通过对应运行时测试。

### 阶段 6：全量收敛，再做优化

1. 跑完整 `official:codegen`，按特性分组修复，不直接在综合题上盲调。
2. 综合测试最后处理：`comprehensive-quicksort`、`comprehensive-stack-machine`、`comprehensive-owned-tree`、`comprehensive-shortest-path`、`comprehensive-large-frame`。
3. 跑完整 `official:optimization`，先要求所有输入输出正确并记录 cycle report。
4. 正确性稳定后再考虑优化：clang 后端优化、常量折叠、减少多余 load/store、mem2reg/SSA、简单死代码消除。
5. 每次优化都同时跑 semantic、codegen、optimization，比较输出与 cycles，避免为性能破坏语义。

## Verification：每层的统一检查

构建：

```sh
cmake -S . -B target/build -DCMAKE_BUILD_TYPE=Release
cmake --build target/build -j
```

回归与分组测试：

```sh
make test FILTER=official:semantic
make test FILTER=official:codegen:builtin-io
make test FILTER=official:codegen:arrays
make test FILTER=official:codegen
make test FILTER=official:optimization
```

每个失败用例依次检查：

1. `SemanticResult` 中的最终类型/绑定/调用目标是否正确。
2. 生成的 LLVM IR 是否能被 clang 接受。
3. 标量值与 place 地址是否混淆。
4. 基本块 terminator、分支汇合和 loop 结果是否正确。
5. 类型大小、字段偏移、数组步长和 Vec 布局是否一致。
6. 汇编能否被 REIMU 执行，stdout 是否逐字节相同。

不要只看“编译成功”或“IR 能打印”；每个阶段都必须以真实 REIMU 运行结果为验收依据。

## 最终交付物

- 一个可查询的 `SemanticResult`，IR 不再重复语义分析。
- `IRGenerator`、类型/布局规则和 LLVM IR 打印能力。
- 标量、控制流、函数/方法、数组/结构体/引用、Box/Vec、derive 的完整 lowering。
- I/O、堆分配和入口包装等最小运行时支持。
- 接好的 `--emit-ir` / `config.mk` / clang / REIMU 测试链路。
- 236 个 semantic、58 个 codegen 全通过，13 个 optimization 至少 correctness 全通过；之后再以 cycle report 做性能改进。

## Assumptions

- 采用仓库参考配置推荐的外部 clang，不引入 LLVM C++ API，也不手写 RV32 后端。
- 以当前 AST 实际能表示的 Rx 子集为准，不为 IR 阶段额外扩展完整 G4 文法。
- 保持现有单参数语义检查接口和官方测试文件不变。
- 第一版优先简单、可调试和正确，不以 SSA 美观或 cycles 为首要目标。
