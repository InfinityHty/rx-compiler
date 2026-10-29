#pragma once
#include "AST.h"
// #include "Types.h"
#include<vector>
#include<unordered_map>
#include<string>

// 第一遍遍历AST，构建Symbol Table
class SemanticCheck{
public:
    bool hasSemanticError(CrateNode* node);
private:
    struct TypeInfo;
    struct Symbol;
    struct ConstantInfo;
    struct FunctionInfo;
    // 保留的关键字
    // Type和Value是两个不同的namespace
    std::vector<std::string> builtin_types = {"i32","u32","isize","usize", "bool", "Box", "Vec", "Copy", "Clone", "PartialEq", "Eq"};
    std::vector<std::string> builtin_values = {"get_i32", "print_i32", "println_i32"};
    enum Derived {Copy,Clone,PartialEq,Eq,Other}; // 支持的Trait

    struct TypeInfo{
        // Default限定为int
        enum Kind{I32,U32,Usize,Isize,Default,Bool,Box,Vec,Unit,Struct,Array,Ref,Never,Unknown};
        Kind kind = Unknown;
        std::string name; // Struct名
        TypeInfo* element = nullptr; // Array元素/Ref拆掉&后的内容/Vec包裹的内容/Box包裹的内容
        long long length = 0; // Array长度
        bool is_mut = false; // Ref类是不是可变引用 &mut i32 
        long long int_val = 0;
        bool bool_val = false;
        TypeInfo();
        TypeInfo(Kind kind_){
            kind = kind_;
        }
    };

    // Tools
    bool IsTypeEqual(const TypeInfo& a,const TypeInfo& b);
    TypeInfo* GetTypeInfo(ASTNode* node);
    TypeInfo* GetSelfTypeInfo(ASTNode* node,std::string struct_name);
    // void ResolveSelfType(TypeInfo* type,const std::string& struct_name); // 把Self替换掉 不过在第2轮预检查的时候处理了相同问题，所以不需要了
    struct PlaceInfo{
        TypeInfo type;
        bool can_write = false; // 能不能改本身
        bool can_mutate_contents = false; // 能不能改内容
        bool has_pass_shared_ref = false; // 是否穿过共享引用
    };
    PlaceInfo AnalyzePlace(ASTNode* node);
    PlaceInfo DereferencePlace(const PlaceInfo& base);
    bool CanWrite(ASTNode* node); // 能否作为左值
    bool IsPlaceExpr(ASTNode* node); // 是否是指向已有存储的place表达式（而非可物化的临时值）
    bool CanCopy(TypeInfo type); // 是否具备Copy trait
    bool CanClone(TypeInfo type); // 是否具备Clone trait
    bool CanPartialEq(TypeInfo type); // 是否具备PartialEq trait
    bool CanTypeMut(TypeInfo type); // type是否可以通过0或多次解引用达到可写状态
    bool CanCoerce(TypeInfo cur,TypeInfo target); // 是否可以强制转换成目标类型
    bool IsBuiltInTypes(std::string name); // 检查是否和关键字冲突
    bool IsBuiltInValues(std::string name);
    Derived StringToDerived(std::string); // 字符串转换成Derived
    bool CheckDerivedTrait(std::set<Derived>& derived,TypeInfo*& field); // 检查struct里的field是否都满足trait
    bool CheckRecursiveField(std::set<std::string>& history,const std::string& cur_typename);
    bool CheckRecursiveConst(const std::vector<std::string>& begin,std::vector<std::string> &cur); // 检查const的路径是否合法

