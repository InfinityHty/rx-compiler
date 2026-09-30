
// Generated from Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "Parser.h"


namespace rx {

/**
 * This interface defines an abstract listener for a parse tree produced by Parser.
 */
class  ParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCrate(Parser::CrateContext *ctx) = 0;
  virtual void exitCrate(Parser::CrateContext *ctx) = 0;

  virtual void enterItem(Parser::ItemContext *ctx) = 0;
  virtual void exitItem(Parser::ItemContext *ctx) = 0;

  virtual void enterUseDeclaration(Parser::UseDeclarationContext *ctx) = 0;
  virtual void exitUseDeclaration(Parser::UseDeclarationContext *ctx) = 0;

  virtual void enterUseTree(Parser::UseTreeContext *ctx) = 0;
  virtual void exitUseTree(Parser::UseTreeContext *ctx) = 0;

  virtual void enterUsePath(Parser::UsePathContext *ctx) = 0;
  virtual void exitUsePath(Parser::UsePathContext *ctx) = 0;

  virtual void enterUsePathSegment(Parser::UsePathSegmentContext *ctx) = 0;
  virtual void exitUsePathSegment(Parser::UsePathSegmentContext *ctx) = 0;

  virtual void enterFunctionDefinition(Parser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(Parser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterFunctionParameters(Parser::FunctionParametersContext *ctx) = 0;
  virtual void exitFunctionParameters(Parser::FunctionParametersContext *ctx) = 0;

  virtual void enterSelfParam(Parser::SelfParamContext *ctx) = 0;
  virtual void exitSelfParam(Parser::SelfParamContext *ctx) = 0;

  virtual void enterFunctionParam(Parser::FunctionParamContext *ctx) = 0;
  virtual void exitFunctionParam(Parser::FunctionParamContext *ctx) = 0;

  virtual void enterStructDefinition(Parser::StructDefinitionContext *ctx) = 0;
  virtual void exitStructDefinition(Parser::StructDefinitionContext *ctx) = 0;

  virtual void enterStructField(Parser::StructFieldContext *ctx) = 0;
  virtual void exitStructField(Parser::StructFieldContext *ctx) = 0;

  virtual void enterOuterAttribute(Parser::OuterAttributeContext *ctx) = 0;
  virtual void exitOuterAttribute(Parser::OuterAttributeContext *ctx) = 0;

  virtual void enterDeriveName(Parser::DeriveNameContext *ctx) = 0;
  virtual void exitDeriveName(Parser::DeriveNameContext *ctx) = 0;

  virtual void enterConstantItem(Parser::ConstantItemContext *ctx) = 0;
  virtual void exitConstantItem(Parser::ConstantItemContext *ctx) = 0;

  virtual void enterInherentImpl(Parser::InherentImplContext *ctx) = 0;
  virtual void exitInherentImpl(Parser::InherentImplContext *ctx) = 0;

  virtual void enterAssociatedItem(Parser::AssociatedItemContext *ctx) = 0;
  virtual void exitAssociatedItem(Parser::AssociatedItemContext *ctx) = 0;

  virtual void enterGenericParams(Parser::GenericParamsContext *ctx) = 0;
  virtual void exitGenericParams(Parser::GenericParamsContext *ctx) = 0;

  virtual void enterLifetimeParam(Parser::LifetimeParamContext *ctx) = 0;
  virtual void exitLifetimeParam(Parser::LifetimeParamContext *ctx) = 0;

  virtual void enterLifetime(Parser::LifetimeContext *ctx) = 0;
  virtual void exitLifetime(Parser::LifetimeContext *ctx) = 0;

  virtual void enterLifetimeBounds(Parser::LifetimeBoundsContext *ctx) = 0;
  virtual void exitLifetimeBounds(Parser::LifetimeBoundsContext *ctx) = 0;

  virtual void enterTypeParamBounds(Parser::TypeParamBoundsContext *ctx) = 0;
  virtual void exitTypeParamBounds(Parser::TypeParamBoundsContext *ctx) = 0;

  virtual void enterWhereClause(Parser::WhereClauseContext *ctx) = 0;
  virtual void exitWhereClause(Parser::WhereClauseContext *ctx) = 0;

  virtual void enterWhereClauseItem(Parser::WhereClauseItemContext *ctx) = 0;
  virtual void exitWhereClauseItem(Parser::WhereClauseItemContext *ctx) = 0;

  virtual void enterTypeRef(Parser::TypeRefContext *ctx) = 0;
  virtual void exitTypeRef(Parser::TypeRefContext *ctx) = 0;

  virtual void enterReferenceType(Parser::ReferenceTypeContext *ctx) = 0;
  virtual void exitReferenceType(Parser::ReferenceTypeContext *ctx) = 0;

  virtual void enterArrayType(Parser::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(Parser::ArrayTypeContext *ctx) = 0;

  virtual void enterTypePath(Parser::TypePathContext *ctx) = 0;
  virtual void exitTypePath(Parser::TypePathContext *ctx) = 0;

  virtual void enterTypePathSegment(Parser::TypePathSegmentContext *ctx) = 0;
  virtual void exitTypePathSegment(Parser::TypePathSegmentContext *ctx) = 0;

  virtual void enterPathInExpression(Parser::PathInExpressionContext *ctx) = 0;
  virtual void exitPathInExpression(Parser::PathInExpressionContext *ctx) = 0;

  virtual void enterPathExprSegment(Parser::PathExprSegmentContext *ctx) = 0;
  virtual void exitPathExprSegment(Parser::PathExprSegmentContext *ctx) = 0;

  virtual void enterPathIdentSegment(Parser::PathIdentSegmentContext *ctx) = 0;
  virtual void exitPathIdentSegment(Parser::PathIdentSegmentContext *ctx) = 0;

  virtual void enterGenericArgs(Parser::GenericArgsContext *ctx) = 0;
  virtual void exitGenericArgs(Parser::GenericArgsContext *ctx) = 0;

  virtual void enterGenericArg(Parser::GenericArgContext *ctx) = 0;
  virtual void exitGenericArg(Parser::GenericArgContext *ctx) = 0;

  virtual void enterGenericClose(Parser::GenericCloseContext *ctx) = 0;
  virtual void exitGenericClose(Parser::GenericCloseContext *ctx) = 0;

  virtual void enterClosedCastType(Parser::ClosedCastTypeContext *ctx) = 0;
  virtual void exitClosedCastType(Parser::ClosedCastTypeContext *ctx) = 0;

  virtual void enterConstValue(Parser::ConstValueContext *ctx) = 0;
  virtual void exitConstValue(Parser::ConstValueContext *ctx) = 0;

  virtual void enterMagnitude(Parser::MagnitudeContext *ctx) = 0;
  virtual void exitMagnitude(Parser::MagnitudeContext *ctx) = 0;

  virtual void enterIdentifierBinding(Parser::IdentifierBindingContext *ctx) = 0;
  virtual void exitIdentifierBinding(Parser::IdentifierBindingContext *ctx) = 0;

  virtual void enterLetStatement(Parser::LetStatementContext *ctx) = 0;
  virtual void exitLetStatement(Parser::LetStatementContext *ctx) = 0;

  virtual void enterBlockExpression(Parser::BlockExpressionContext *ctx) = 0;
  virtual void exitBlockExpression(Parser::BlockExpressionContext *ctx) = 0;

  virtual void enterStatement(Parser::StatementContext *ctx) = 0;
  virtual void exitStatement(Parser::StatementContext *ctx) = 0;

  virtual void enterExpressionWithBlock(Parser::ExpressionWithBlockContext *ctx) = 0;
  virtual void exitExpressionWithBlock(Parser::ExpressionWithBlockContext *ctx) = 0;

  virtual void enterIfExpression(Parser::IfExpressionContext *ctx) = 0;
  virtual void exitIfExpression(Parser::IfExpressionContext *ctx) = 0;

  virtual void enterExpression(Parser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(Parser::ExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(Parser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(Parser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(Parser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(Parser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(Parser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(Parser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterComparisonExpression(Parser::ComparisonExpressionContext *ctx) = 0;
  virtual void exitComparisonExpression(Parser::ComparisonExpressionContext *ctx) = 0;

  virtual void enterBitOrExpression(Parser::BitOrExpressionContext *ctx) = 0;
  virtual void exitBitOrExpression(Parser::BitOrExpressionContext *ctx) = 0;

  virtual void enterClosedBitOrExpression(Parser::ClosedBitOrExpressionContext *ctx) = 0;
  virtual void exitClosedBitOrExpression(Parser::ClosedBitOrExpressionContext *ctx) = 0;

  virtual void enterBitXorExpression(Parser::BitXorExpressionContext *ctx) = 0;
  virtual void exitBitXorExpression(Parser::BitXorExpressionContext *ctx) = 0;

  virtual void enterClosedBitXorExpression(Parser::ClosedBitXorExpressionContext *ctx) = 0;
  virtual void exitClosedBitXorExpression(Parser::ClosedBitXorExpressionContext *ctx) = 0;

  virtual void enterBitAndExpression(Parser::BitAndExpressionContext *ctx) = 0;
  virtual void exitBitAndExpression(Parser::BitAndExpressionContext *ctx) = 0;

  virtual void enterClosedBitAndExpression(Parser::ClosedBitAndExpressionContext *ctx) = 0;
  virtual void exitClosedBitAndExpression(Parser::ClosedBitAndExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(Parser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(Parser::ShiftExpressionContext *ctx) = 0;

  virtual void enterClosedShiftExpression(Parser::ClosedShiftExpressionContext *ctx) = 0;
  virtual void exitClosedShiftExpression(Parser::ClosedShiftExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(Parser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(Parser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterClosedAdditiveExpression(Parser::ClosedAdditiveExpressionContext *ctx) = 0;
  virtual void exitClosedAdditiveExpression(Parser::ClosedAdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(Parser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(Parser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterClosedMultiplicativeExpression(Parser::ClosedMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitClosedMultiplicativeExpression(Parser::ClosedMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterCastExpression(Parser::CastExpressionContext *ctx) = 0;
  virtual void exitCastExpression(Parser::CastExpressionContext *ctx) = 0;

  virtual void enterClosedCastExpression(Parser::ClosedCastExpressionContext *ctx) = 0;
  virtual void exitClosedCastExpression(Parser::ClosedCastExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(Parser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(Parser::UnaryExpressionContext *ctx) = 0;

  virtual void enterPostfixExpression(Parser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(Parser::PostfixExpressionContext *ctx) = 0;

  virtual void enterConditionExpression(Parser::ConditionExpressionContext *ctx) = 0;
  virtual void exitConditionExpression(Parser::ConditionExpressionContext *ctx) = 0;

  virtual void enterConditionAssignmentExpression(Parser::ConditionAssignmentExpressionContext *ctx) = 0;
  virtual void exitConditionAssignmentExpression(Parser::ConditionAssignmentExpressionContext *ctx) = 0;

  virtual void enterConditionLogicalOrExpression(Parser::ConditionLogicalOrExpressionContext *ctx) = 0;
  virtual void exitConditionLogicalOrExpression(Parser::ConditionLogicalOrExpressionContext *ctx) = 0;

  virtual void enterConditionLogicalAndExpression(Parser::ConditionLogicalAndExpressionContext *ctx) = 0;
  virtual void exitConditionLogicalAndExpression(Parser::ConditionLogicalAndExpressionContext *ctx) = 0;

  virtual void enterConditionComparisonExpression(Parser::ConditionComparisonExpressionContext *ctx) = 0;
  virtual void exitConditionComparisonExpression(Parser::ConditionComparisonExpressionContext *ctx) = 0;

  virtual void enterConditionBitOrExpression(Parser::ConditionBitOrExpressionContext *ctx) = 0;
  virtual void exitConditionBitOrExpression(Parser::ConditionBitOrExpressionContext *ctx) = 0;

  virtual void enterConditionClosedBitOrExpression(Parser::ConditionClosedBitOrExpressionContext *ctx) = 0;
  virtual void exitConditionClosedBitOrExpression(Parser::ConditionClosedBitOrExpressionContext *ctx) = 0;

  virtual void enterConditionBitXorExpression(Parser::ConditionBitXorExpressionContext *ctx) = 0;
  virtual void exitConditionBitXorExpression(Parser::ConditionBitXorExpressionContext *ctx) = 0;

  virtual void enterConditionClosedBitXorExpression(Parser::ConditionClosedBitXorExpressionContext *ctx) = 0;
  virtual void exitConditionClosedBitXorExpression(Parser::ConditionClosedBitXorExpressionContext *ctx) = 0;

  virtual void enterConditionBitAndExpression(Parser::ConditionBitAndExpressionContext *ctx) = 0;
  virtual void exitConditionBitAndExpression(Parser::ConditionBitAndExpressionContext *ctx) = 0;

  virtual void enterConditionClosedBitAndExpression(Parser::ConditionClosedBitAndExpressionContext *ctx) = 0;
  virtual void exitConditionClosedBitAndExpression(Parser::ConditionClosedBitAndExpressionContext *ctx) = 0;

  virtual void enterConditionShiftExpression(Parser::ConditionShiftExpressionContext *ctx) = 0;
  virtual void exitConditionShiftExpression(Parser::ConditionShiftExpressionContext *ctx) = 0;

  virtual void enterConditionClosedShiftExpression(Parser::ConditionClosedShiftExpressionContext *ctx) = 0;
  virtual void exitConditionClosedShiftExpression(Parser::ConditionClosedShiftExpressionContext *ctx) = 0;

  virtual void enterConditionAdditiveExpression(Parser::ConditionAdditiveExpressionContext *ctx) = 0;
  virtual void exitConditionAdditiveExpression(Parser::ConditionAdditiveExpressionContext *ctx) = 0;

  virtual void enterConditionClosedAdditiveExpression(Parser::ConditionClosedAdditiveExpressionContext *ctx) = 0;
  virtual void exitConditionClosedAdditiveExpression(Parser::ConditionClosedAdditiveExpressionContext *ctx) = 0;

  virtual void enterConditionMultiplicativeExpression(Parser::ConditionMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitConditionMultiplicativeExpression(Parser::ConditionMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterConditionClosedMultiplicativeExpression(Parser::ConditionClosedMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitConditionClosedMultiplicativeExpression(Parser::ConditionClosedMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterConditionCastExpression(Parser::ConditionCastExpressionContext *ctx) = 0;
  virtual void exitConditionCastExpression(Parser::ConditionCastExpressionContext *ctx) = 0;

  virtual void enterConditionClosedCastExpression(Parser::ConditionClosedCastExpressionContext *ctx) = 0;
  virtual void exitConditionClosedCastExpression(Parser::ConditionClosedCastExpressionContext *ctx) = 0;

  virtual void enterConditionUnaryExpression(Parser::ConditionUnaryExpressionContext *ctx) = 0;
  virtual void exitConditionUnaryExpression(Parser::ConditionUnaryExpressionContext *ctx) = 0;

  virtual void enterConditionPostfixExpression(Parser::ConditionPostfixExpressionContext *ctx) = 0;
  virtual void exitConditionPostfixExpression(Parser::ConditionPostfixExpressionContext *ctx) = 0;

  virtual void enterConditionBreakExpression(Parser::ConditionBreakExpressionContext *ctx) = 0;
  virtual void exitConditionBreakExpression(Parser::ConditionBreakExpressionContext *ctx) = 0;

  virtual void enterConditionBreakAssignmentExpression(Parser::ConditionBreakAssignmentExpressionContext *ctx) = 0;
  virtual void exitConditionBreakAssignmentExpression(Parser::ConditionBreakAssignmentExpressionContext *ctx) = 0;

  virtual void enterConditionBreakLogicalOrExpression(Parser::ConditionBreakLogicalOrExpressionContext *ctx) = 0;
  virtual void exitConditionBreakLogicalOrExpression(Parser::ConditionBreakLogicalOrExpressionContext *ctx) = 0;

  virtual void enterConditionBreakLogicalAndExpression(Parser::ConditionBreakLogicalAndExpressionContext *ctx) = 0;
  virtual void exitConditionBreakLogicalAndExpression(Parser::ConditionBreakLogicalAndExpressionContext *ctx) = 0;

  virtual void enterConditionBreakComparisonExpression(Parser::ConditionBreakComparisonExpressionContext *ctx) = 0;
  virtual void exitConditionBreakComparisonExpression(Parser::ConditionBreakComparisonExpressionContext *ctx) = 0;

  virtual void enterConditionBreakBitOrExpression(Parser::ConditionBreakBitOrExpressionContext *ctx) = 0;
  virtual void exitConditionBreakBitOrExpression(Parser::ConditionBreakBitOrExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedBitOrExpression(Parser::ConditionBreakClosedBitOrExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedBitOrExpression(Parser::ConditionBreakClosedBitOrExpressionContext *ctx) = 0;

  virtual void enterConditionBreakBitXorExpression(Parser::ConditionBreakBitXorExpressionContext *ctx) = 0;
  virtual void exitConditionBreakBitXorExpression(Parser::ConditionBreakBitXorExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedBitXorExpression(Parser::ConditionBreakClosedBitXorExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedBitXorExpression(Parser::ConditionBreakClosedBitXorExpressionContext *ctx) = 0;

  virtual void enterConditionBreakBitAndExpression(Parser::ConditionBreakBitAndExpressionContext *ctx) = 0;
  virtual void exitConditionBreakBitAndExpression(Parser::ConditionBreakBitAndExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedBitAndExpression(Parser::ConditionBreakClosedBitAndExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedBitAndExpression(Parser::ConditionBreakClosedBitAndExpressionContext *ctx) = 0;

  virtual void enterConditionBreakShiftExpression(Parser::ConditionBreakShiftExpressionContext *ctx) = 0;
  virtual void exitConditionBreakShiftExpression(Parser::ConditionBreakShiftExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedShiftExpression(Parser::ConditionBreakClosedShiftExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedShiftExpression(Parser::ConditionBreakClosedShiftExpressionContext *ctx) = 0;

  virtual void enterConditionBreakAdditiveExpression(Parser::ConditionBreakAdditiveExpressionContext *ctx) = 0;
  virtual void exitConditionBreakAdditiveExpression(Parser::ConditionBreakAdditiveExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedAdditiveExpression(Parser::ConditionBreakClosedAdditiveExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedAdditiveExpression(Parser::ConditionBreakClosedAdditiveExpressionContext *ctx) = 0;

  virtual void enterConditionBreakMultiplicativeExpression(Parser::ConditionBreakMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitConditionBreakMultiplicativeExpression(Parser::ConditionBreakMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedMultiplicativeExpression(Parser::ConditionBreakClosedMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedMultiplicativeExpression(Parser::ConditionBreakClosedMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterConditionBreakCastExpression(Parser::ConditionBreakCastExpressionContext *ctx) = 0;
  virtual void exitConditionBreakCastExpression(Parser::ConditionBreakCastExpressionContext *ctx) = 0;

  virtual void enterConditionBreakClosedCastExpression(Parser::ConditionBreakClosedCastExpressionContext *ctx) = 0;
  virtual void exitConditionBreakClosedCastExpression(Parser::ConditionBreakClosedCastExpressionContext *ctx) = 0;

  virtual void enterConditionBreakUnaryExpression(Parser::ConditionBreakUnaryExpressionContext *ctx) = 0;
  virtual void exitConditionBreakUnaryExpression(Parser::ConditionBreakUnaryExpressionContext *ctx) = 0;

  virtual void enterConditionBreakPostfixExpression(Parser::ConditionBreakPostfixExpressionContext *ctx) = 0;
  virtual void exitConditionBreakPostfixExpression(Parser::ConditionBreakPostfixExpressionContext *ctx) = 0;

  virtual void enterStatementExpression(Parser::StatementExpressionContext *ctx) = 0;
  virtual void exitStatementExpression(Parser::StatementExpressionContext *ctx) = 0;

  virtual void enterStatementAssignmentExpression(Parser::StatementAssignmentExpressionContext *ctx) = 0;
  virtual void exitStatementAssignmentExpression(Parser::StatementAssignmentExpressionContext *ctx) = 0;

  virtual void enterStatementLogicalOrExpression(Parser::StatementLogicalOrExpressionContext *ctx) = 0;
  virtual void exitStatementLogicalOrExpression(Parser::StatementLogicalOrExpressionContext *ctx) = 0;

  virtual void enterStatementLogicalAndExpression(Parser::StatementLogicalAndExpressionContext *ctx) = 0;
  virtual void exitStatementLogicalAndExpression(Parser::StatementLogicalAndExpressionContext *ctx) = 0;

  virtual void enterStatementComparisonExpression(Parser::StatementComparisonExpressionContext *ctx) = 0;
  virtual void exitStatementComparisonExpression(Parser::StatementComparisonExpressionContext *ctx) = 0;

  virtual void enterStatementBitOrExpression(Parser::StatementBitOrExpressionContext *ctx) = 0;
  virtual void exitStatementBitOrExpression(Parser::StatementBitOrExpressionContext *ctx) = 0;

  virtual void enterStatementClosedBitOrExpression(Parser::StatementClosedBitOrExpressionContext *ctx) = 0;
  virtual void exitStatementClosedBitOrExpression(Parser::StatementClosedBitOrExpressionContext *ctx) = 0;

  virtual void enterStatementBitXorExpression(Parser::StatementBitXorExpressionContext *ctx) = 0;
  virtual void exitStatementBitXorExpression(Parser::StatementBitXorExpressionContext *ctx) = 0;

  virtual void enterStatementClosedBitXorExpression(Parser::StatementClosedBitXorExpressionContext *ctx) = 0;
  virtual void exitStatementClosedBitXorExpression(Parser::StatementClosedBitXorExpressionContext *ctx) = 0;

  virtual void enterStatementBitAndExpression(Parser::StatementBitAndExpressionContext *ctx) = 0;
  virtual void exitStatementBitAndExpression(Parser::StatementBitAndExpressionContext *ctx) = 0;

  virtual void enterStatementClosedBitAndExpression(Parser::StatementClosedBitAndExpressionContext *ctx) = 0;
  virtual void exitStatementClosedBitAndExpression(Parser::StatementClosedBitAndExpressionContext *ctx) = 0;

  virtual void enterStatementShiftExpression(Parser::StatementShiftExpressionContext *ctx) = 0;
  virtual void exitStatementShiftExpression(Parser::StatementShiftExpressionContext *ctx) = 0;

  virtual void enterStatementClosedShiftExpression(Parser::StatementClosedShiftExpressionContext *ctx) = 0;
  virtual void exitStatementClosedShiftExpression(Parser::StatementClosedShiftExpressionContext *ctx) = 0;

  virtual void enterStatementAdditiveExpression(Parser::StatementAdditiveExpressionContext *ctx) = 0;
  virtual void exitStatementAdditiveExpression(Parser::StatementAdditiveExpressionContext *ctx) = 0;

  virtual void enterStatementClosedAdditiveExpression(Parser::StatementClosedAdditiveExpressionContext *ctx) = 0;
  virtual void exitStatementClosedAdditiveExpression(Parser::StatementClosedAdditiveExpressionContext *ctx) = 0;

  virtual void enterStatementMultiplicativeExpression(Parser::StatementMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitStatementMultiplicativeExpression(Parser::StatementMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterStatementClosedMultiplicativeExpression(Parser::StatementClosedMultiplicativeExpressionContext *ctx) = 0;
  virtual void exitStatementClosedMultiplicativeExpression(Parser::StatementClosedMultiplicativeExpressionContext *ctx) = 0;

  virtual void enterStatementCastExpression(Parser::StatementCastExpressionContext *ctx) = 0;
  virtual void exitStatementCastExpression(Parser::StatementCastExpressionContext *ctx) = 0;

  virtual void enterStatementClosedCastExpression(Parser::StatementClosedCastExpressionContext *ctx) = 0;
  virtual void exitStatementClosedCastExpression(Parser::StatementClosedCastExpressionContext *ctx) = 0;

  virtual void enterStatementUnaryExpression(Parser::StatementUnaryExpressionContext *ctx) = 0;
  virtual void exitStatementUnaryExpression(Parser::StatementUnaryExpressionContext *ctx) = 0;

  virtual void enterStatementPostfixExpression(Parser::StatementPostfixExpressionContext *ctx) = 0;
  virtual void exitStatementPostfixExpression(Parser::StatementPostfixExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(Parser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(Parser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterNonBlockPrimary(Parser::NonBlockPrimaryContext *ctx) = 0;
  virtual void exitNonBlockPrimary(Parser::NonBlockPrimaryContext *ctx) = 0;

  virtual void enterConditionPrimary(Parser::ConditionPrimaryContext *ctx) = 0;
  virtual void exitConditionPrimary(Parser::ConditionPrimaryContext *ctx) = 0;

  virtual void enterConditionPrimaryWithoutBareBlock(Parser::ConditionPrimaryWithoutBareBlockContext *ctx) = 0;
  virtual void exitConditionPrimaryWithoutBareBlock(Parser::ConditionPrimaryWithoutBareBlockContext *ctx) = 0;

  virtual void enterLiteralExpression(Parser::LiteralExpressionContext *ctx) = 0;
  virtual void exitLiteralExpression(Parser::LiteralExpressionContext *ctx) = 0;

  virtual void enterStructExprFields(Parser::StructExprFieldsContext *ctx) = 0;
  virtual void exitStructExprFields(Parser::StructExprFieldsContext *ctx) = 0;

  virtual void enterStructExprField(Parser::StructExprFieldContext *ctx) = 0;
  virtual void exitStructExprField(Parser::StructExprFieldContext *ctx) = 0;

  virtual void enterArrayExpression(Parser::ArrayExpressionContext *ctx) = 0;
  virtual void exitArrayExpression(Parser::ArrayExpressionContext *ctx) = 0;

  virtual void enterPostfixSuffix(Parser::PostfixSuffixContext *ctx) = 0;
  virtual void exitPostfixSuffix(Parser::PostfixSuffixContext *ctx) = 0;

  virtual void enterDotSuffix(Parser::DotSuffixContext *ctx) = 0;
  virtual void exitDotSuffix(Parser::DotSuffixContext *ctx) = 0;

  virtual void enterCallArguments(Parser::CallArgumentsContext *ctx) = 0;
  virtual void exitCallArguments(Parser::CallArgumentsContext *ctx) = 0;

  virtual void enterUnaryOperator(Parser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(Parser::UnaryOperatorContext *ctx) = 0;

  virtual void enterMultiplicativeOperator(Parser::MultiplicativeOperatorContext *ctx) = 0;
  virtual void exitMultiplicativeOperator(Parser::MultiplicativeOperatorContext *ctx) = 0;

  virtual void enterAdditiveOperator(Parser::AdditiveOperatorContext *ctx) = 0;
  virtual void exitAdditiveOperator(Parser::AdditiveOperatorContext *ctx) = 0;

  virtual void enterShiftRight(Parser::ShiftRightContext *ctx) = 0;
  virtual void exitShiftRight(Parser::ShiftRightContext *ctx) = 0;

  virtual void enterComparisonExceptLt(Parser::ComparisonExceptLtContext *ctx) = 0;
  virtual void exitComparisonExceptLt(Parser::ComparisonExceptLtContext *ctx) = 0;

  virtual void enterAssignmentOperator(Parser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(Parser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterEqualsSign(Parser::EqualsSignContext *ctx) = 0;
  virtual void exitEqualsSign(Parser::EqualsSignContext *ctx) = 0;

  virtual void enterIdentifier(Parser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(Parser::IdentifierContext *ctx) = 0;


};

}  // namespace rx
