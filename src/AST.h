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
    ASTNode* CheckType(rx::Parser::TypeRefContext* ctx);
    ASTNode* CheckConstValue(rx::Parser::ConstValueContext* ctx);
    virtual ~ASTNode() = 0;
};
// 派生类
// items
class CrateNode : public ASTNode {
public:
    std::vector<ASTNode*> items; // 一个程序中的所有块
    CrateNode(const ASTNodeType kind_,rx::Parser::CrateContext* ctx);
};

class FnItemNode : public ASTNode {
public:
    std::string name; // 函数名
    ASTNode* blockExpr; // 函数体
    ASTNode* returnType = nullptr; // 返回类型
    std::vector<ASTNode*> parameters; // 函数参数
    FnItemNode(const ASTNodeType kind_,rx::Parser::FunctionDefinitionContext* ctx);

};

class StructItemNode : public ASTNode {
public:
    std::string name; // 结构体名
    std::vector<ASTNode*> structField; // 结构体里的内容
    StructItemNode(const ASTNodeType kind_,rx::Parser::StructDefinitionContext* ctx);
};

class ConstItemNode : public ASTNode {
public:
    std::string name; // 常量名
    ASTNode* type; // 常量类型
    ASTNode* value; // 常量值
    ConstItemNode(const ASTNodeType kind_,rx::Parser::ConstantItemContext* ctx);

};

class ImplItemNode : public ASTNode {
public:
    ASTNode* type; // 填充的类型
    std::vector<ASTNode*> associatedItems; // impl块的内容
    ImplItemNode(const ASTNodeType kind_,rx::Parser::InherentImplContext* ctx);
};

// statements
class LetStmtNode : public ASTNode {
public:
    std::string name; // 变量名
    ASTNode* type; // 变量类型（可能需要推断）
    ASTNode* expr; // 绑定值
    bool mut; // 是否可变
    LetStmtNode(const ASTNodeType kind_,rx::Parser::LetStatementContext* ctx);

};

class ExprStmtNode : public ASTNode {
public:
    ASTNode* expr;
    ExprStmtNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
};

// expr
class IntLitNode : public ASTNode {
public:
    uint64_t value;
    IntLitNode(const ASTNodeType kind_,std::string value_);
};
class BoolLitNode : public ASTNode {
public:
    bool value;
    BoolLitNode(const ASTNodeType kind_,bool vlaue_);
};
class PathExprNode : public ASTNode {
public:
    PathExprNode(const ASTNodeType kind_);

};
class StructExprNode : public ASTNode {
public:
    StructExprNode(const ASTNodeType kind_,rx::Parser::StructFieldContext* ctx);

};
class ArrayExprNode : public ASTNode {
public:
    ArrayExprNode(const ASTNodeType kind_);

};
class ArrayRepeatNode : public ASTNode {
public:
    ArrayRepeatNode(const ASTNodeType kind_);

};
class UnaryExprNode : public ASTNode {
public:
    ASTNode* expr;
    std::string op;
    UnaryExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
};
class BinaryExprNode : public ASTNode {
public:
    std::vector<ASTNode*> operands;
    std::vector<std::string> op;
    BinaryExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
};
class BlockExprNode : public ASTNode {
public:
    std::vector<ASTNode*> statements;
    ASTNode* return_expression = nullptr;
    BlockExprNode(const ASTNodeType kind_,rx::Parser::BlockExpressionContext* ctx);
};
class AssignExprNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right = nullptr;
    std::string op;
    AssignExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);
};
class IfExprNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* if_block;
    ASTNode* else_block = nullptr;
    IfExprNode(const ASTNodeType kind_,rx::Parser::IfExpressionContext* ctx);
};
class WhileExprNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* content;
    WhileExprNode(const ASTNodeType kind_,rx::Parser::ConditionExpressionContext* ctx1,rx::Parser::BlockExpressionContext* ctx2);
};
class LoopExprNode : public ASTNode {
public:
    ASTNode* content;
    LoopExprNode(const ASTNodeType kind_,rx::Parser::BlockExpressionContext* ctx);
};
class CastExprNode : public ASTNode {
public:
    ASTNode* expr;
    std::vector<ASTNode*> types;
    CastExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx);

};
class BreakExprNode : public ASTNode {
public:
    BreakExprNode(const ASTNodeType kind_);
};
class ContinueExprNode : public ASTNode {
public:
    ContinueExprNode(const ASTNodeType kind_);
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

};
class RefTypeNode : public ASTNode {
public:
    ASTNode* type; // &后面跟着的type 如 &i32, &'a i32, &'a mut Vec<i32>, and &'_ i32
    bool mut;
    RefTypeNode(const ASTNodeType kind_,rx::Parser::ReferenceTypeContext* ctx);

};
class ArrayTypeNode : public ASTNode {
public:
    ASTNode* type;
    ASTNode* length;
    ArrayTypeNode(const ASTNodeType kind_,rx::Parser::ArrayTypeContext* ctx);
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
    ASTNode* type;
    FnParamNode(const ASTNodeType kind_,rx::Parser::FunctionParamContext* ctx);
};
class StructFieldNode : public ASTNode {
public:
    std::string name;
    ASTNode* type;
    StructFieldNode(const ASTNodeType kind_,rx::Parser::StructFieldContext* ctx);
};