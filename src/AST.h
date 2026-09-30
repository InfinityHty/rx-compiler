#pragma once

#include "Lexer.h"
#include "Parser.h"
#include <vector>

enum ASTNodeType {
     // items
    Crate, FnItem, StructItem, ConstItem, ImplItem, /*UseItem,*/
    // statements
    LetStmt, ExprStmt,
    // expressions
    IntLit, BoolLit, PathExpr, StructExpr, ArrayExpr, ArrayRepeat,
    UnaryExpr, BinaryExpr, AssignExpr, CastExpr,
    CallExpr, MethodCallExpr, FieldExpr, IndexExpr,
    BlockExpr, IfExpr, LoopExpr, WhileExpr,
    BreakExpr, ContinueExpr, ReturnExpr,
    // types
    UnitType, PathType, RefType, ArrayType,
};

// 基类
class ASTNode {
public:
    const ASTNodeType kind;
    ASTNode(const ASTNodeType kind_) : kind(kind_) {}
    virtual ~ASTNode() = 0;
};
// 全部都是派生类
class CrateNode : public ASTNode {
public:
    std::vector<ASTNode*> items; // 一个程序中的所有块
    CrateNode(const ASTNodeType kind_,rx::Parser::CrateContext* ctx);
};

class FnItemNode : public ASTNode {
public:
    ASTNode* identifier, *blockExpr, *returnType; // 函数名 函数体 返回类型
    std::vector<ASTNode*> parameters; // 函数参数
    FnItemNode(const ASTNodeType kind_,rx::Parser::FunctionDefinitionContext* ctx);

};
class StructItemNode : public ASTNode {
public:
    ASTNode* identifier;
    std::vector<ASTNode*> structField;
    StructItemNode(const ASTNodeType kind_,rx::Parser::StructDefinitionContext* ctx);
};
class ConstItemNode : public ASTNode {
public:
    ASTNode* identifier, *type, *value;
    ConstItemNode(const ASTNodeType kind_,rx::Parser::ConstantItemContext* ctx);

};
class ImplItemNode : public ASTNode {
public:
    ASTNode* type;
    std::vector<ASTNode*> items;
    ImplItemNode(const ASTNodeType kind_,rx::Parser::InherentImplContext* ctx);
};
class LetStmt : public ASTNode {
public:
    LetStmt(const ASTNodeType kind_);

};
class ExprStmt : public ASTNode {
public:
    ExprStmt(const ASTNodeType kind_);
};
class IntLit : public ASTNode {
public:
    
    IntLit(const ASTNodeType kind_);
};
class BoolLit : public ASTNode {
public:
    bool value;
    BoolLit(const ASTNodeType kind_);

};