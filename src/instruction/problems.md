我用 `make test FILTER=official:semantic` 跑了一遍全部 official semantic 测试（共 236 个用例）：**91 通过，145 失败**。失败分两类：

- **漏检（134 个）**：`rej-` 用例本应被拒绝（exit 1），但编译器接受了（exit 0）——即还没实现的检查。
- **误拒（11 个）**：`acc-` 用例本应通过（exit 0），但编译器拒绝了（exit 1）——即现有检查过严。

完整明细如下（完整 markdown 也已存到 `/tmp/failure_table.md`）：

### aggregate-arguments-and-reference-fields (2)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-immutable-struct-field-assignment` | 漏检 | Immutable struct field assignment. |
| `rej-by-value-array-parameter-checks-its-fixed-length` | 漏检 | By-value array parameter checks its fixed length. |

### arrays (5)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-array-length-mismatch` | 漏检 | Array length mismatch. |
| `rej-an-existing-i32-cannot-index-an-array` | 漏检 | An existing i32 cannot index an array. |
| `rej-immutable-array-element-cannot-be-assigned` | 漏检 | Immutable array element cannot be assigned. |
| `rej-repeating-more-than-once-requires-copy` | 漏检 | Repeating more than once requires Copy. |
| `rej-integers-are-not-indexable` | 漏检 | Integers are not indexable. |

### blocks-if-and-never (5)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-if-without-else-requires-a-unit-consequent` | 漏检 | If without else requires a unit consequent. |
| `rej-a-non-final-block-statement-without-semicolon-must-be-unit` | 漏检 | A non-final block statement without semicolon must be unit. |
| `rej-a-semicolon-removes-the-function-tail-value` | 漏检 | A semicolon removes the function tail value. |
| `rej-bare-return-is-unit` | 漏检 | Bare return is unit. |
| `rej-a-unit-function-cannot-return-an-integer` | 漏检 | A unit function cannot return an integer. |

### boolean-and-short-circuit (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-no-integer-truthiness` | 漏检 | No integer truthiness. |
| `rej-lazy-operators-require-bool` | 漏检 | Lazy operators require bool. |
| `rej-lazy-operators-have-no-reference-variants` | 漏检 | Lazy operators have no reference variants. |
| `rej-bitwise-operand-types-must-match` | 漏检 | Bitwise operand types must match. |

### box-and-moves (5)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `acc-owned-dereference-move-valid-partial-moves-and-reinitialization-after-move` | 误拒 | Owned dereference move, valid partial moves, and reinitialization after move. |
| `rej-immutable-box-owner-gives-immutable-contents` | 漏检 | Immutable Box owner gives immutable contents. |
| `rej-shared-reference-to-box-forbids-writes` | 漏检 | Shared reference to Box forbids writes. |
| `rej-constructor-argument-must-match-t` | 漏检 | Constructor argument must match T. |
| `rej-box-constructor-needs-one-argument` | 漏检 | Box constructor needs one argument. |

### builtin-io (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-getint-has-no-arguments` | 漏检 | get_i32 has no arguments. |
| `rej-missing-builtin-argument` | 漏检 | Missing builtin argument. |
| `rej-i-o-requires-i32-with-no-implicit-integer-conversion` | 漏检 | I/O requires i32, with no implicit integer conversion. |
| `rej-unit-result-cannot-be-used-as-i32` | 漏检 | Unit result cannot be used as i32. |

### calls-recursion-and-abi (3)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-too-few-ordinary-arguments` | 漏检 | Too few ordinary arguments. |
| `rej-too-many-ordinary-arguments` | 漏检 | Too many ordinary arguments. |
| `rej-wrong-ordinary-argument-type` | 漏检 | Wrong ordinary argument type. |

### casts-and-literals (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-integer-to-bool-cast-is-unsupported` | 漏检 | Integer-to-bool cast is unsupported. |
| `rej-reference-to-integer-cast-is-unsupported` | 漏检 | Reference-to-integer cast is unsupported. |
| `rej-signed-integer-types-remain-distinct` | 漏检 | Signed integer types remain distinct. |
| `rej-unsigned-integer-types-remain-distinct` | 漏检 | Unsigned integer types remain distinct. |

### compound-assignment (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-compound-destination-must-be-mutable` | 漏检 | Compound destination must be mutable. |
| `rej-an-explicit-mismatched-suffix-cannot-coerce` | 漏检 | An explicit mismatched suffix cannot coerce. |
| `rej-reference-destinations-are-not-implicitly-dereferenced` | 漏检 | Reference destinations are not implicitly dereferenced. |
| `rej-a-literal-is-not-an-assignment-place` | 漏检 | A literal is not an assignment place. |

