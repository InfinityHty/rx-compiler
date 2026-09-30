
// Generated from Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ParserVisitor.h"


namespace rx {

/**
 * This class provides an empty implementation of ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ParserBaseVisitor : public ParserVisitor {
public:

  virtual std::any visitCrate(Parser::CrateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem(Parser::ItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUseDeclaration(Parser::UseDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUseTree(Parser::UseTreeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsePath(Parser::UsePathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsePathSegment(Parser::UsePathSegmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(Parser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionParameters(Parser::FunctionParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelfParam(Parser::SelfParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionParam(Parser::FunctionParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructDefinition(Parser::StructDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructField(Parser::StructFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOuterAttribute(Parser::OuterAttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeriveName(Parser::DeriveNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantItem(Parser::ConstantItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInherentImpl(Parser::InherentImplContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociatedItem(Parser::AssociatedItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericParams(Parser::GenericParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLifetimeParam(Parser::LifetimeParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLifetime(Parser::LifetimeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLifetimeBounds(Parser::LifetimeBoundsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeParamBounds(Parser::TypeParamBoundsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhereClause(Parser::WhereClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhereClauseItem(Parser::WhereClauseItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeRef(Parser::TypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReferenceType(Parser::ReferenceTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(Parser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypePath(Parser::TypePathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypePathSegment(Parser::TypePathSegmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathInExpression(Parser::PathInExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathExprSegment(Parser::PathExprSegmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathIdentSegment(Parser::PathIdentSegmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericArgs(Parser::GenericArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericArg(Parser::GenericArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericClose(Parser::GenericCloseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedCastType(Parser::ClosedCastTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstValue(Parser::ConstValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMagnitude(Parser::MagnitudeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierBinding(Parser::IdentifierBindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLetStatement(Parser::LetStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockExpression(Parser::BlockExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(Parser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionWithBlock(Parser::ExpressionWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfExpression(Parser::IfExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(Parser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentExpression(Parser::AssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(Parser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(Parser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonExpression(Parser::ComparisonExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitOrExpression(Parser::BitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedBitOrExpression(Parser::ClosedBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitXorExpression(Parser::BitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedBitXorExpression(Parser::ClosedBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitAndExpression(Parser::BitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedBitAndExpression(Parser::ClosedBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftExpression(Parser::ShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedShiftExpression(Parser::ClosedShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(Parser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedAdditiveExpression(Parser::ClosedAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(Parser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedMultiplicativeExpression(Parser::ClosedMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCastExpression(Parser::CastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosedCastExpression(Parser::ClosedCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(Parser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixExpression(Parser::PostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionExpression(Parser::ConditionExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionAssignmentExpression(Parser::ConditionAssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionLogicalOrExpression(Parser::ConditionLogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionLogicalAndExpression(Parser::ConditionLogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionComparisonExpression(Parser::ConditionComparisonExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBitOrExpression(Parser::ConditionBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedBitOrExpression(Parser::ConditionClosedBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBitXorExpression(Parser::ConditionBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedBitXorExpression(Parser::ConditionClosedBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBitAndExpression(Parser::ConditionBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedBitAndExpression(Parser::ConditionClosedBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionShiftExpression(Parser::ConditionShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedShiftExpression(Parser::ConditionClosedShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionAdditiveExpression(Parser::ConditionAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedAdditiveExpression(Parser::ConditionClosedAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionMultiplicativeExpression(Parser::ConditionMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedMultiplicativeExpression(Parser::ConditionClosedMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionCastExpression(Parser::ConditionCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionClosedCastExpression(Parser::ConditionClosedCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionUnaryExpression(Parser::ConditionUnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionPostfixExpression(Parser::ConditionPostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakExpression(Parser::ConditionBreakExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakAssignmentExpression(Parser::ConditionBreakAssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakLogicalOrExpression(Parser::ConditionBreakLogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakLogicalAndExpression(Parser::ConditionBreakLogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakComparisonExpression(Parser::ConditionBreakComparisonExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakBitOrExpression(Parser::ConditionBreakBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedBitOrExpression(Parser::ConditionBreakClosedBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakBitXorExpression(Parser::ConditionBreakBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedBitXorExpression(Parser::ConditionBreakClosedBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakBitAndExpression(Parser::ConditionBreakBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedBitAndExpression(Parser::ConditionBreakClosedBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakShiftExpression(Parser::ConditionBreakShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedShiftExpression(Parser::ConditionBreakClosedShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakAdditiveExpression(Parser::ConditionBreakAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedAdditiveExpression(Parser::ConditionBreakClosedAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakMultiplicativeExpression(Parser::ConditionBreakMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedMultiplicativeExpression(Parser::ConditionBreakClosedMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakCastExpression(Parser::ConditionBreakCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakClosedCastExpression(Parser::ConditionBreakClosedCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakUnaryExpression(Parser::ConditionBreakUnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionBreakPostfixExpression(Parser::ConditionBreakPostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementExpression(Parser::StatementExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementAssignmentExpression(Parser::StatementAssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementLogicalOrExpression(Parser::StatementLogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementLogicalAndExpression(Parser::StatementLogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementComparisonExpression(Parser::StatementComparisonExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementBitOrExpression(Parser::StatementBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedBitOrExpression(Parser::StatementClosedBitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementBitXorExpression(Parser::StatementBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedBitXorExpression(Parser::StatementClosedBitXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementBitAndExpression(Parser::StatementBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedBitAndExpression(Parser::StatementClosedBitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementShiftExpression(Parser::StatementShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedShiftExpression(Parser::StatementClosedShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementAdditiveExpression(Parser::StatementAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedAdditiveExpression(Parser::StatementClosedAdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementMultiplicativeExpression(Parser::StatementMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedMultiplicativeExpression(Parser::StatementClosedMultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementCastExpression(Parser::StatementCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementClosedCastExpression(Parser::StatementClosedCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementUnaryExpression(Parser::StatementUnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementPostfixExpression(Parser::StatementPostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(Parser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonBlockPrimary(Parser::NonBlockPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionPrimary(Parser::ConditionPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionPrimaryWithoutBareBlock(Parser::ConditionPrimaryWithoutBareBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpression(Parser::LiteralExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructExprFields(Parser::StructExprFieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructExprField(Parser::StructExprFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayExpression(Parser::ArrayExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixSuffix(Parser::PostfixSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDotSuffix(Parser::DotSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallArguments(Parser::CallArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOperator(Parser::UnaryOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeOperator(Parser::MultiplicativeOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveOperator(Parser::AdditiveOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftRight(Parser::ShiftRightContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonExceptLt(Parser::ComparisonExceptLtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperator(Parser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualsSign(Parser::EqualsSignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(Parser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace rx
