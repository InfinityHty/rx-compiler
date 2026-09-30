
// Generated from Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace rx {


class  Parser : public antlr4::Parser {
public:
  enum {
    AS = 1, BREAK = 2, CONST = 3, CONTINUE = 4, CRATE = 5, ELSE = 6, FALSE = 7, 
    FN = 8, IF = 9, IMPL = 10, LET = 11, LOOP = 12, MUT = 13, RETURN = 14, 
    SELF_VALUE = 15, SELF_TYPE = 16, STATIC = 17, STRUCT = 18, SUPER = 19, 
    TRUE = 20, USE = 21, WHERE = 22, WHILE = 23, RESERVED_KEYWORD = 24, 
    DERIVE = 25, COPY = 26, CLONE = 27, PARTIAL_EQ = 28, EQ = 29, UNDERSCORE = 30, 
    IDENTIFIER = 31, INVALID_LIFETIME = 32, INVALID_CHARACTER_LITERAL = 33, 
    LIFETIME = 34, INTEGER_LITERAL = 35, INVALID_NUMBER = 36, GT = 37, LT = 38, 
    LE = 39, EQEQ = 40, NE = 41, ANDAND = 42, OROR = 43, NOT = 44, PLUS = 45, 
    MINUS = 46, STAR = 47, SLASH = 48, PERCENT = 49, CARET = 50, AMP = 51, 
    PIPE = 52, SHL = 53, ASSIGN = 54, PLUS_ASSIGN = 55, MINUS_ASSIGN = 56, 
    STAR_ASSIGN = 57, SLASH_ASSIGN = 58, PERCENT_ASSIGN = 59, CARET_ASSIGN = 60, 
    AMP_ASSIGN = 61, PIPE_ASSIGN = 62, SHL_ASSIGN = 63, DOT = 64, COMMA = 65, 
    SEMI = 66, COLON = 67, PATHSEP = 68, ARROW = 69, HASH = 70, LBRACE = 71, 
    RBRACE = 72, LBRACKET = 73, RBRACKET = 74, LPAREN = 75, RPAREN = 76, 
    WHITESPACE = 77, LINE_COMMENT = 78, BLOCK_COMMENT = 79, UNTERMINATED_BLOCK_COMMENT = 80, 
    ERROR_CHAR = 81, GT_SECOND = 82, GE_EQ = 83, SHR_EQ = 84
  };

  enum {
    RuleCrate = 0, RuleItem = 1, RuleUseDeclaration = 2, RuleUseTree = 3, 
    RuleUsePath = 4, RuleUsePathSegment = 5, RuleFunctionDefinition = 6, 
    RuleFunctionParameters = 7, RuleSelfParam = 8, RuleFunctionParam = 9, 
    RuleStructDefinition = 10, RuleStructField = 11, RuleOuterAttribute = 12, 
    RuleDeriveName = 13, RuleConstantItem = 14, RuleInherentImpl = 15, RuleAssociatedItem = 16, 
    RuleGenericParams = 17, RuleLifetimeParam = 18, RuleLifetime = 19, RuleLifetimeBounds = 20, 
    RuleTypeParamBounds = 21, RuleWhereClause = 22, RuleWhereClauseItem = 23, 
    RuleTypeRef = 24, RuleReferenceType = 25, RuleArrayType = 26, RuleTypePath = 27, 
    RuleTypePathSegment = 28, RulePathInExpression = 29, RulePathExprSegment = 30, 
    RulePathIdentSegment = 31, RuleGenericArgs = 32, RuleGenericArg = 33, 
    RuleGenericClose = 34, RuleClosedCastType = 35, RuleConstValue = 36, 
    RuleMagnitude = 37, RuleIdentifierBinding = 38, RuleLetStatement = 39, 
    RuleBlockExpression = 40, RuleStatement = 41, RuleExpressionWithBlock = 42, 
    RuleIfExpression = 43, RuleExpression = 44, RuleAssignmentExpression = 45, 
    RuleLogicalOrExpression = 46, RuleLogicalAndExpression = 47, RuleComparisonExpression = 48, 
    RuleBitOrExpression = 49, RuleClosedBitOrExpression = 50, RuleBitXorExpression = 51, 
    RuleClosedBitXorExpression = 52, RuleBitAndExpression = 53, RuleClosedBitAndExpression = 54, 
    RuleShiftExpression = 55, RuleClosedShiftExpression = 56, RuleAdditiveExpression = 57, 
    RuleClosedAdditiveExpression = 58, RuleMultiplicativeExpression = 59, 
    RuleClosedMultiplicativeExpression = 60, RuleCastExpression = 61, RuleClosedCastExpression = 62, 
    RuleUnaryExpression = 63, RulePostfixExpression = 64, RuleConditionExpression = 65, 
    RuleConditionAssignmentExpression = 66, RuleConditionLogicalOrExpression = 67, 
    RuleConditionLogicalAndExpression = 68, RuleConditionComparisonExpression = 69, 
    RuleConditionBitOrExpression = 70, RuleConditionClosedBitOrExpression = 71, 
    RuleConditionBitXorExpression = 72, RuleConditionClosedBitXorExpression = 73, 
    RuleConditionBitAndExpression = 74, RuleConditionClosedBitAndExpression = 75, 
    RuleConditionShiftExpression = 76, RuleConditionClosedShiftExpression = 77, 
    RuleConditionAdditiveExpression = 78, RuleConditionClosedAdditiveExpression = 79, 
    RuleConditionMultiplicativeExpression = 80, RuleConditionClosedMultiplicativeExpression = 81, 
    RuleConditionCastExpression = 82, RuleConditionClosedCastExpression = 83, 
    RuleConditionUnaryExpression = 84, RuleConditionPostfixExpression = 85, 
    RuleConditionBreakExpression = 86, RuleConditionBreakAssignmentExpression = 87, 
    RuleConditionBreakLogicalOrExpression = 88, RuleConditionBreakLogicalAndExpression = 89, 
    RuleConditionBreakComparisonExpression = 90, RuleConditionBreakBitOrExpression = 91, 
    RuleConditionBreakClosedBitOrExpression = 92, RuleConditionBreakBitXorExpression = 93, 
    RuleConditionBreakClosedBitXorExpression = 94, RuleConditionBreakBitAndExpression = 95, 
    RuleConditionBreakClosedBitAndExpression = 96, RuleConditionBreakShiftExpression = 97, 
    RuleConditionBreakClosedShiftExpression = 98, RuleConditionBreakAdditiveExpression = 99, 
    RuleConditionBreakClosedAdditiveExpression = 100, RuleConditionBreakMultiplicativeExpression = 101, 
    RuleConditionBreakClosedMultiplicativeExpression = 102, RuleConditionBreakCastExpression = 103, 
    RuleConditionBreakClosedCastExpression = 104, RuleConditionBreakUnaryExpression = 105, 
    RuleConditionBreakPostfixExpression = 106, RuleStatementExpression = 107, 
    RuleStatementAssignmentExpression = 108, RuleStatementLogicalOrExpression = 109, 
    RuleStatementLogicalAndExpression = 110, RuleStatementComparisonExpression = 111, 
    RuleStatementBitOrExpression = 112, RuleStatementClosedBitOrExpression = 113, 
    RuleStatementBitXorExpression = 114, RuleStatementClosedBitXorExpression = 115, 
    RuleStatementBitAndExpression = 116, RuleStatementClosedBitAndExpression = 117, 
    RuleStatementShiftExpression = 118, RuleStatementClosedShiftExpression = 119, 
    RuleStatementAdditiveExpression = 120, RuleStatementClosedAdditiveExpression = 121, 
    RuleStatementMultiplicativeExpression = 122, RuleStatementClosedMultiplicativeExpression = 123, 
    RuleStatementCastExpression = 124, RuleStatementClosedCastExpression = 125, 
    RuleStatementUnaryExpression = 126, RuleStatementPostfixExpression = 127, 
    RulePrimaryExpression = 128, RuleNonBlockPrimary = 129, RuleConditionPrimary = 130, 
    RuleConditionPrimaryWithoutBareBlock = 131, RuleLiteralExpression = 132, 
    RuleStructExprFields = 133, RuleStructExprField = 134, RuleArrayExpression = 135, 
    RulePostfixSuffix = 136, RuleDotSuffix = 137, RuleCallArguments = 138, 
    RuleUnaryOperator = 139, RuleMultiplicativeOperator = 140, RuleAdditiveOperator = 141, 
    RuleShiftRight = 142, RuleComparisonExceptLt = 143, RuleAssignmentOperator = 144, 
    RuleEqualsSign = 145, RuleIdentifier = 146
  };