### constant-errors (9)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-direct-constant-dependency-cycle` | 漏检 | Direct constant dependency cycle. |
| `rej-indirect-constant-cycle` | 漏检 | Indirect constant cycle. |
| `rej-associated-constant-cycle` | 漏检 | Associated constant cycle. |
| `rej-a-constant-path-must-resolve-to-a-constant` | 漏检 | A constant path must resolve to a constant. |
| `rej-repeat-length-cannot-name-a-local` | 漏检 | Repeat length cannot name a local. |
| `rej-an-i32-constant-cannot-be-a-usize-repeat-count` | 漏检 | An i32 constant cannot be a usize repeat count. |
| `rej-array-length-must-be-usize` | 漏检 | Array length must be usize. |
| `rej-unsigned-constant-negation-is-invalid` | 漏检 | Unsigned constant negation is invalid. |
| `rej-constant-initializer-must-match-declared-type` | 漏检 | Constant initializer must match declared type. |

### constants-and-paths (2)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-constant-dependency-cycle` | 漏检 | Constant dependency cycle. |
| `rej-array-length-must-have-usize-type` | 漏检 | Array length must have usize type. |

### copy-clone-and-equality (5)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-box-fields-cannot-derive-copy` | 漏检 | Box fields cannot derive Copy. |
| `rej-mutable-references-cannot-derive-clone` | 漏检 | Mutable references cannot derive Clone. |
| `rej-same-type-equality-requires-partialeq` | 漏检 | Same-type equality requires PartialEq. |
| `rej-clone-must-be-available` | 漏检 | Clone must be available. |
| `rej-every-field-must-support-the-requested-derive` | 漏检 | Every field must support the requested derive. |

### entry (1)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-main-cannot-have-generic-parameters` | 漏检 | Main cannot have generic parameters. |

### evaluation-order-and-temporaries (3)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-ordinary-assignment-requires-a-place` | 漏检 | Ordinary assignment requires a place. |
| `rej-an-arithmetic-result-is-not-a-place` | 漏检 | An arithmetic result is not a place. |
| `acc-mutable-container-temporaries-and-extended-aggregate-borrows` | 误拒 | Mutable Vec and array temporaries evaluate once; returned array and struct storage stays live across statements. |

### expected-types (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-a-fixed-if-target-rejects-a-suffixed-incompatible-branch` | 漏检 | A fixed if target rejects a suffixed incompatible branch. |
| `rej-a-fixed-array-target-rejects-a-mismatched-element` | 漏检 | A fixed array target rejects a mismatched element. |
| `rej-a-fixed-loop-target-rejects-a-mismatched-break` | 漏检 | A fixed loop target rejects a mismatched break. |
| `rej-assignment-cannot-change-a-binding-s-type` | 漏检 | Assignment cannot change a binding's type. |

### integer-arithmetic (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-explicitly-different-arithmetic-operand-types` | 漏检 | Explicitly different arithmetic operand types. |
| `rej-unary-minus-is-signed-only` | 漏检 | Unary minus is signed-only. |
| `rej-booleans-are-not-arithmetic-integers` | 漏检 | Booleans are not arithmetic integers. |
| `rej-no-bool-to-integer-implicit-conversion` | 漏检 | No bool-to-integer implicit conversion. |

### invalid-impls-and-generics (7)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-missing-concrete-box-type-argument` | 漏检 | Missing concrete Box type argument. |
| `rej-box-requires-exactly-one-concrete-type-argument` | 漏检 | Box requires exactly one concrete type argument. |
| `rej-vec-requires-exactly-one-concrete-type-argument` | 漏检 | Vec requires exactly one concrete type argument. |
| `rej-primitives-take-no-type-arguments` | 漏检 | Primitives take no type arguments. |
| `rej-structs-have-no-type-parameters` | 漏检 | Structs have no type parameters. |
| `rej-functions-have-no-type-parameters` | 漏检 | Functions have no type parameters. |
| `rej-method-segments-have-no-type-parameters` | 漏检 | Method segments have no type parameters. |

### lifetimes-and-use (1)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-discarding-a-valid-use-does-not-suppress-a-type-error` | 漏检 | Discarding a valid use does not suppress a type error. |

### loops-and-jumps (7)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-break-outside-a-loop` | 漏检 | Break outside a loop. |
| `rej-continue-outside-a-loop` | 漏检 | Continue outside a loop. |
| `rej-a-while-cannot-accept-a-break-value` | 漏检 | A while cannot accept a break value. |
| `rej-while-body-must-be-unit` | 漏检 | While body must be unit. |
| `rej-loop-body-must-be-unit` | 漏检 | Loop body must be unit. |
| `rej-a-jump-in-a-while-condition-cannot-target-that-while` | 漏检 | A jump in a while condition cannot target that while. |
| `rej-a-condition-cannot-jump-to-an-outer-loop` | 漏检 | A condition cannot jump to an outer loop. |

