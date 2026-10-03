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
    // others
    FnSelfParam,FnParam, StructField,
};

// 基类
class ASTNode {
public:
    const ASTNodeType kind;
    ASTNode(const ASTNodeType kind_) : kind(kind_) {}
    static ASTNode* CheckType(rx::Parser::TypeRefContext* ctx);
    static ASTNode* CheckConstValue(rx::Parser::ConstValueContext* ctx);
    virtual ~ASTNode() = 0;
};
// 派生类
// items
class CrateNode : public ASTNode {
public:
    std::vector<ASTNode*> items; // 一个程序中的所有块
    CrateNode(const ASTNodeType kind_,rx::Parser::CrateContext* ctx);
    ~CrateNode(){
        for(auto item : items){
            delete item;
        }
    }
};

class FnItemNode : public ASTNode {
public:
    std::string name; // 函数名
    ASTNode* blockExpr = nullptr; // 函数体
    ASTNode* returnType = nullptr; // 返回类型
    std::vector<ASTNode*> parameters; // 函数参数
    FnItemNode(const ASTNodeType kind_,rx::Parser::FunctionDefinitionContext* ctx);
    ~FnItemNode(){
        if(blockExpr) delete blockExpr;
        if(returnType) delete returnType;
        for(auto param : parameters){
            delete param;
        }
    }
};

class StructItemNode : public ASTNode {
public:
    std::string name; // 结构体名
    std::vector<ASTNode*> structField; // 结构体里的内容
    StructItemNode(const ASTNodeType kind_,rx::Parser::StructDefinitionContext* ctx);
    ~StructItemNode(){
        for(auto field : structField){
            delete field;
        }
    }
};

class ConstItemNode : public ASTNode {
public:
    std::string name; // 常量名
    ASTNode* type = nullptr; // 常量类型
    ASTNode* value = nullptr; // 常量值
    ConstItemNode(const ASTNodeType kind_,rx::Parser::ConstantItemContext* ctx);
    ~ConstItemNode(){
        if(type) delete type;
        if(value) delete value;
    }
};

class ImplItemNode : public ASTNode {
public:
    ASTNode* type = nullptr; // 填充的类型
    std::vector<ASTNode*> associatedItems; // impl块的内容
    ImplItemNode(const ASTNodeType kind_,rx::Parser::InherentImplContext* ctx);
    ~ImplItemNode(){
        if(type) delete type;
        for(auto item : associatedItems){
            delete item;
        }
    }
};

// statements
class LetStmtNode : public ASTNode {
public:
    std::string name; // 变量名
    ASTNode* type = nullptr; // 变量类型（可能需要推断）
    ASTNode* expr = nullptr; // 绑定值
    bool mut; // 是否可变
    LetStmtNode(const ASTNodeType kind_,rx::Parser::LetStatementContext* ctx);
    ~LetStmtNode(){
        if(type) delete type;
        if(expr) delete expr;
    }
};

class ExprStmtNode : public ASTNode {
public:
    ASTNode* expr = nullptr;
    ExprStmtNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
    ~ExprStmtNode(){
        if(expr) delete expr;
    }
};