  explicit Parser(antlr4::TokenStream *input);

  Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CrateContext;
  class ItemContext;
  class UseDeclarationContext;
  class UseTreeContext;
  class UsePathContext;
  class UsePathSegmentContext;
  class FunctionDefinitionContext;
  class FunctionParametersContext;
  class SelfParamContext;
  class FunctionParamContext;
  class StructDefinitionContext;
  class StructFieldContext;
  class OuterAttributeContext;
  class DeriveNameContext;
  class ConstantItemContext;
  class InherentImplContext;
  class AssociatedItemContext;
  class GenericParamsContext;
  class LifetimeParamContext;
  class LifetimeContext;
  class LifetimeBoundsContext;
  class TypeParamBoundsContext;
  class WhereClauseContext;
  class WhereClauseItemContext;
  class TypeRefContext;
  class ReferenceTypeContext;
  class ArrayTypeContext;
  class TypePathContext;
  class TypePathSegmentContext;
  class PathInExpressionContext;
  class PathExprSegmentContext;
  class PathIdentSegmentContext;
  class GenericArgsContext;
  class GenericArgContext;
  class GenericCloseContext;
  class ClosedCastTypeContext;
  class ConstValueContext;
  class MagnitudeContext;
  class IdentifierBindingContext;
  class LetStatementContext;
  class BlockExpressionContext;
  class StatementContext;
  class ExpressionWithBlockContext;
  class IfExpressionContext;
  class ExpressionContext;
  class AssignmentExpressionContext;
  class LogicalOrExpressionContext;
  class LogicalAndExpressionContext;
  class ComparisonExpressionContext;
  class BitOrExpressionContext;
  class ClosedBitOrExpressionContext;
  class BitXorExpressionContext;
  class ClosedBitXorExpressionContext;
  class BitAndExpressionContext;
  class ClosedBitAndExpressionContext;
  class ShiftExpressionContext;
  class ClosedShiftExpressionContext;
  class AdditiveExpressionContext;
  class ClosedAdditiveExpressionContext;
  class MultiplicativeExpressionContext;
  class ClosedMultiplicativeExpressionContext;
  class CastExpressionContext;
  class ClosedCastExpressionContext;
  class UnaryExpressionContext;
  class PostfixExpressionContext;
  class ConditionExpressionContext;
  class ConditionAssignmentExpressionContext;
  class ConditionLogicalOrExpressionContext;
  class ConditionLogicalAndExpressionContext;
  class ConditionComparisonExpressionContext;
  class ConditionBitOrExpressionContext;
  class ConditionClosedBitOrExpressionContext;
  class ConditionBitXorExpressionContext;
  class ConditionClosedBitXorExpressionContext;
  class ConditionBitAndExpressionContext;
  class ConditionClosedBitAndExpressionContext;
  class ConditionShiftExpressionContext;
  class ConditionClosedShiftExpressionContext;
  class ConditionAdditiveExpressionContext;
  class ConditionClosedAdditiveExpressionContext;
  class ConditionMultiplicativeExpressionContext;
  class ConditionClosedMultiplicativeExpressionContext;
  class ConditionCastExpressionContext;
  class ConditionClosedCastExpressionContext;
  class ConditionUnaryExpressionContext;
  class ConditionPostfixExpressionContext;
  class ConditionBreakExpressionContext;
  class ConditionBreakAssignmentExpressionContext;
  class ConditionBreakLogicalOrExpressionContext;
  class ConditionBreakLogicalAndExpressionContext;
  class ConditionBreakComparisonExpressionContext;
  class ConditionBreakBitOrExpressionContext;
  class ConditionBreakClosedBitOrExpressionContext;
  class ConditionBreakBitXorExpressionContext;
  class ConditionBreakClosedBitXorExpressionContext;
  class ConditionBreakBitAndExpressionContext;
  class ConditionBreakClosedBitAndExpressionContext;
  class ConditionBreakShiftExpressionContext;
  class ConditionBreakClosedShiftExpressionContext;
  class ConditionBreakAdditiveExpressionContext;
  class ConditionBreakClosedAdditiveExpressionContext;
  class ConditionBreakMultiplicativeExpressionContext;
  class ConditionBreakClosedMultiplicativeExpressionContext;
  class ConditionBreakCastExpressionContext;
  class ConditionBreakClosedCastExpressionContext;
  class ConditionBreakUnaryExpressionContext;
  class ConditionBreakPostfixExpressionContext;
  class StatementExpressionContext;
  class StatementAssignmentExpressionContext;
  class StatementLogicalOrExpressionContext;
  class StatementLogicalAndExpressionContext;
  class StatementComparisonExpressionContext;
  class StatementBitOrExpressionContext;
  class StatementClosedBitOrExpressionContext;
  class StatementBitXorExpressionContext;
  class StatementClosedBitXorExpressionContext;
  class StatementBitAndExpressionContext;
  class StatementClosedBitAndExpressionContext;
  class StatementShiftExpressionContext;
  class StatementClosedShiftExpressionContext;
  class StatementAdditiveExpressionContext;
  class StatementClosedAdditiveExpressionContext;
  class StatementMultiplicativeExpressionContext;
  class StatementClosedMultiplicativeExpressionContext;
  class StatementCastExpressionContext;
  class StatementClosedCastExpressionContext;
  class StatementUnaryExpressionContext;
  class StatementPostfixExpressionContext;
  class PrimaryExpressionContext;
  class NonBlockPrimaryContext;
  class ConditionPrimaryContext;
  class ConditionPrimaryWithoutBareBlockContext;
  class LiteralExpressionContext;
  class StructExprFieldsContext;
  class StructExprFieldContext;
  class ArrayExpressionContext;
  class PostfixSuffixContext;
  class DotSuffixContext;
  class CallArgumentsContext;
  class UnaryOperatorContext;
  class MultiplicativeOperatorContext;
  class AdditiveOperatorContext;
  class ShiftRightContext;
  class ComparisonExceptLtContext;
  class AssignmentOperatorContext;
  class EqualsSignContext;
  class IdentifierContext; 