### methods-and-self (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-mutable-receiver-needs-a-mutable-place` | 漏检 | Mutable receiver needs a mutable place. |
| `rej-explicit-associated-call-does-not-autoref-an-owned-argument` | 漏检 | Explicit associated call does not autoref an owned argument. |
| `rej-an-associated-function-is-not-a-dot-call-method` | 漏检 | An associated function is not a dot-call method. |
| `rej-no-matching-method` | 漏检 | No matching method. |

### names-and-shadowing (2)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-unresolved-initializer` | 漏检 | Unresolved initializer. |
| `rej-local-non-callable-shadow-prevents-function-lookup` | 漏检 | Local non-callable shadow prevents function lookup. |

### namespace-errors (6)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-unresolved-value-name` | 漏检 | Unresolved value name. |
| `rej-a-block-local-name-cannot-escape` | 漏检 | A block-local name cannot escape. |
| `rej-a-binding-is-invisible-in-its-own-initializer` | 漏检 | A binding is invisible in its own initializer. |
| `rej-a-local-shadows-a-function-without-callable-fallback` | 漏检 | A local shadows a function without callable fallback. |
| `rej-self-outside-a-method` | 漏检 | self outside a method. |
| `rej-named-field-structs-are-not-callable-constructors` | 漏检 | Named-field structs are not callable constructors. |

### nested-containers (2)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-vec-cannot-coerce-into-an-array-or-slice` | 漏检 | Vec cannot coerce into an array or slice. |
| `rej-nested-element-types-must-match` | 漏检 | Nested element types must match. |

### protected-names (1)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `acc-builtin-type-names-may-be-fields-associated-items-and-ordinary-values` | 误拒 | Builtin type names may be fields, associated items, and ordinary values. |

### recursive-layout (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-direct-infinite-inline-layout` | 漏检 | Direct infinite inline layout. |
| `rej-mutual-inline-cycle` | 漏检 | Mutual inline cycle. |
| `rej-inline-arrays-do-not-break-layout-cycles` | 漏检 | Inline arrays do not break layout cycles. |
| `rej-a-container-cannot-repair-an-invalid-declaration` | 漏检 | A container cannot repair an invalid declaration. |

### recursive-traits (1)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-a-recursive-vec-field-cannot-derive-copy` | 漏检 | A recursive Vec field cannot derive Copy. |

### reference-coercions (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-owned-box-is-not-implicitly-borrowed` | 漏检 | Owned Box is not implicitly borrowed. |
| `rej-box-does-not-coerce-to-owned-contents` | 漏检 | Box does not coerce to owned contents. |
| `rej-inner-reference-mutability-is-not-rewritten` | 漏检 | Inner reference mutability is not rewritten. |
| `rej-vec-has-no-deref-coercion` | 漏检 | Vec has no deref coercion. |

### reference-lub (1)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-with-a-fixed-target-an-incompatible-reference-is-a-required-error` | 漏检 | With a fixed target an incompatible reference is a required error. |

### references-and-mutability (6)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-a-named-immutable-local-cannot-be-mutably-borrowed` | 漏检 | A named immutable local cannot be mutably borrowed. |
| `rej-shared-dereference-is-not-mutable` | 漏检 | Shared dereference is not mutable. |
| `rej-a-shared-outer-layer-prevents-mutable-access` | 漏检 | A shared outer layer prevents mutable access. |
| `rej-rebinding-an-immutable-reference-binding-is-invalid` | 漏检 | Rebinding an immutable reference binding is invalid. |
| `rej-scalar-values-cannot-be-dereferenced` | 漏检 | Scalar values cannot be dereferenced. |
| `rej-shared-reference-cannot-become-mutable` | 漏检 | Shared reference cannot become mutable. |

### runtime-value-merges (1)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `acc-input-dependent-reference-aggregate-and-owner-results` | 误拒 | Runtime branches and value-bearing breaks merge coerced references, mutable targets, copied aggregates and owned containers. |

### scalar-reference-operators (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-arithmetic-supports-only-one-shared-reference-layer` | 漏检 | Arithmetic supports only one shared-reference layer. |
| `rej-mutable-reference-unary-arithmetic-unsupported` | 漏检 | Mutable-reference unary arithmetic unsupported. |
| `rej-ordering-cannot-coerce-a-mutable-left-operand-to-match-a-shared-right-operand` | 漏检 | Ordering cannot coerce a mutable left operand to match a shared right operand. |
| `rej-ordering-does-not-mix-a-value-and-a-reference` | 漏检 | Ordering does not mix a value and a reference. |