// expr
class IntLitNode : public ASTNode {
public:
    uint64_t value;
    std::string suffix;
    IntLitNode(const ASTNodeType kind_,std::string value_);
};
class BoolLitNode : public ASTNode {
public:
    bool value;
    BoolLitNode(const ASTNodeType kind_,bool vlaue_);
};
class PathExprNode : public ASTNode {
public:
    std::vector<std::string> segments;
    PathExprNode(const ASTNodeType kind_,rx::Parser::PathInExpressionContext* ctx);
};
class StructExprNode : public ASTNode {
public:
    ASTNode* struct_name = nullptr;
    std::vector<std::string> member_name;
    std::vector<ASTNode*> expr;
    StructExprNode(const ASTNodeType kind_);
    ~StructExprNode(){
        if(struct_name) delete struct_name;
        for(auto expression : expr){
            delete expression;
        }
    }
};
class ArrayExprNode : public ASTNode {
public:
    std::vector<ASTNode*> elements; // 数组中的元素
    ArrayExprNode(const ASTNodeType kind_,rx::Parser::ArrayExpressionContext* ctx);
    ~ArrayExprNode(){
        for(auto element : elements){
            delete element;
        }
    }

};
class ArrayRepeatNode : public ASTNode {
public:
    ASTNode* element = nullptr; // 元素
    ASTNode* num = nullptr; // 重复次数
    ArrayRepeatNode(const ASTNodeType kind_);
    ~ArrayRepeatNode(){
        if(element) delete element;
        if(num) delete num;
    }

};
class UnaryExprNode : public ASTNode {
public:
    ASTNode* expr = nullptr;
    std::string op;
    UnaryExprNode(const ASTNodeType kind_);
    UnaryExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
    ~UnaryExprNode(){
        if(expr) delete expr;
    }
};
class BinaryExprNode : public ASTNode {
public:
    std::vector<ASTNode*> operands;
    std::vector<std::string> op;
    BinaryExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
    ~BinaryExprNode(){
        for(auto operand : operands){
            delete operand;
        }
    }
};
class BlockExprNode : public ASTNode {
public:
    std::vector<ASTNode*> statements;
    ASTNode* return_expression = nullptr;
    BlockExprNode(const ASTNodeType kind_,rx::Parser::BlockExpressionContext* ctx);
    ~BlockExprNode(){
        for(auto stmt : statements){
            delete stmt;
        }
        if(return_expression) delete return_expression; 
    }
};
class AssignExprNode : public ASTNode {
public:
    ASTNode* left = nullptr;
    ASTNode* right = nullptr;
    std::string op;
    AssignExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
    ~AssignExprNode(){
        if(left) delete left;
        if(right) delete right;
    }
};
class IfExprNode : public ASTNode {
public:
    ASTNode* condition = nullptr;
    ASTNode* if_block = nullptr;
    ASTNode* else_block = nullptr;
    IfExprNode(const ASTNodeType kind_,rx::Parser::IfExpressionContext* ctx);
    ~IfExprNode(){
        if(condition) delete condition;
        if(if_block) delete if_block;
        if(else_block) delete else_block;
    }
};
class WhileExprNode : public ASTNode {
public:
    ASTNode* condition = nullptr;
    ASTNode* content = nullptr;
    WhileExprNode(const ASTNodeType kind_,rx::Parser::ConditionExpressionContext* ctx1,rx::Parser::BlockExpressionContext* ctx2);
    ~WhileExprNode(){
        if(condition) delete condition;
        if(content) delete content;
    }
};
class LoopExprNode : public ASTNode {
public:
    ASTNode* content = nullptr;
    LoopExprNode(const ASTNodeType kind_,rx::Parser::BlockExpressionContext* ctx);
    ~LoopExprNode(){
        if(content) delete content;
    }
};
class CastExprNode : public ASTNode {
public:
    ASTNode* expr = nullptr;
    std::vector<ASTNode*> types;
    CastExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
    ~CastExprNode(){
        if(expr) delete expr;
        for(auto type : types){
            delete type;
        }
    }

};
class BreakExprNode : public ASTNode {
public:
    ASTNode* expr = nullptr;
    BreakExprNode(const ASTNodeType kind_);
    ~BreakExprNode(){
        if(expr) delete expr;
    }
};
class ContinueExprNode : public ASTNode {
public:
    ContinueExprNode(const ASTNodeType kind_);
};
class CallExprNode : public ASTNode {
public:
    ASTNode* func = nullptr;
    std::vector<ASTNode*> args;
    CallExprNode(const ASTNodeType kind_);
    ~CallExprNode(){
        if(func) delete func;
        for(auto arg : args){
            delete arg;
        }
    }
};
class MethodCallExprNode : public ASTNode {
public:
    ASTNode* receiver = nullptr;
    std::string name;
    std::vector<ASTNode*> args;
    MethodCallExprNode(const ASTNodeType kind_);
    ~MethodCallExprNode(){
        if(receiver) delete receiver;
        for(auto arg : args){
            delete arg;
        }
    }
};
class FieldExprNode : public ASTNode {
public:
    ASTNode* receiver = nullptr;
    std::string name;
    FieldExprNode(const ASTNodeType kind_);
    ~FieldExprNode(){
        if(receiver) delete receiver;
    }
};
class IndexExprNode : public ASTNode {
public:
    ASTNode* base = nullptr;
    ASTNode* index = nullptr;
    IndexExprNode(const ASTNodeType kind_);
    ~IndexExprNode(){
        if(base) delete base;
        if(index) delete index;
    }
};
class ReturnExprNode : public ASTNode {
public:
    ASTNode* expr = nullptr;
    ReturnExprNode(const ASTNodeType kind_);
    ~ReturnExprNode(){
        if(expr) delete expr;
    }
};
// type
class UnitTypeNode : public ASTNode {
public:
    UnitTypeNode(const ASTNodeType kind_);
};
class PathTypeNode : public ASTNode {
public:
    std::vector<std::string> segments; // 路径分段
    PathTypeNode(const ASTNodeType kind_,rx::Parser::TypePathContext* ctx);
    PathTypeNode(const ASTNodeType kind_);
};
class RefTypeNode : public ASTNode {
public:
    ASTNode* type = nullptr; // &后面跟着的type 如 &i32, &'a i32, &'a mut Vec<i32>, and &'_ i32
    bool mut;
    RefTypeNode(const ASTNodeType kind_,rx::Parser::ReferenceTypeContext* ctx);
    RefTypeNode(const ASTNodeType kind_);
    ~RefTypeNode(){
        if(type) delete type;
    }
};
class ArrayTypeNode : public ASTNode {
public:
    ASTNode* type = nullptr;
    ASTNode* length = nullptr;
    ArrayTypeNode(const ASTNodeType kind_,rx::Parser::ArrayTypeContext* ctx);
    ~ArrayTypeNode(){
        if(type) delete type;
        if(length) delete length;
    }
};
// others
class FnSelfParamNode : public ASTNode {
public:
    bool mut;
    bool amp;
    FnSelfParamNode(const ASTNodeType kind_,rx::Parser::SelfParamContext* ctx);
};
class FnParamNode : public ASTNode {
public:
    std::string name;
    bool mut;
    ASTNode* type = nullptr;
    FnParamNode(const ASTNodeType kind_,rx::Parser::FunctionParamContext* ctx);
    ~FnParamNode(){
        if(type) delete type;
    }
};
class StructFieldNode : public ASTNode {
public:
    std::string name;
    ASTNode* type = nullptr;
    StructFieldNode(const ASTNodeType kind_,rx::Parser::StructFieldContext* ctx);
    ~StructFieldNode(){
        if(type) delete type;
    }
};