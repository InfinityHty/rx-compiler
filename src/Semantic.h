#pragma once
#include "AST.h"
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
    std::vector<std::string> builtin_names = {"i32","u32","isize","usize", "bool", "Box", "self", "Self",
        "Vec", "Copy", "Clone", "PartialEq", "Eq","get_i32", "print_i32", "println_i32"};
    enum Derived {Copy,Clone,PartialEq,Eq,Other}; // 支持的Trait
    struct TypeInfo{
        enum Kind{I32,U32,Usize,Isize,Bool,Box,Vec,Unit,Struct,Array,Ref,Never,Unknown};
        Kind kind = Unknown;
        std::string name; // Struct名
        TypeInfo* element = nullptr; // Array元素/Ref拆掉&后的内容
        uint64_t length; // Array长度
        bool is_mut = false; // Ref类是不是可变引用 &mut i32 
    };
    // Tools
    bool IsTypeEqual(const TypeInfo& a,const TypeInfo& b);
    TypeInfo* GetTypeInfo(ASTNode* node);
    TypeInfo* GetSelfTypeInfo(ASTNode* node,std::string struct_name);
    bool IsBuiltIn(std::string name);
    Derived StringToDerived(std::string);
    struct Symbol{
        TypeInfo* type;
        bool is_const = false; // 是不是const
        bool mut = false; // 是否可变
    };
    struct FunctionInfo{
        std::vector<Symbol*> params; // 参数类型
        TypeInfo* return_type = nullptr; // 返回类型
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
        std::any value; // 这里应该怎么存const的值？
    };
    std::unordered_map<std::string,ConstantInfo*> constants_table; // 全局常量表

    std::vector<std::unordered_map<std::string,Symbol>> scopes; // 作用域
    bool error = false;
    // dispatch
    void Visit(ASTNode* node);
    // branch
    void VisitCrate(CrateNode* node);
    void VisitFnItem(FnItemNode* node);
    void VisitStructItem(StructItemNode* node);
    void VisitConstItem(ConstItemNode* node);
    void VisitImplItem(ImplItemNode* node);
};