  class  CrateContext : public antlr4::ParserRuleContext {
  public:
    CrateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ItemContext *> item();
    ItemContext* item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CrateContext* crate();

  class  ItemContext : public antlr4::ParserRuleContext {
  public:
    ItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UseDeclarationContext *useDeclaration();
    FunctionDefinitionContext *functionDefinition();
    StructDefinitionContext *structDefinition();
    ConstantItemContext *constantItem();
    InherentImplContext *inherentImpl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ItemContext* item();

  class  UseDeclarationContext : public antlr4::ParserRuleContext {
  public:
    UseDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *USE();
    UseTreeContext *useTree();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UseDeclarationContext* useDeclaration();

  class  UseTreeContext : public antlr4::ParserRuleContext {
  public:
    UseTreeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *PATHSEP();
    std::vector<UseTreeContext *> useTree();
    UseTreeContext* useTree(size_t i);
    UsePathContext *usePath();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *AS();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *UNDERSCORE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UseTreeContext* useTree();

  class  UsePathContext : public antlr4::ParserRuleContext {
  public:
    UsePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UsePathSegmentContext *> usePathSegment();
    UsePathSegmentContext* usePathSegment(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PATHSEP();
    antlr4::tree::TerminalNode* PATHSEP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UsePathContext* usePath();

  class  UsePathSegmentContext : public antlr4::ParserRuleContext {
  public:
    UsePathSegmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *SELF_VALUE();
    antlr4::tree::TerminalNode *SUPER();
    antlr4::tree::TerminalNode *CRATE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UsePathSegmentContext* usePathSegment();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FN();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockExpressionContext *blockExpression();
    GenericParamsContext *genericParams();
    FunctionParametersContext *functionParameters();
    antlr4::tree::TerminalNode *ARROW();
    TypeRefContext *typeRef();
    WhereClauseContext *whereClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionParametersContext : public antlr4::ParserRuleContext {
  public:
    FunctionParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelfParamContext *selfParam();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    std::vector<FunctionParamContext *> functionParam();
    FunctionParamContext* functionParam(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionParametersContext* functionParameters();

  class  SelfParamContext : public antlr4::ParserRuleContext {
  public:
    SelfParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELF_VALUE();
    antlr4::tree::TerminalNode *AMP();
    antlr4::tree::TerminalNode *MUT();
    LifetimeContext *lifetime();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelfParamContext* selfParam();

  class  FunctionParamContext : public antlr4::ParserRuleContext {
  public:
    FunctionParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierBindingContext *identifierBinding();
    antlr4::tree::TerminalNode *COLON();
    TypeRefContext *typeRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionParamContext* functionParam();

  class  StructDefinitionContext : public antlr4::ParserRuleContext {
  public:
    StructDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<OuterAttributeContext *> outerAttribute();
    OuterAttributeContext* outerAttribute(size_t i);
    GenericParamsContext *genericParams();
    WhereClauseContext *whereClause();
    std::vector<StructFieldContext *> structField();
    StructFieldContext* structField(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDefinitionContext* structDefinition();

  class  StructFieldContext : public antlr4::ParserRuleContext {
  public:
    StructFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *COLON();
    TypeRefContext *typeRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructFieldContext* structField();

  class  OuterAttributeContext : public antlr4::ParserRuleContext {
  public:
    OuterAttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HASH();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *DERIVE();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<DeriveNameContext *> deriveName();
    DeriveNameContext* deriveName(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OuterAttributeContext* outerAttribute();

  class  DeriveNameContext : public antlr4::ParserRuleContext {
  public:
    DeriveNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COPY();
    antlr4::tree::TerminalNode *CLONE();
    antlr4::tree::TerminalNode *PARTIAL_EQ();
    antlr4::tree::TerminalNode *EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeriveNameContext* deriveName();

  class  ConstantItemContext : public antlr4::ParserRuleContext {
  public:
    ConstantItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *COLON();
    TypeRefContext *typeRef();
    EqualsSignContext *equalsSign();
    ConstValueContext *constValue();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantItemContext* constantItem();

  class  InherentImplContext : public antlr4::ParserRuleContext {
  public:
    InherentImplContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPL();
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    GenericParamsContext *genericParams();
    WhereClauseContext *whereClause();
    std::vector<AssociatedItemContext *> associatedItem();
    AssociatedItemContext* associatedItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InherentImplContext* inherentImpl();

  class  AssociatedItemContext : public antlr4::ParserRuleContext {
  public:
    AssociatedItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantItemContext *constantItem();
    FunctionDefinitionContext *functionDefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssociatedItemContext* associatedItem();

  class  GenericParamsContext : public antlr4::ParserRuleContext {
  public:
    GenericParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    GenericCloseContext *genericClose();
    std::vector<LifetimeParamContext *> lifetimeParam();
    LifetimeParamContext* lifetimeParam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericParamsContext* genericParams();

  class  LifetimeParamContext : public antlr4::ParserRuleContext {
  public:
    LifetimeParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LifetimeContext *lifetime();
    antlr4::tree::TerminalNode *COLON();
    LifetimeBoundsContext *lifetimeBounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LifetimeParamContext* lifetimeParam();

  class  LifetimeContext : public antlr4::ParserRuleContext {
  public:
    LifetimeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIFETIME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LifetimeContext* lifetime();

  class  LifetimeBoundsContext : public antlr4::ParserRuleContext {
  public:
    LifetimeBoundsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LifetimeContext *> lifetime();
    LifetimeContext* lifetime(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LifetimeBoundsContext* lifetimeBounds();

  class  TypeParamBoundsContext : public antlr4::ParserRuleContext {
  public:
    TypeParamBoundsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LifetimeContext *> lifetime();
    LifetimeContext* lifetime(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeParamBoundsContext* typeParamBounds();

  class  WhereClauseContext : public antlr4::ParserRuleContext {
  public:
    WhereClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    std::vector<WhereClauseItemContext *> whereClauseItem();
    WhereClauseItemContext* whereClauseItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereClauseContext* whereClause();

  class  WhereClauseItemContext : public antlr4::ParserRuleContext {
  public:
    WhereClauseItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LifetimeContext *lifetime();
    antlr4::tree::TerminalNode *COLON();
    LifetimeBoundsContext *lifetimeBounds();
    TypeRefContext *typeRef();
    TypeParamBoundsContext *typeParamBounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereClauseItemContext* whereClauseItem();

  class  TypeRefContext : public antlr4::ParserRuleContext {
  public:
    TypeRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *RPAREN();
    TypePathContext *typePath();
    ReferenceTypeContext *referenceType();
    ArrayTypeContext *arrayType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeRefContext* typeRef();

  class  ReferenceTypeContext : public antlr4::ParserRuleContext {
  public:
    ReferenceTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *AMP();
    antlr4::tree::TerminalNode *ANDAND();
    LifetimeContext *lifetime();
    antlr4::tree::TerminalNode *MUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReferenceTypeContext* referenceType();

  class  ArrayTypeContext : public antlr4::ParserRuleContext {
  public:
    ArrayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *SEMI();
    ConstValueContext *constValue();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayTypeContext* arrayType();

  class  TypePathContext : public antlr4::ParserRuleContext {
  public:
    TypePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypePathSegmentContext *> typePathSegment();
    TypePathSegmentContext* typePathSegment(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PATHSEP();
    antlr4::tree::TerminalNode* PATHSEP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypePathContext* typePath();

  class  TypePathSegmentContext : public antlr4::ParserRuleContext {
  public:
    TypePathSegmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PathIdentSegmentContext *pathIdentSegment();
    GenericArgsContext *genericArgs();
    antlr4::tree::TerminalNode *PATHSEP();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypePathSegmentContext* typePathSegment();

  class  PathInExpressionContext : public antlr4::ParserRuleContext {
  public:
    PathInExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PathExprSegmentContext *> pathExprSegment();
    PathExprSegmentContext* pathExprSegment(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PATHSEP();
    antlr4::tree::TerminalNode* PATHSEP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PathInExpressionContext* pathInExpression();

  class  PathExprSegmentContext : public antlr4::ParserRuleContext {
  public:
    PathExprSegmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PathIdentSegmentContext *pathIdentSegment();
    antlr4::tree::TerminalNode *PATHSEP();
    GenericArgsContext *genericArgs();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PathExprSegmentContext* pathExprSegment();

  class  PathIdentSegmentContext : public antlr4::ParserRuleContext {
  public:
    PathIdentSegmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *SELF_VALUE();
    antlr4::tree::TerminalNode *SELF_TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PathIdentSegmentContext* pathIdentSegment();

  class  GenericArgsContext : public antlr4::ParserRuleContext {
  public:
    GenericArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    GenericCloseContext *genericClose();
    std::vector<GenericArgContext *> genericArg();
    GenericArgContext* genericArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericArgsContext* genericArgs();

  class  GenericArgContext : public antlr4::ParserRuleContext {
  public:
    GenericArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LifetimeContext *lifetime();
    TypeRefContext *typeRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericArgContext* genericArg();

  class  GenericCloseContext : public antlr4::ParserRuleContext {
  public:
    GenericCloseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GT_SECOND();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericCloseContext* genericClose();

  class  ClosedCastTypeContext : public antlr4::ParserRuleContext {
  public:
    ClosedCastTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    TypeRefContext *typeRef();
    ArrayTypeContext *arrayType();
    ClosedCastTypeContext *closedCastType();
    antlr4::tree::TerminalNode *AMP();
    antlr4::tree::TerminalNode *ANDAND();
    LifetimeContext *lifetime();
    antlr4::tree::TerminalNode *MUT();
    PathIdentSegmentContext *pathIdentSegment();
    GenericArgsContext *genericArgs();
    std::vector<TypePathSegmentContext *> typePathSegment();
    TypePathSegmentContext* typePathSegment(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PATHSEP();
    antlr4::tree::TerminalNode* PATHSEP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedCastTypeContext* closedCastType();

  class  ConstValueContext : public antlr4::ParserRuleContext {
  public:
    ConstValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_LITERAL();
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();
    PathInExpressionContext *pathInExpression();
    antlr4::tree::TerminalNode *MINUS();
    MagnitudeContext *magnitude();
    antlr4::tree::TerminalNode *LPAREN();
    ConstValueContext *constValue();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstValueContext* constValue();

  class  MagnitudeContext : public antlr4::ParserRuleContext {
  public:
    MagnitudeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_LITERAL();
    PathInExpressionContext *pathInExpression();
    antlr4::tree::TerminalNode *LPAREN();
    MagnitudeContext *magnitude();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MagnitudeContext* magnitude();

  class  IdentifierBindingContext : public antlr4::ParserRuleContext {
  public:
    IdentifierBindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *MUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierBindingContext* identifierBinding();

  class  LetStatementContext : public antlr4::ParserRuleContext {
  public:
    LetStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    IdentifierBindingContext *identifierBinding();
    EqualsSignContext *equalsSign();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *COLON();
    TypeRefContext *typeRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LetStatementContext* letStatement();

  class  BlockExpressionContext : public antlr4::ParserRuleContext {
  public:
    BlockExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    StatementExpressionContext *statementExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockExpressionContext* blockExpression();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    LetStatementContext *letStatement();
    ExpressionWithBlockContext *expressionWithBlock();
    StatementExpressionContext *statementExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionWithBlockContext : public antlr4::ParserRuleContext {
  public:
    ExpressionWithBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockExpressionContext *blockExpression();
    IfExpressionContext *ifExpression();
    antlr4::tree::TerminalNode *LOOP();
    antlr4::tree::TerminalNode *WHILE();
    ConditionExpressionContext *conditionExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionWithBlockContext* expressionWithBlock();

  class  IfExpressionContext : public antlr4::ParserRuleContext {
  public:
    IfExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    ConditionExpressionContext *conditionExpression();
    std::vector<BlockExpressionContext *> blockExpression();
    BlockExpressionContext* blockExpression(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    IfExpressionContext *ifExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfExpressionContext* ifExpression();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  AssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    AssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalOrExpressionContext *logicalOrExpression();
    AssignmentOperatorContext *assignmentOperator();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentExpressionContext* assignmentExpression();

  class  LogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalAndExpressionContext *> logicalAndExpression();
    LogicalAndExpressionContext* logicalAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OROR();
    antlr4::tree::TerminalNode* OROR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalOrExpressionContext* logicalOrExpression();

  class  LogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ComparisonExpressionContext *> comparisonExpression();
    ComparisonExpressionContext* comparisonExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ANDAND();
    antlr4::tree::TerminalNode* ANDAND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalAndExpressionContext* logicalAndExpression();

  class  ComparisonExpressionContext : public antlr4::ParserRuleContext {
  public:
    ComparisonExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BitOrExpressionContext *> bitOrExpression();
    BitOrExpressionContext* bitOrExpression(size_t i);
    ComparisonExceptLtContext *comparisonExceptLt();
    ClosedBitOrExpressionContext *closedBitOrExpression();
    antlr4::tree::TerminalNode *LT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonExpressionContext* comparisonExpression();

  class  BitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    BitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BitXorExpressionContext *> bitXorExpression();
    BitXorExpressionContext* bitXorExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BitOrExpressionContext* bitOrExpression();

  class  ClosedBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClosedBitXorExpressionContext *closedBitXorExpression();
    std::vector<BitXorExpressionContext *> bitXorExpression();
    BitXorExpressionContext* bitXorExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedBitOrExpressionContext* closedBitOrExpression();

  class  BitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    BitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BitAndExpressionContext *> bitAndExpression();
    BitAndExpressionContext* bitAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BitXorExpressionContext* bitXorExpression();

  class  ClosedBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClosedBitAndExpressionContext *closedBitAndExpression();
    std::vector<BitAndExpressionContext *> bitAndExpression();
    BitAndExpressionContext* bitAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedBitXorExpressionContext* closedBitXorExpression();

  class  BitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    BitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BitAndExpressionContext* bitAndExpression();

  class  ClosedBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClosedShiftExpressionContext *closedShiftExpression();
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedBitAndExpressionContext* closedBitAndExpression();

  class  ShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    std::vector<ClosedAdditiveExpressionContext *> closedAdditiveExpression();
    ClosedAdditiveExpressionContext* closedAdditiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShiftExpressionContext* shiftExpression();

  class  ClosedShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ClosedAdditiveExpressionContext *> closedAdditiveExpression();
    ClosedAdditiveExpressionContext* closedAdditiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedShiftExpressionContext* closedShiftExpression();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  ClosedAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClosedMultiplicativeExpressionContext *closedMultiplicativeExpression();
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedAdditiveExpressionContext* closedAdditiveExpression();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CastExpressionContext *> castExpression();
    CastExpressionContext* castExpression(size_t i);
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  ClosedMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClosedCastExpressionContext *closedCastExpression();
    std::vector<CastExpressionContext *> castExpression();
    CastExpressionContext* castExpression(size_t i);
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedMultiplicativeExpressionContext* closedMultiplicativeExpression();

  class  CastExpressionContext : public antlr4::ParserRuleContext {
  public:
    CastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExpressionContext *unaryExpression();
    std::vector<antlr4::tree::TerminalNode *> AS();
    antlr4::tree::TerminalNode* AS(size_t i);
    std::vector<TypeRefContext *> typeRef();
    TypeRefContext* typeRef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CastExpressionContext* castExpression();

  class  ClosedCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    ClosedCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExpressionContext *unaryExpression();
    CastExpressionContext *castExpression();
    antlr4::tree::TerminalNode *AS();
    ClosedCastTypeContext *closedCastType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosedCastExpressionContext* closedCastExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryOperatorContext *unaryOperator();
    UnaryExpressionContext *unaryExpression();
    PostfixExpressionContext *postfixExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  PostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    PostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    std::vector<PostfixSuffixContext *> postfixSuffix();
    PostfixSuffixContext* postfixSuffix(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PostfixExpressionContext* postfixExpression();

  class  ConditionExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionAssignmentExpressionContext *conditionAssignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionExpressionContext* conditionExpression();

  class  ConditionAssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionAssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionLogicalOrExpressionContext *conditionLogicalOrExpression();
    AssignmentOperatorContext *assignmentOperator();
    ConditionExpressionContext *conditionExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionAssignmentExpressionContext* conditionAssignmentExpression();

  class  ConditionLogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionLogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionLogicalAndExpressionContext *> conditionLogicalAndExpression();
    ConditionLogicalAndExpressionContext* conditionLogicalAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OROR();
    antlr4::tree::TerminalNode* OROR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionLogicalOrExpressionContext* conditionLogicalOrExpression();

  class  ConditionLogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionLogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionComparisonExpressionContext *> conditionComparisonExpression();
    ConditionComparisonExpressionContext* conditionComparisonExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ANDAND();
    antlr4::tree::TerminalNode* ANDAND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionLogicalAndExpressionContext* conditionLogicalAndExpression();

  class  ConditionComparisonExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionComparisonExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionBitOrExpressionContext *> conditionBitOrExpression();
    ConditionBitOrExpressionContext* conditionBitOrExpression(size_t i);
    ComparisonExceptLtContext *comparisonExceptLt();
    ConditionClosedBitOrExpressionContext *conditionClosedBitOrExpression();
    antlr4::tree::TerminalNode *LT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionComparisonExpressionContext* conditionComparisonExpression();

  class  ConditionBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionBitXorExpressionContext *> conditionBitXorExpression();
    ConditionBitXorExpressionContext* conditionBitXorExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBitOrExpressionContext* conditionBitOrExpression();

  class  ConditionClosedBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionClosedBitXorExpressionContext *conditionClosedBitXorExpression();
    std::vector<ConditionBitXorExpressionContext *> conditionBitXorExpression();
    ConditionBitXorExpressionContext* conditionBitXorExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedBitOrExpressionContext* conditionClosedBitOrExpression();

  class  ConditionBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionBitAndExpressionContext *> conditionBitAndExpression();
    ConditionBitAndExpressionContext* conditionBitAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBitXorExpressionContext* conditionBitXorExpression();

  class  ConditionClosedBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionClosedBitAndExpressionContext *conditionClosedBitAndExpression();
    std::vector<ConditionBitAndExpressionContext *> conditionBitAndExpression();
    ConditionBitAndExpressionContext* conditionBitAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedBitXorExpressionContext* conditionClosedBitXorExpression();

  class  ConditionBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionShiftExpressionContext *> conditionShiftExpression();
    ConditionShiftExpressionContext* conditionShiftExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBitAndExpressionContext* conditionBitAndExpression();

  class  ConditionClosedBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionClosedShiftExpressionContext *conditionClosedShiftExpression();
    std::vector<ConditionShiftExpressionContext *> conditionShiftExpression();
    ConditionShiftExpressionContext* conditionShiftExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedBitAndExpressionContext* conditionClosedBitAndExpression();

  class  ConditionShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionAdditiveExpressionContext *> conditionAdditiveExpression();
    ConditionAdditiveExpressionContext* conditionAdditiveExpression(size_t i);
    std::vector<ConditionClosedAdditiveExpressionContext *> conditionClosedAdditiveExpression();
    ConditionClosedAdditiveExpressionContext* conditionClosedAdditiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionShiftExpressionContext* conditionShiftExpression();

  class  ConditionClosedShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionClosedAdditiveExpressionContext *> conditionClosedAdditiveExpression();
    ConditionClosedAdditiveExpressionContext* conditionClosedAdditiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    std::vector<ConditionAdditiveExpressionContext *> conditionAdditiveExpression();
    ConditionAdditiveExpressionContext* conditionAdditiveExpression(size_t i);
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedShiftExpressionContext* conditionClosedShiftExpression();

  class  ConditionAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionMultiplicativeExpressionContext *> conditionMultiplicativeExpression();
    ConditionMultiplicativeExpressionContext* conditionMultiplicativeExpression(size_t i);
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionAdditiveExpressionContext* conditionAdditiveExpression();

  class  ConditionClosedAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionClosedMultiplicativeExpressionContext *conditionClosedMultiplicativeExpression();
    std::vector<ConditionMultiplicativeExpressionContext *> conditionMultiplicativeExpression();
    ConditionMultiplicativeExpressionContext* conditionMultiplicativeExpression(size_t i);
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedAdditiveExpressionContext* conditionClosedAdditiveExpression();

  class  ConditionMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionCastExpressionContext *> conditionCastExpression();
    ConditionCastExpressionContext* conditionCastExpression(size_t i);
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionMultiplicativeExpressionContext* conditionMultiplicativeExpression();

  class  ConditionClosedMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionClosedCastExpressionContext *conditionClosedCastExpression();
    std::vector<ConditionCastExpressionContext *> conditionCastExpression();
    ConditionCastExpressionContext* conditionCastExpression(size_t i);
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedMultiplicativeExpressionContext* conditionClosedMultiplicativeExpression();

  class  ConditionCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionUnaryExpressionContext *conditionUnaryExpression();
    std::vector<antlr4::tree::TerminalNode *> AS();
    antlr4::tree::TerminalNode* AS(size_t i);
    std::vector<TypeRefContext *> typeRef();
    TypeRefContext* typeRef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionCastExpressionContext* conditionCastExpression();

  class  ConditionClosedCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionClosedCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionUnaryExpressionContext *conditionUnaryExpression();
    ConditionCastExpressionContext *conditionCastExpression();
    antlr4::tree::TerminalNode *AS();
    ClosedCastTypeContext *closedCastType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionClosedCastExpressionContext* conditionClosedCastExpression();

  class  ConditionUnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionUnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryOperatorContext *unaryOperator();
    ConditionUnaryExpressionContext *conditionUnaryExpression();
    ConditionPostfixExpressionContext *conditionPostfixExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionUnaryExpressionContext* conditionUnaryExpression();

  class  ConditionPostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionPostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionPrimaryContext *conditionPrimary();
    std::vector<PostfixSuffixContext *> postfixSuffix();
    PostfixSuffixContext* postfixSuffix(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionPostfixExpressionContext* conditionPostfixExpression();

  class  ConditionBreakExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakAssignmentExpressionContext *conditionBreakAssignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakExpressionContext* conditionBreakExpression();

  class  ConditionBreakAssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakAssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakLogicalOrExpressionContext *conditionBreakLogicalOrExpression();
    AssignmentOperatorContext *assignmentOperator();
    ConditionExpressionContext *conditionExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakAssignmentExpressionContext* conditionBreakAssignmentExpression();

  class  ConditionBreakLogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakLogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakLogicalAndExpressionContext *conditionBreakLogicalAndExpression();
    std::vector<antlr4::tree::TerminalNode *> OROR();
    antlr4::tree::TerminalNode* OROR(size_t i);
    std::vector<ConditionLogicalAndExpressionContext *> conditionLogicalAndExpression();
    ConditionLogicalAndExpressionContext* conditionLogicalAndExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakLogicalOrExpressionContext* conditionBreakLogicalOrExpression();

  class  ConditionBreakLogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakLogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakComparisonExpressionContext *conditionBreakComparisonExpression();
    std::vector<antlr4::tree::TerminalNode *> ANDAND();
    antlr4::tree::TerminalNode* ANDAND(size_t i);
    std::vector<ConditionComparisonExpressionContext *> conditionComparisonExpression();
    ConditionComparisonExpressionContext* conditionComparisonExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakLogicalAndExpressionContext* conditionBreakLogicalAndExpression();

  class  ConditionBreakComparisonExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakComparisonExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakBitOrExpressionContext *conditionBreakBitOrExpression();
    ComparisonExceptLtContext *comparisonExceptLt();
    ConditionBitOrExpressionContext *conditionBitOrExpression();
    ConditionBreakClosedBitOrExpressionContext *conditionBreakClosedBitOrExpression();
    antlr4::tree::TerminalNode *LT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakComparisonExpressionContext* conditionBreakComparisonExpression();

  class  ConditionBreakBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakBitXorExpressionContext *conditionBreakBitXorExpression();
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    std::vector<ConditionBitXorExpressionContext *> conditionBitXorExpression();
    ConditionBitXorExpressionContext* conditionBitXorExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakBitOrExpressionContext* conditionBreakBitOrExpression();

  class  ConditionBreakClosedBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakClosedBitXorExpressionContext *conditionBreakClosedBitXorExpression();
    ConditionBreakBitXorExpressionContext *conditionBreakBitXorExpression();
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    ConditionClosedBitXorExpressionContext *conditionClosedBitXorExpression();
    std::vector<ConditionBitXorExpressionContext *> conditionBitXorExpression();
    ConditionBitXorExpressionContext* conditionBitXorExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedBitOrExpressionContext* conditionBreakClosedBitOrExpression();

  class  ConditionBreakBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakBitAndExpressionContext *conditionBreakBitAndExpression();
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);
    std::vector<ConditionBitAndExpressionContext *> conditionBitAndExpression();
    ConditionBitAndExpressionContext* conditionBitAndExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakBitXorExpressionContext* conditionBreakBitXorExpression();

  class  ConditionBreakClosedBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakClosedBitAndExpressionContext *conditionBreakClosedBitAndExpression();
    ConditionBreakBitAndExpressionContext *conditionBreakBitAndExpression();
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);
    ConditionClosedBitAndExpressionContext *conditionClosedBitAndExpression();
    std::vector<ConditionBitAndExpressionContext *> conditionBitAndExpression();
    ConditionBitAndExpressionContext* conditionBitAndExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedBitXorExpressionContext* conditionBreakClosedBitXorExpression();

  class  ConditionBreakBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakShiftExpressionContext *conditionBreakShiftExpression();
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);
    std::vector<ConditionShiftExpressionContext *> conditionShiftExpression();
    ConditionShiftExpressionContext* conditionShiftExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakBitAndExpressionContext* conditionBreakBitAndExpression();

  class  ConditionBreakClosedBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakClosedShiftExpressionContext *conditionBreakClosedShiftExpression();
    ConditionBreakShiftExpressionContext *conditionBreakShiftExpression();
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);
    ConditionClosedShiftExpressionContext *conditionClosedShiftExpression();
    std::vector<ConditionShiftExpressionContext *> conditionShiftExpression();
    ConditionShiftExpressionContext* conditionShiftExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedBitAndExpressionContext* conditionBreakClosedBitAndExpression();

  class  ConditionBreakShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakAdditiveExpressionContext *conditionBreakAdditiveExpression();
    std::vector<ConditionAdditiveExpressionContext *> conditionAdditiveExpression();
    ConditionAdditiveExpressionContext* conditionAdditiveExpression(size_t i);
    ConditionBreakClosedAdditiveExpressionContext *conditionBreakClosedAdditiveExpression();
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);
    std::vector<ConditionClosedAdditiveExpressionContext *> conditionClosedAdditiveExpression();
    ConditionClosedAdditiveExpressionContext* conditionClosedAdditiveExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakShiftExpressionContext* conditionBreakShiftExpression();

  class  ConditionBreakClosedShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakClosedAdditiveExpressionContext *conditionBreakClosedAdditiveExpression();
    std::vector<ConditionClosedAdditiveExpressionContext *> conditionClosedAdditiveExpression();
    ConditionClosedAdditiveExpressionContext* conditionClosedAdditiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    ConditionBreakAdditiveExpressionContext *conditionBreakAdditiveExpression();
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);
    std::vector<ConditionAdditiveExpressionContext *> conditionAdditiveExpression();
    ConditionAdditiveExpressionContext* conditionAdditiveExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedShiftExpressionContext* conditionBreakClosedShiftExpression();

  class  ConditionBreakAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakMultiplicativeExpressionContext *conditionBreakMultiplicativeExpression();
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);
    std::vector<ConditionMultiplicativeExpressionContext *> conditionMultiplicativeExpression();
    ConditionMultiplicativeExpressionContext* conditionMultiplicativeExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakAdditiveExpressionContext* conditionBreakAdditiveExpression();

  class  ConditionBreakClosedAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakClosedMultiplicativeExpressionContext *conditionBreakClosedMultiplicativeExpression();
    ConditionBreakMultiplicativeExpressionContext *conditionBreakMultiplicativeExpression();
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);
    ConditionClosedMultiplicativeExpressionContext *conditionClosedMultiplicativeExpression();
    std::vector<ConditionMultiplicativeExpressionContext *> conditionMultiplicativeExpression();
    ConditionMultiplicativeExpressionContext* conditionMultiplicativeExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedAdditiveExpressionContext* conditionBreakClosedAdditiveExpression();

  class  ConditionBreakMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakCastExpressionContext *conditionBreakCastExpression();
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);
    std::vector<ConditionCastExpressionContext *> conditionCastExpression();
    ConditionCastExpressionContext* conditionCastExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakMultiplicativeExpressionContext* conditionBreakMultiplicativeExpression();

  class  ConditionBreakClosedMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakClosedCastExpressionContext *conditionBreakClosedCastExpression();
    ConditionBreakCastExpressionContext *conditionBreakCastExpression();
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);
    ConditionClosedCastExpressionContext *conditionClosedCastExpression();
    std::vector<ConditionCastExpressionContext *> conditionCastExpression();
    ConditionCastExpressionContext* conditionCastExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedMultiplicativeExpressionContext* conditionBreakClosedMultiplicativeExpression();

  class  ConditionBreakCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakUnaryExpressionContext *conditionBreakUnaryExpression();
    std::vector<antlr4::tree::TerminalNode *> AS();
    antlr4::tree::TerminalNode* AS(size_t i);
    std::vector<TypeRefContext *> typeRef();
    TypeRefContext* typeRef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakCastExpressionContext* conditionBreakCastExpression();

  class  ConditionBreakClosedCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakClosedCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionBreakUnaryExpressionContext *conditionBreakUnaryExpression();
    ConditionBreakCastExpressionContext *conditionBreakCastExpression();
    antlr4::tree::TerminalNode *AS();
    ClosedCastTypeContext *closedCastType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakClosedCastExpressionContext* conditionBreakClosedCastExpression();

  class  ConditionBreakUnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakUnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryOperatorContext *unaryOperator();
    ConditionUnaryExpressionContext *conditionUnaryExpression();
    ConditionBreakPostfixExpressionContext *conditionBreakPostfixExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakUnaryExpressionContext* conditionBreakUnaryExpression();

  class  ConditionBreakPostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionBreakPostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionPrimaryWithoutBareBlockContext *conditionPrimaryWithoutBareBlock();
    std::vector<PostfixSuffixContext *> postfixSuffix();
    PostfixSuffixContext* postfixSuffix(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionBreakPostfixExpressionContext* conditionBreakPostfixExpression();

  class  StatementExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementAssignmentExpressionContext *statementAssignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementExpressionContext* statementExpression();

  class  StatementAssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementAssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementLogicalOrExpressionContext *statementLogicalOrExpression();
    AssignmentOperatorContext *assignmentOperator();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementAssignmentExpressionContext* statementAssignmentExpression();

  class  StatementLogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementLogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementLogicalAndExpressionContext *statementLogicalAndExpression();
    std::vector<antlr4::tree::TerminalNode *> OROR();
    antlr4::tree::TerminalNode* OROR(size_t i);
    std::vector<LogicalAndExpressionContext *> logicalAndExpression();
    LogicalAndExpressionContext* logicalAndExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementLogicalOrExpressionContext* statementLogicalOrExpression();

  class  StatementLogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementLogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementComparisonExpressionContext *statementComparisonExpression();
    std::vector<antlr4::tree::TerminalNode *> ANDAND();
    antlr4::tree::TerminalNode* ANDAND(size_t i);
    std::vector<ComparisonExpressionContext *> comparisonExpression();
    ComparisonExpressionContext* comparisonExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementLogicalAndExpressionContext* statementLogicalAndExpression();

  class  StatementComparisonExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementComparisonExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementBitOrExpressionContext *statementBitOrExpression();
    ComparisonExceptLtContext *comparisonExceptLt();
    BitOrExpressionContext *bitOrExpression();
    StatementClosedBitOrExpressionContext *statementClosedBitOrExpression();
    antlr4::tree::TerminalNode *LT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementComparisonExpressionContext* statementComparisonExpression();

  class  StatementBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementBitXorExpressionContext *statementBitXorExpression();
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    std::vector<BitXorExpressionContext *> bitXorExpression();
    BitXorExpressionContext* bitXorExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementBitOrExpressionContext* statementBitOrExpression();

  class  StatementClosedBitOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedBitOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementClosedBitXorExpressionContext *statementClosedBitXorExpression();
    StatementBitXorExpressionContext *statementBitXorExpression();
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    ClosedBitXorExpressionContext *closedBitXorExpression();
    std::vector<BitXorExpressionContext *> bitXorExpression();
    BitXorExpressionContext* bitXorExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedBitOrExpressionContext* statementClosedBitOrExpression();

  class  StatementBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementBitAndExpressionContext *statementBitAndExpression();
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);
    std::vector<BitAndExpressionContext *> bitAndExpression();
    BitAndExpressionContext* bitAndExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementBitXorExpressionContext* statementBitXorExpression();

  class  StatementClosedBitXorExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedBitXorExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementClosedBitAndExpressionContext *statementClosedBitAndExpression();
    StatementBitAndExpressionContext *statementBitAndExpression();
    std::vector<antlr4::tree::TerminalNode *> CARET();
    antlr4::tree::TerminalNode* CARET(size_t i);
    ClosedBitAndExpressionContext *closedBitAndExpression();
    std::vector<BitAndExpressionContext *> bitAndExpression();
    BitAndExpressionContext* bitAndExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedBitXorExpressionContext* statementClosedBitXorExpression();

  class  StatementBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementShiftExpressionContext *statementShiftExpression();
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementBitAndExpressionContext* statementBitAndExpression();

  class  StatementClosedBitAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedBitAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementClosedShiftExpressionContext *statementClosedShiftExpression();
    StatementShiftExpressionContext *statementShiftExpression();
    std::vector<antlr4::tree::TerminalNode *> AMP();
    antlr4::tree::TerminalNode* AMP(size_t i);
    ClosedShiftExpressionContext *closedShiftExpression();
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedBitAndExpressionContext* statementClosedBitAndExpression();

  class  StatementShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementAdditiveExpressionContext *statementAdditiveExpression();
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    StatementClosedAdditiveExpressionContext *statementClosedAdditiveExpression();
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);
    std::vector<ClosedAdditiveExpressionContext *> closedAdditiveExpression();
    ClosedAdditiveExpressionContext* closedAdditiveExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementShiftExpressionContext* statementShiftExpression();

  class  StatementClosedShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementClosedAdditiveExpressionContext *statementClosedAdditiveExpression();
    std::vector<ClosedAdditiveExpressionContext *> closedAdditiveExpression();
    ClosedAdditiveExpressionContext* closedAdditiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SHL();
    antlr4::tree::TerminalNode* SHL(size_t i);
    StatementAdditiveExpressionContext *statementAdditiveExpression();
    std::vector<ShiftRightContext *> shiftRight();
    ShiftRightContext* shiftRight(size_t i);
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedShiftExpressionContext* statementClosedShiftExpression();

  class  StatementAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementMultiplicativeExpressionContext *statementMultiplicativeExpression();
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementAdditiveExpressionContext* statementAdditiveExpression();

  class  StatementClosedAdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedAdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementClosedMultiplicativeExpressionContext *statementClosedMultiplicativeExpression();
    StatementMultiplicativeExpressionContext *statementMultiplicativeExpression();
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);
    ClosedMultiplicativeExpressionContext *closedMultiplicativeExpression();
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedAdditiveExpressionContext* statementClosedAdditiveExpression();

  class  StatementMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementCastExpressionContext *statementCastExpression();
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);
    std::vector<CastExpressionContext *> castExpression();
    CastExpressionContext* castExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementMultiplicativeExpressionContext* statementMultiplicativeExpression();

  class  StatementClosedMultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedMultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementClosedCastExpressionContext *statementClosedCastExpression();
    StatementCastExpressionContext *statementCastExpression();
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);
    ClosedCastExpressionContext *closedCastExpression();
    std::vector<CastExpressionContext *> castExpression();
    CastExpressionContext* castExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedMultiplicativeExpressionContext* statementClosedMultiplicativeExpression();

  class  StatementCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementUnaryExpressionContext *statementUnaryExpression();
    std::vector<antlr4::tree::TerminalNode *> AS();
    antlr4::tree::TerminalNode* AS(size_t i);
    std::vector<TypeRefContext *> typeRef();
    TypeRefContext* typeRef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementCastExpressionContext* statementCastExpression();

  class  StatementClosedCastExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementClosedCastExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementUnaryExpressionContext *statementUnaryExpression();
    StatementCastExpressionContext *statementCastExpression();
    antlr4::tree::TerminalNode *AS();
    ClosedCastTypeContext *closedCastType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementClosedCastExpressionContext* statementClosedCastExpression();

  class  StatementUnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementUnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryOperatorContext *unaryOperator();
    UnaryExpressionContext *unaryExpression();
    StatementPostfixExpressionContext *statementPostfixExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementUnaryExpressionContext* statementUnaryExpression();

  class  StatementPostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    StatementPostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NonBlockPrimaryContext *nonBlockPrimary();
    std::vector<PostfixSuffixContext *> postfixSuffix();
    PostfixSuffixContext* postfixSuffix(size_t i);
    ExpressionWithBlockContext *expressionWithBlock();
    DotSuffixContext *dotSuffix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementPostfixExpressionContext* statementPostfixExpression();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NonBlockPrimaryContext *nonBlockPrimary();
    ExpressionWithBlockContext *expressionWithBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  NonBlockPrimaryContext : public antlr4::ParserRuleContext {
  public:
    NonBlockPrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralExpressionContext *literalExpression();
    PathInExpressionContext *pathInExpression();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    StructExprFieldsContext *structExprFields();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionContext *expression();
    ArrayExpressionContext *arrayExpression();
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *CONTINUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonBlockPrimaryContext* nonBlockPrimary();

  class  ConditionPrimaryContext : public antlr4::ParserRuleContext {
  public:
    ConditionPrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionPrimaryWithoutBareBlockContext *conditionPrimaryWithoutBareBlock();
    BlockExpressionContext *blockExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionPrimaryContext* conditionPrimary();

  class  ConditionPrimaryWithoutBareBlockContext : public antlr4::ParserRuleContext {
  public:
    ConditionPrimaryWithoutBareBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralExpressionContext *literalExpression();
    PathInExpressionContext *pathInExpression();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionContext *expression();
    ArrayExpressionContext *arrayExpression();
    IfExpressionContext *ifExpression();
    antlr4::tree::TerminalNode *LOOP();
    BlockExpressionContext *blockExpression();
    antlr4::tree::TerminalNode *WHILE();
    ConditionExpressionContext *conditionExpression();
    antlr4::tree::TerminalNode *BREAK();
    ConditionBreakExpressionContext *conditionBreakExpression();
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *CONTINUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionPrimaryWithoutBareBlockContext* conditionPrimaryWithoutBareBlock();

  class  LiteralExpressionContext : public antlr4::ParserRuleContext {
  public:
    LiteralExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_LITERAL();
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralExpressionContext* literalExpression();

  class  StructExprFieldsContext : public antlr4::ParserRuleContext {
  public:
    StructExprFieldsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructExprFieldContext *> structExprField();
    StructExprFieldContext* structExprField(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructExprFieldsContext* structExprFields();

  class  StructExprFieldContext : public antlr4::ParserRuleContext {
  public:
    StructExprFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructExprFieldContext* structExprField();

  class  ArrayExpressionContext : public antlr4::ParserRuleContext {
  public:
    ArrayExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *SEMI();
    ConstValueContext *constValue();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayExpressionContext* arrayExpression();

  class  PostfixSuffixContext : public antlr4::ParserRuleContext {
  public:
    PostfixSuffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CallArgumentsContext *callArguments();
    antlr4::tree::TerminalNode *LBRACKET();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACKET();
    DotSuffixContext *dotSuffix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PostfixSuffixContext* postfixSuffix();

  class  DotSuffixContext : public antlr4::ParserRuleContext {
  public:
    DotSuffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    PathExprSegmentContext *pathExprSegment();
    CallArgumentsContext *callArguments();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DotSuffixContext* dotSuffix();

  class  CallArgumentsContext : public antlr4::ParserRuleContext {
  public:
    CallArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallArgumentsContext* callArguments();

  class  UnaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    UnaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *AMP();
    antlr4::tree::TerminalNode *ANDAND();
    antlr4::tree::TerminalNode *MUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryOperatorContext* unaryOperator();

  class  MultiplicativeOperatorContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PERCENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeOperatorContext* multiplicativeOperator();

  class  AdditiveOperatorContext : public antlr4::ParserRuleContext {
  public:
    AdditiveOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveOperatorContext* additiveOperator();

  class  ShiftRightContext : public antlr4::ParserRuleContext {
  public:
    ShiftRightContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GT_SECOND();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShiftRightContext* shiftRight();

  class  ComparisonExceptLtContext : public antlr4::ParserRuleContext {
  public:
    ComparisonExceptLtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQEQ();
    antlr4::tree::TerminalNode *NE();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GE_EQ();
    antlr4::tree::TerminalNode *GT_SECOND();
    antlr4::tree::TerminalNode *SHR_EQ();
    GenericCloseContext *genericClose();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonExceptLtContext* comparisonExceptLt();

  class  AssignmentOperatorContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EqualsSignContext *equalsSign();
    antlr4::tree::TerminalNode *PLUS_ASSIGN();
    antlr4::tree::TerminalNode *MINUS_ASSIGN();
    antlr4::tree::TerminalNode *STAR_ASSIGN();
    antlr4::tree::TerminalNode *SLASH_ASSIGN();
    antlr4::tree::TerminalNode *PERCENT_ASSIGN();
    antlr4::tree::TerminalNode *AMP_ASSIGN();
    antlr4::tree::TerminalNode *PIPE_ASSIGN();
    antlr4::tree::TerminalNode *CARET_ASSIGN();
    antlr4::tree::TerminalNode *SHL_ASSIGN();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GT_SECOND();
    antlr4::tree::TerminalNode *SHR_EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentOperatorContext* assignmentOperator();

  class  EqualsSignContext : public antlr4::ParserRuleContext {
  public:
    EqualsSignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *GE_EQ();
    antlr4::tree::TerminalNode *SHR_EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualsSignContext* equalsSign();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DERIVE();
    antlr4::tree::TerminalNode *COPY();
    antlr4::tree::TerminalNode *CLONE();
    antlr4::tree::TerminalNode *PARTIAL_EQ();
    antlr4::tree::TerminalNode *EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace rx
