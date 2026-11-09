
// Generated from Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "Parser.h"


namespace rx {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by Parser.
 */
class  ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Parser.
   */
    virtual std::any visitCrate(Parser::CrateContext *context) = 0;

    virtual std::any visitItem(Parser::ItemContext *context) = 0;

    virtual std::any visitUseDeclaration(Parser::UseDeclarationContext *context) = 0;

    virtual std::any visitUseTree(Parser::UseTreeContext *context) = 0;

    virtual std::any visitUsePath(Parser::UsePathContext *context) = 0;

    virtual std::any visitUsePathSegment(Parser::UsePathSegmentContext *context) = 0;

    virtual std::any visitFunctionDefinition(Parser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitFunctionParameters(Parser::FunctionParametersContext *context) = 0;

    virtual std::any visitSelfParam(Parser::SelfParamContext *context) = 0;

    virtual std::any visitFunctionParam(Parser::FunctionParamContext *context) = 0;

    virtual std::any visitStructDefinition(Parser::StructDefinitionContext *context) = 0;

    virtual std::any visitStructField(Parser::StructFieldContext *context) = 0;

    virtual std::any visitOuterAttribute(Parser::OuterAttributeContext *context) = 0;

    virtual std::any visitDeriveName(Parser::DeriveNameContext *context) = 0;

    virtual std::any visitConstantItem(Parser::ConstantItemContext *context) = 0;

    virtual std::any visitInherentImpl(Parser::InherentImplContext *context) = 0;

    virtual std::any visitAssociatedItem(Parser::AssociatedItemContext *context) = 0;

    virtual std::any visitGenericParams(Parser::GenericParamsContext *context) = 0;

    virtual std::any visitLifetimeParam(Parser::LifetimeParamContext *context) = 0;

    virtual std::any visitLifetime(Parser::LifetimeContext *context) = 0;

    virtual std::any visitLifetimeBounds(Parser::LifetimeBoundsContext *context) = 0;

    virtual std::any visitTypeParamBounds(Parser::TypeParamBoundsContext *context) = 0;

    virtual std::any visitWhereClause(Parser::WhereClauseContext *context) = 0;

    virtual std::any visitWhereClauseItem(Parser::WhereClauseItemContext *context) = 0;

    virtual std::any visitTypeRef(Parser::TypeRefContext *context) = 0;

    virtual std::any visitReferenceType(Parser::ReferenceTypeContext *context) = 0;

    virtual std::any visitArrayType(Parser::ArrayTypeContext *context) = 0;

    virtual std::any visitTypePath(Parser::TypePathContext *context) = 0;

    virtual std::any visitTypePathSegment(Parser::TypePathSegmentContext *context) = 0;

    virtual std::any visitPathInExpression(Parser::PathInExpressionContext *context) = 0;

    virtual std::any visitPathExprSegment(Parser::PathExprSegmentContext *context) = 0;

    virtual std::any visitPathIdentSegment(Parser::PathIdentSegmentContext *context) = 0;

    virtual std::any visitGenericArgs(Parser::GenericArgsContext *context) = 0;

    virtual std::any visitGenericArg(Parser::GenericArgContext *context) = 0;

    virtual std::any visitGenericClose(Parser::GenericCloseContext *context) = 0;

    virtual std::any visitClosedCastType(Parser::ClosedCastTypeContext *context) = 0;

    virtual std::any visitConstValue(Parser::ConstValueContext *context) = 0;

    virtual std::any visitMagnitude(Parser::MagnitudeContext *context) = 0;

    virtual std::any visitIdentifierBinding(Parser::IdentifierBindingContext *context) = 0;

    virtual std::any visitLetStatement(Parser::LetStatementContext *context) = 0;

    virtual std::any visitBlockExpression(Parser::BlockExpressionContext *context) = 0;

    virtual std::any visitStatement(Parser::StatementContext *context) = 0;

    virtual std::any visitExpressionWithBlock(Parser::ExpressionWithBlockContext *context) = 0;

    virtual std::any visitIfExpression(Parser::IfExpressionContext *context) = 0;

    virtual std::any visitExpression(Parser::ExpressionContext *context) = 0;

    virtual std::any visitAssignmentExpression(Parser::AssignmentExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(Parser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(Parser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitComparisonExpression(Parser::ComparisonExpressionContext *context) = 0;

    virtual std::any visitBitOrExpression(Parser::BitOrExpressionContext *context) = 0;

    virtual std::any visitClosedBitOrExpression(Parser::ClosedBitOrExpressionContext *context) = 0;

    virtual std::any visitBitXorExpression(Parser::BitXorExpressionContext *context) = 0;

    virtual std::any visitClosedBitXorExpression(Parser::ClosedBitXorExpressionContext *context) = 0;

    virtual std::any visitBitAndExpression(Parser::BitAndExpressionContext *context) = 0;

    virtual std::any visitClosedBitAndExpression(Parser::ClosedBitAndExpressionContext *context) = 0;

    virtual std::any visitShiftExpression(Parser::ShiftExpressionContext *context) = 0;

    virtual std::any visitClosedShiftExpression(Parser::ClosedShiftExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(Parser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitClosedAdditiveExpression(Parser::ClosedAdditiveExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(Parser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitClosedMultiplicativeExpression(Parser::ClosedMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitCastExpression(Parser::CastExpressionContext *context) = 0;

    virtual std::any visitClosedCastExpression(Parser::ClosedCastExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(Parser::UnaryExpressionContext *context) = 0;

    virtual std::any visitPostfixExpression(Parser::PostfixExpressionContext *context) = 0;

    virtual std::any visitConditionExpression(Parser::ConditionExpressionContext *context) = 0;

    virtual std::any visitConditionAssignmentExpression(Parser::ConditionAssignmentExpressionContext *context) = 0;

    virtual std::any visitConditionLogicalOrExpression(Parser::ConditionLogicalOrExpressionContext *context) = 0;

    virtual std::any visitConditionLogicalAndExpression(Parser::ConditionLogicalAndExpressionContext *context) = 0;

    virtual std::any visitConditionComparisonExpression(Parser::ConditionComparisonExpressionContext *context) = 0;

    virtual std::any visitConditionBitOrExpression(Parser::ConditionBitOrExpressionContext *context) = 0;

    virtual std::any visitConditionClosedBitOrExpression(Parser::ConditionClosedBitOrExpressionContext *context) = 0;

    virtual std::any visitConditionBitXorExpression(Parser::ConditionBitXorExpressionContext *context) = 0;

    virtual std::any visitConditionClosedBitXorExpression(Parser::ConditionClosedBitXorExpressionContext *context) = 0;

    virtual std::any visitConditionBitAndExpression(Parser::ConditionBitAndExpressionContext *context) = 0;

    virtual std::any visitConditionClosedBitAndExpression(Parser::ConditionClosedBitAndExpressionContext *context) = 0;

    virtual std::any visitConditionShiftExpression(Parser::ConditionShiftExpressionContext *context) = 0;

    virtual std::any visitConditionClosedShiftExpression(Parser::ConditionClosedShiftExpressionContext *context) = 0;

    virtual std::any visitConditionAdditiveExpression(Parser::ConditionAdditiveExpressionContext *context) = 0;

    virtual std::any visitConditionClosedAdditiveExpression(Parser::ConditionClosedAdditiveExpressionContext *context) = 0;

    virtual std::any visitConditionMultiplicativeExpression(Parser::ConditionMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitConditionClosedMultiplicativeExpression(Parser::ConditionClosedMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitConditionCastExpression(Parser::ConditionCastExpressionContext *context) = 0;

    virtual std::any visitConditionClosedCastExpression(Parser::ConditionClosedCastExpressionContext *context) = 0;

    virtual std::any visitConditionUnaryExpression(Parser::ConditionUnaryExpressionContext *context) = 0;

    virtual std::any visitConditionPostfixExpression(Parser::ConditionPostfixExpressionContext *context) = 0;

    virtual std::any visitConditionBreakExpression(Parser::ConditionBreakExpressionContext *context) = 0;

    virtual std::any visitConditionBreakAssignmentExpression(Parser::ConditionBreakAssignmentExpressionContext *context) = 0;

    virtual std::any visitConditionBreakLogicalOrExpression(Parser::ConditionBreakLogicalOrExpressionContext *context) = 0;

    virtual std::any visitConditionBreakLogicalAndExpression(Parser::ConditionBreakLogicalAndExpressionContext *context) = 0;

    virtual std::any visitConditionBreakComparisonExpression(Parser::ConditionBreakComparisonExpressionContext *context) = 0;

    virtual std::any visitConditionBreakBitOrExpression(Parser::ConditionBreakBitOrExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedBitOrExpression(Parser::ConditionBreakClosedBitOrExpressionContext *context) = 0;

    virtual std::any visitConditionBreakBitXorExpression(Parser::ConditionBreakBitXorExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedBitXorExpression(Parser::ConditionBreakClosedBitXorExpressionContext *context) = 0;

    virtual std::any visitConditionBreakBitAndExpression(Parser::ConditionBreakBitAndExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedBitAndExpression(Parser::ConditionBreakClosedBitAndExpressionContext *context) = 0;

    virtual std::any visitConditionBreakShiftExpression(Parser::ConditionBreakShiftExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedShiftExpression(Parser::ConditionBreakClosedShiftExpressionContext *context) = 0;

    virtual std::any visitConditionBreakAdditiveExpression(Parser::ConditionBreakAdditiveExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedAdditiveExpression(Parser::ConditionBreakClosedAdditiveExpressionContext *context) = 0;

    virtual std::any visitConditionBreakMultiplicativeExpression(Parser::ConditionBreakMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedMultiplicativeExpression(Parser::ConditionBreakClosedMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitConditionBreakCastExpression(Parser::ConditionBreakCastExpressionContext *context) = 0;

    virtual std::any visitConditionBreakClosedCastExpression(Parser::ConditionBreakClosedCastExpressionContext *context) = 0;

    virtual std::any visitConditionBreakUnaryExpression(Parser::ConditionBreakUnaryExpressionContext *context) = 0;

    virtual std::any visitConditionBreakPostfixExpression(Parser::ConditionBreakPostfixExpressionContext *context) = 0;

    virtual std::any visitStatementExpression(Parser::StatementExpressionContext *context) = 0;

    virtual std::any visitStatementAssignmentExpression(Parser::StatementAssignmentExpressionContext *context) = 0;

    virtual std::any visitStatementLogicalOrExpression(Parser::StatementLogicalOrExpressionContext *context) = 0;

    virtual std::any visitStatementLogicalAndExpression(Parser::StatementLogicalAndExpressionContext *context) = 0;

    virtual std::any visitStatementComparisonExpression(Parser::StatementComparisonExpressionContext *context) = 0;

    virtual std::any visitStatementBitOrExpression(Parser::StatementBitOrExpressionContext *context) = 0;

    virtual std::any visitStatementClosedBitOrExpression(Parser::StatementClosedBitOrExpressionContext *context) = 0;

    virtual std::any visitStatementBitXorExpression(Parser::StatementBitXorExpressionContext *context) = 0;

    virtual std::any visitStatementClosedBitXorExpression(Parser::StatementClosedBitXorExpressionContext *context) = 0;

    virtual std::any visitStatementBitAndExpression(Parser::StatementBitAndExpressionContext *context) = 0;

    virtual std::any visitStatementClosedBitAndExpression(Parser::StatementClosedBitAndExpressionContext *context) = 0;

    virtual std::any visitStatementShiftExpression(Parser::StatementShiftExpressionContext *context) = 0;

    virtual std::any visitStatementClosedShiftExpression(Parser::StatementClosedShiftExpressionContext *context) = 0;

    virtual std::any visitStatementAdditiveExpression(Parser::StatementAdditiveExpressionContext *context) = 0;

    virtual std::any visitStatementClosedAdditiveExpression(Parser::StatementClosedAdditiveExpressionContext *context) = 0;

    virtual std::any visitStatementMultiplicativeExpression(Parser::StatementMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitStatementClosedMultiplicativeExpression(Parser::StatementClosedMultiplicativeExpressionContext *context) = 0;

    virtual std::any visitStatementCastExpression(Parser::StatementCastExpressionContext *context) = 0;

    virtual std::any visitStatementClosedCastExpression(Parser::StatementClosedCastExpressionContext *context) = 0;

    virtual std::any visitStatementUnaryExpression(Parser::StatementUnaryExpressionContext *context) = 0;

    virtual std::any visitStatementPostfixExpression(Parser::StatementPostfixExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpression(Parser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitNonBlockPrimary(Parser::NonBlockPrimaryContext *context) = 0;

    virtual std::any visitConditionPrimary(Parser::ConditionPrimaryContext *context) = 0;

    virtual std::any visitConditionPrimaryWithoutBareBlock(Parser::ConditionPrimaryWithoutBareBlockContext *context) = 0;

    virtual std::any visitLiteralExpression(Parser::LiteralExpressionContext *context) = 0;

    virtual std::any visitStructExprFields(Parser::StructExprFieldsContext *context) = 0;

    virtual std::any visitStructExprField(Parser::StructExprFieldContext *context) = 0;

    virtual std::any visitArrayExpression(Parser::ArrayExpressionContext *context) = 0;

    virtual std::any visitPostfixSuffix(Parser::PostfixSuffixContext *context) = 0;

    virtual std::any visitDotSuffix(Parser::DotSuffixContext *context) = 0;

    virtual std::any visitCallArguments(Parser::CallArgumentsContext *context) = 0;

    virtual std::any visitUnaryOperator(Parser::UnaryOperatorContext *context) = 0;

    virtual std::any visitMultiplicativeOperator(Parser::MultiplicativeOperatorContext *context) = 0;

    virtual std::any visitAdditiveOperator(Parser::AdditiveOperatorContext *context) = 0;

    virtual std::any visitShiftRight(Parser::ShiftRightContext *context) = 0;

    virtual std::any visitComparisonExceptLt(Parser::ComparisonExceptLtContext *context) = 0;

    virtual std::any visitAssignmentOperator(Parser::AssignmentOperatorContext *context) = 0;

    virtual std::any visitEqualsSign(Parser::EqualsSignContext *context) = 0;

    virtual std::any visitIdentifier(Parser::IdentifierContext *context) = 0;


};

}  // namespace rx