    struct Symbol{
        TypeInfo* type = nullptr;
        bool is_const = false; // 是不是const
        bool mut = false; // 是否可变
    };
    struct FunctionInfo{
        std::vector<std::pair<std::string,Symbol*>> params{}; // 参数 要按顺序
        TypeInfo* return_type = nullptr; // 返回类型
        bool has_generic = false;
    };
    std::unordered_map<std::string,FunctionInfo*> functions_table; // 全局函数表
    struct StructInfo{
        std::unordered_map<std::string,TypeInfo*> fields;
        std::set<Derived> derived; // 不能重复
        std::unordered_map<std::string,FunctionInfo*> methods; // 由impl语句进行挂载
        std::unordered_map<std::string,ConstantInfo*> consts; // impl挂载
    };
    std::unordered_map<std::string,StructInfo*> structs_table; // 全局结构体表
    struct ConstantInfo{
        TypeInfo* type;
        long long int_value;
        bool bool_value;
        std::vector<std::string> path_value{};
    };
    std::unordered_map<std::string,ConstantInfo*> constants_table; // 全局常量表
    // scopes and shadowing
    std::vector<std::unordered_map<std::string,Symbol*>> scopes; // 作用域
    std::unordered_map<std::string,Symbol*> top_params;
    int layer = -1;
    // loop 
    struct CycleInfo{
        bool is_loop = false;
        std::vector<TypeInfo> exit_types{};
    };
    std::vector<CycleInfo> cycles_stack; // 专门记录目前的循环嵌套情况
    bool analysize_condition = false;
    // function
    std::vector<TypeInfo> function_return_types{}; // 记录多个可能的return type
    std::vector<std::string> call_path{}; // 记录函数path
    // block
    std::vector<bool> diverge{};
    // Array
    bool in_scope = false; // 是不是scope里的变量

    bool error = false;
    // dispatch
    void Visit(ASTNode* node);
    TypeInfo VisitAndGetType(ASTNode* node);
    // branch
    void VisitCrate(CrateNode* node);
    // items
    void VisitFnItem(FnItemNode* node);
    void VisitStructItem(StructItemNode* node);
    void VisitConstItem(ConstItemNode* node);
    void VisitImplItem(ImplItemNode* node);
    // statements
    void VisitLetStmt(LetStmtNode* node);
    void VisitExprStmt(ExprStmtNode* node);
    // expressions
    TypeInfo VisitIntLit(IntLitNode* node); //
    TypeInfo VisitBoolLit(BoolLitNode* node); //
    TypeInfo VisitPathExpr(PathExprNode* node); //
    TypeInfo VisitStructExpr(StructExprNode* node); //
    TypeInfo VisitArrayExpr(ArrayExprNode* node); //
    TypeInfo VisitArrayRepeat(ArrayRepeatNode* node); //
    TypeInfo VisitUnaryExpr(UnaryExprNode* node); //
    TypeInfo VisitBinaryExpr(BinaryExprNode* node); //
    TypeInfo VisitAssignExpr(AssignExprNode* node); //
    TypeInfo VisitCastExpr(CastExprNode* node); //
    TypeInfo VisitCallExpr(CallExprNode* node);
    TypeInfo VisitMethodCallExpr(MethodCallExprNode* node);
    TypeInfo VisitFieldExpr(FieldExprNode* node); //
    TypeInfo VisitIndexExpr(IndexExprNode* node); //
    TypeInfo VisitBlockExpr(BlockExprNode* node); //
    TypeInfo VisitIfExpr(IfExprNode* node); //
    TypeInfo VisitLoopExpr(LoopExprNode* node); //
    TypeInfo VisitWhileExpr(WhileExprNode* node); // 
    TypeInfo VisitBreakExpr(BreakExprNode* node); //
    TypeInfo VisitContinueExpr(ContinueExprNode* node); //
    TypeInfo VisitReturnExpr(ReturnExprNode* node);
    // type
    TypeInfo VisitUnitType(UnitTypeNode* node);
    TypeInfo VisitPathType(PathTypeNode* node);
    TypeInfo VisitRefType(RefTypeNode* node);
    TypeInfo VisitArrayType(ArrayTypeNode* node);
};

// Crate, FnItem, StructItem, ConstItem, ImplItem, /*UseItem,*/
//     // statements
//     LetStmt, ExprStmt,
//     // expressions
//     IntLit, BoolLit, PathExpr, StructExpr, ArrayExpr, ArrayRepeat,
//     UnaryExpr, BinaryExpr, AssignExpr, CastExpr,
//     CallExpr, MethodCallExpr, FieldExpr, IndexExpr,
//     BlockExpr, IfExpr, LoopExpr, WhileExpr,
//     BreakExpr, ContinueExpr, ReturnExpr,
//     // types
//     UnitType, PathType, RefType, ArrayType,
//     // others
//     FnSelfParam,FnParam, StructField,