### shifts (2)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-shift-count-must-be-integer` | 漏检 | Shift count must be integer. |
| `rej-shift-left-operand-must-be-integer` | 漏检 | Shift left operand must be integer. |

### structs-and-fields (6)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-missing-struct-initializer-field` | 漏检 | Missing struct initializer field. |
| `rej-duplicate-initializer-field` | 漏检 | Duplicate initializer field. |
| `rej-unknown-initializer-field` | 漏检 | Unknown initializer field. |
| `rej-wrong-field-type` | 漏检 | Wrong field type. |
| `rej-unknown-accessed-field` | 漏检 | Unknown accessed field. |
| `rej-same-shaped-structs-remain-nominally-distinct` | 漏检 | Same-shaped structs remain nominally distinct. |

### trait-dispatch-and-reference-equality (2)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-container-equality-requires-element-partialeq` | 漏检 | Container equality requires element PartialEq. |
| `rej-even-empty-container-clone-requires-element-clone` | 漏检 | Even empty container clone requires element Clone. |

### unreachable-checks (4)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-unknown-name-after-return` | 漏检 | Unknown name after return. |
| `rej-wrong-type-in-an-untaken-branch` | 漏检 | Wrong type in an untaken branch. |
| `rej-unreachable-break-participates-in-loop-result-typing` | 漏检 | Unreachable break participates in loop result typing. |
| `rej-while-remains-unit-even-when-its-condition-is-true` | 漏检 | While remains unit even when its condition is true. |

### vec-index-mutability (10)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-shared-vector-reference-blocks-stored-mutable-reference` | 漏检 | A shared reference to a vector prevents mutation through its stored mutable references. |
| `rej-shared-array-reference-blocks-stored-mutable-reference` | 漏检 | The valid immutable owned-array case does not permit mutation through a shared array reference. |
| `rej-shared-box-reference-blocks-stored-mutable-reference` | 漏检 | The valid immutable owned-Box case does not permit mutation through a shared Box reference. |
| `acc-mutable-vector-supports-writes-and-mutable-borrows` | 误拒 | Mutable vectors permit assignment, compound assignment, explicit borrowing, annotated mutable-reference initializers, and &mut arguments. |
| `acc-shared-coercions-and-receivers-on-immutable-vector` | 误拒 | Shared coercions, explicit shared borrows, and shared method receivers need no mutable vector access. |
| `acc-immutable-array-struct-and-box-preserve-stored-mutable-access` | 误拒 | Immutable owned arrays, structs, and Boxes permit mutation through their stored mutable references. |
| `acc-mutable-reference-before-vector-indexing` | 误拒 | A mutable reference reached through an immutable array or Box can supply access before indexing a vector. |
| `acc-mutable-vector-supports-nested-projections` | 误拒 | Mutable vectors permit writes through nested struct fields, Boxes, arrays, and mutable vector references. |
| `acc-moved-vectors-use-new-place-mutability` | 误拒 | Moving a vector to a mutable binding or temporary gives indexing the new place's mutability. |
| `acc-copied-and-cloned-values-have-independent-mutability` | 误拒 | Mutating a separate copy or explicit clone does not require mutable access to the original vector. |

### vec-operations (6)

| 用例 | 失败类型 | 官方描述 |
|---|---|---|
| `rej-push-requires-mutable-access` | 漏检 | Push requires mutable access. |
| `rej-push-checks-element-type` | 漏检 | Push checks element type. |
| `rej-remove-index-must-be-usize` | 漏检 | Remove index must be usize. |
| `rej-vec-is-not-dereferenceable` | 漏检 | Vec is not dereferenceable. |
| `rej-vec-constructor-has-no-value-arguments` | 漏检 | Vec constructor has no value arguments. |
| `rej-shared-vec-indexing-is-immutable` | 漏检 | Shared Vec indexing is immutable. |

几点观察，可以帮你排优先级：

- **绝大多数是漏检（134/145）**，即"前半部分"尚未覆盖的检查：类型系统核心（类型匹配、unit 规则、break/return 规则、bool 与整数的区分）、mutability/借用检查、常量求值与循环依赖检测、struct 字段初始化检查、泛型参数检查、递归布局检测等。
- **误拒只有 11 个**，集中在 `vec-index-mutability`（7 个），说明你目前的 mutability 分析对"通过存储的可变引用/新 place 的 mutability"这类情况过严——实现完整的 place-based mutability 分析时应该能一并解决。
- 建议优先做的几块：`structs-and-fields` 的初始化字段检查（规则独立、容易做）、`invalid-impls-and-generics`（纯声明检查）、`constant-errors` 的循环依赖检测（图的拓扑/DFS）、以及 `loops-and-jumps` 的 break/continue 上下文检查。