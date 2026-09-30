
// Generated from Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ParserListener.h"


namespace rx {

/**
 * This class provides an empty implementation of ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ParserBaseListener : public ParserListener {
public:

  virtual void enterCrate(Parser::CrateContext * /*ctx*/) override { }
  virtual void exitCrate(Parser::CrateContext * /*ctx*/) override { }

  virtual void enterItem(Parser::ItemContext * /*ctx*/) override { }
  virtual void exitItem(Parser::ItemContext * /*ctx*/) override { }

  virtual void enterUseDeclaration(Parser::UseDeclarationContext * /*ctx*/) override { }
  virtual void exitUseDeclaration(Parser::UseDeclarationContext * /*ctx*/) override { }

  virtual void enterUseTree(Parser::UseTreeContext * /*ctx*/) override { }
  virtual void exitUseTree(Parser::UseTreeContext * /*ctx*/) override { }

  virtual void enterUsePath(Parser::UsePathContext * /*ctx*/) override { }
  virtual void exitUsePath(Parser::UsePathContext * /*ctx*/) override { }

  virtual void enterUsePathSegment(Parser::UsePathSegmentContext * /*ctx*/) override { }
  virtual void exitUsePathSegment(Parser::UsePathSegmentContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(Parser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(Parser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterFunctionParameters(Parser::FunctionParametersContext * /*ctx*/) override { }
  virtual void exitFunctionParameters(Parser::FunctionParametersContext * /*ctx*/) override { }

  virtual void enterSelfParam(Parser::SelfParamContext * /*ctx*/) override { }
  virtual void exitSelfParam(Parser::SelfParamContext * /*ctx*/) override { }

  virtual void enterFunctionParam(Parser::FunctionParamContext * /*ctx*/) override { }
  virtual void exitFunctionParam(Parser::FunctionParamContext * /*ctx*/) override { }

  virtual void enterStructDefinition(Parser::StructDefinitionContext * /*ctx*/) override { }
  virtual void exitStructDefinition(Parser::StructDefinitionContext * /*ctx*/) override { }

  virtual void enterStructField(Parser::StructFieldContext * /*ctx*/) override { }
  virtual void exitStructField(Parser::StructFieldContext * /*ctx*/) override { }

  virtual void enterOuterAttribute(Parser::OuterAttributeContext * /*ctx*/) override { }
  virtual void exitOuterAttribute(Parser::OuterAttributeContext * /*ctx*/) override { }

  virtual void enterDeriveName(Parser::DeriveNameContext * /*ctx*/) override { }
  virtual void exitDeriveName(Parser::DeriveNameContext * /*ctx*/) override { }

  virtual void enterConstantItem(Parser::ConstantItemContext * /*ctx*/) override { }
  virtual void exitConstantItem(Parser::ConstantItemContext * /*ctx*/) override { }

  virtual void enterInherentImpl(Parser::InherentImplContext * /*ctx*/) override { }
  virtual void exitInherentImpl(Parser::InherentImplContext * /*ctx*/) override { }

  virtual void enterAssociatedItem(Parser::AssociatedItemContext * /*ctx*/) override { }
  virtual void exitAssociatedItem(Parser::AssociatedItemContext * /*ctx*/) override { }

  virtual void enterGenericParams(Parser::GenericParamsContext * /*ctx*/) override { }
  virtual void exitGenericParams(Parser::GenericParamsContext * /*ctx*/) override { }

  virtual void enterLifetimeParam(Parser::LifetimeParamContext * /*ctx*/) override { }
  virtual void exitLifetimeParam(Parser::LifetimeParamContext * /*ctx*/) override { }

  virtual void enterLifetime(Parser::LifetimeContext * /*ctx*/) override { }
  virtual void exitLifetime(Parser::LifetimeContext * /*ctx*/) override { }

  virtual void enterLifetimeBounds(Parser::LifetimeBoundsContext * /*ctx*/) override { }
  virtual void exitLifetimeBounds(Parser::LifetimeBoundsContext * /*ctx*/) override { }

  virtual void enterTypeParamBounds(Parser::TypeParamBoundsContext * /*ctx*/) override { }
  virtual void exitTypeParamBounds(Parser::TypeParamBoundsContext * /*ctx*/) override { }

  virtual void enterWhereClause(Parser::WhereClauseContext * /*ctx*/) override { }
  virtual void exitWhereClause(Parser::WhereClauseContext * /*ctx*/) override { }

  virtual void enterWhereClauseItem(Parser::WhereClauseItemContext * /*ctx*/) override { }
  virtual void exitWhereClauseItem(Parser::WhereClauseItemContext * /*ctx*/) override { }

  virtual void enterTypeRef(Parser::TypeRefContext * /*ctx*/) override { }
  virtual void exitTypeRef(Parser::TypeRefContext * /*ctx*/) override { }

  virtual void enterReferenceType(Parser::ReferenceTypeContext * /*ctx*/) override { }
  virtual void exitReferenceType(Parser::ReferenceTypeContext * /*ctx*/) override { }

  virtual void enterArrayType(Parser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(Parser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterTypePath(Parser::TypePathContext * /*ctx*/) override { }
  virtual void exitTypePath(Parser::TypePathContext * /*ctx*/) override { }

  virtual void enterTypePathSegment(Parser::TypePathSegmentContext * /*ctx*/) override { }
  virtual void exitTypePathSegment(Parser::TypePathSegmentContext * /*ctx*/) override { }

  virtual void enterPathInExpression(Parser::PathInExpressionContext * /*ctx*/) override { }
  virtual void exitPathInExpression(Parser::PathInExpressionContext * /*ctx*/) override { }

  virtual void enterPathExprSegment(Parser::PathExprSegmentContext * /*ctx*/) override { }
  virtual void exitPathExprSegment(Parser::PathExprSegmentContext * /*ctx*/) override { }

  virtual void enterPathIdentSegment(Parser::PathIdentSegmentContext * /*ctx*/) override { }
  virtual void exitPathIdentSegment(Parser::PathIdentSegmentContext * /*ctx*/) override { }

  virtual void enterGenericArgs(Parser::GenericArgsContext * /*ctx*/) override { }
  virtual void exitGenericArgs(Parser::GenericArgsContext * /*ctx*/) override { }

  virtual void enterGenericArg(Parser::GenericArgContext * /*ctx*/) override { }
  virtual void exitGenericArg(Parser::GenericArgContext * /*ctx*/) override { }

  virtual void enterGenericClose(Parser::GenericCloseContext * /*ctx*/) override { }
  virtual void exitGenericClose(Parser::GenericCloseContext * /*ctx*/) override { }

  virtual void enterClosedCastType(Parser::ClosedCastTypeContext * /*ctx*/) override { }
  virtual void exitClosedCastType(Parser::ClosedCastTypeContext * /*ctx*/) override { }

  virtual void enterConstValue(Parser::ConstValueContext * /*ctx*/) override { }
  virtual void exitConstValue(Parser::ConstValueContext * /*ctx*/) override { }

  virtual void enterMagnitude(Parser::MagnitudeContext * /*ctx*/) override { }
  virtual void exitMagnitude(Parser::MagnitudeContext * /*ctx*/) override { }

  virtual void enterIdentifierBinding(Parser::IdentifierBindingContext * /*ctx*/) override { }
  virtual void exitIdentifierBinding(Parser::IdentifierBindingContext * /*ctx*/) override { }

  virtual void enterLetStatement(Parser::LetStatementContext * /*ctx*/) override { }
  virtual void exitLetStatement(Parser::LetStatementContext * /*ctx*/) override { }

  virtual void enterBlockExpression(Parser::BlockExpressionContext * /*ctx*/) override { }
  virtual void exitBlockExpression(Parser::BlockExpressionContext * /*ctx*/) override { }

  virtual void enterStatement(Parser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(Parser::StatementContext * /*ctx*/) override { }

  virtual void enterExpressionWithBlock(Parser::ExpressionWithBlockContext * /*ctx*/) override { }
  virtual void exitExpressionWithBlock(Parser::ExpressionWithBlockContext * /*ctx*/) override { }

  virtual void enterIfExpression(Parser::IfExpressionContext * /*ctx*/) override { }
  virtual void exitIfExpression(Parser::IfExpressionContext * /*ctx*/) override { }

  virtual void enterExpression(Parser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(Parser::ExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(Parser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(Parser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(Parser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(Parser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(Parser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(Parser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterComparisonExpression(Parser::ComparisonExpressionContext * /*ctx*/) override { }
  virtual void exitComparisonExpression(Parser::ComparisonExpressionContext * /*ctx*/) override { }

  virtual void enterBitOrExpression(Parser::BitOrExpressionContext * /*ctx*/) override { }
  virtual void exitBitOrExpression(Parser::BitOrExpressionContext * /*ctx*/) override { }

  virtual void enterClosedBitOrExpression(Parser::ClosedBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitClosedBitOrExpression(Parser::ClosedBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterBitXorExpression(Parser::BitXorExpressionContext * /*ctx*/) override { }
  virtual void exitBitXorExpression(Parser::BitXorExpressionContext * /*ctx*/) override { }

  virtual void enterClosedBitXorExpression(Parser::ClosedBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitClosedBitXorExpression(Parser::ClosedBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterBitAndExpression(Parser::BitAndExpressionContext * /*ctx*/) override { }
  virtual void exitBitAndExpression(Parser::BitAndExpressionContext * /*ctx*/) override { }

  virtual void enterClosedBitAndExpression(Parser::ClosedBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitClosedBitAndExpression(Parser::ClosedBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterShiftExpression(Parser::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(Parser::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterClosedShiftExpression(Parser::ClosedShiftExpressionContext * /*ctx*/) override { }
  virtual void exitClosedShiftExpression(Parser::ClosedShiftExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(Parser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(Parser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterClosedAdditiveExpression(Parser::ClosedAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitClosedAdditiveExpression(Parser::ClosedAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(Parser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(Parser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterClosedMultiplicativeExpression(Parser::ClosedMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitClosedMultiplicativeExpression(Parser::ClosedMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterCastExpression(Parser::CastExpressionContext * /*ctx*/) override { }
  virtual void exitCastExpression(Parser::CastExpressionContext * /*ctx*/) override { }

  virtual void enterClosedCastExpression(Parser::ClosedCastExpressionContext * /*ctx*/) override { }
  virtual void exitClosedCastExpression(Parser::ClosedCastExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(Parser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(Parser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(Parser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(Parser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterConditionExpression(Parser::ConditionExpressionContext * /*ctx*/) override { }
  virtual void exitConditionExpression(Parser::ConditionExpressionContext * /*ctx*/) override { }

  virtual void enterConditionAssignmentExpression(Parser::ConditionAssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitConditionAssignmentExpression(Parser::ConditionAssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterConditionLogicalOrExpression(Parser::ConditionLogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionLogicalOrExpression(Parser::ConditionLogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionLogicalAndExpression(Parser::ConditionLogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionLogicalAndExpression(Parser::ConditionLogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterConditionComparisonExpression(Parser::ConditionComparisonExpressionContext * /*ctx*/) override { }
  virtual void exitConditionComparisonExpression(Parser::ConditionComparisonExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBitOrExpression(Parser::ConditionBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBitOrExpression(Parser::ConditionBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedBitOrExpression(Parser::ConditionClosedBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedBitOrExpression(Parser::ConditionClosedBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBitXorExpression(Parser::ConditionBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBitXorExpression(Parser::ConditionBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedBitXorExpression(Parser::ConditionClosedBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedBitXorExpression(Parser::ConditionClosedBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBitAndExpression(Parser::ConditionBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBitAndExpression(Parser::ConditionBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedBitAndExpression(Parser::ConditionClosedBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedBitAndExpression(Parser::ConditionClosedBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterConditionShiftExpression(Parser::ConditionShiftExpressionContext * /*ctx*/) override { }
  virtual void exitConditionShiftExpression(Parser::ConditionShiftExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedShiftExpression(Parser::ConditionClosedShiftExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedShiftExpression(Parser::ConditionClosedShiftExpressionContext * /*ctx*/) override { }

  virtual void enterConditionAdditiveExpression(Parser::ConditionAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitConditionAdditiveExpression(Parser::ConditionAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedAdditiveExpression(Parser::ConditionClosedAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedAdditiveExpression(Parser::ConditionClosedAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterConditionMultiplicativeExpression(Parser::ConditionMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitConditionMultiplicativeExpression(Parser::ConditionMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedMultiplicativeExpression(Parser::ConditionClosedMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedMultiplicativeExpression(Parser::ConditionClosedMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterConditionCastExpression(Parser::ConditionCastExpressionContext * /*ctx*/) override { }
  virtual void exitConditionCastExpression(Parser::ConditionCastExpressionContext * /*ctx*/) override { }

  virtual void enterConditionClosedCastExpression(Parser::ConditionClosedCastExpressionContext * /*ctx*/) override { }
  virtual void exitConditionClosedCastExpression(Parser::ConditionClosedCastExpressionContext * /*ctx*/) override { }

  virtual void enterConditionUnaryExpression(Parser::ConditionUnaryExpressionContext * /*ctx*/) override { }
  virtual void exitConditionUnaryExpression(Parser::ConditionUnaryExpressionContext * /*ctx*/) override { }

  virtual void enterConditionPostfixExpression(Parser::ConditionPostfixExpressionContext * /*ctx*/) override { }
  virtual void exitConditionPostfixExpression(Parser::ConditionPostfixExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakExpression(Parser::ConditionBreakExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakExpression(Parser::ConditionBreakExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakAssignmentExpression(Parser::ConditionBreakAssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakAssignmentExpression(Parser::ConditionBreakAssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakLogicalOrExpression(Parser::ConditionBreakLogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakLogicalOrExpression(Parser::ConditionBreakLogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakLogicalAndExpression(Parser::ConditionBreakLogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakLogicalAndExpression(Parser::ConditionBreakLogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakComparisonExpression(Parser::ConditionBreakComparisonExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakComparisonExpression(Parser::ConditionBreakComparisonExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakBitOrExpression(Parser::ConditionBreakBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakBitOrExpression(Parser::ConditionBreakBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedBitOrExpression(Parser::ConditionBreakClosedBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedBitOrExpression(Parser::ConditionBreakClosedBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakBitXorExpression(Parser::ConditionBreakBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakBitXorExpression(Parser::ConditionBreakBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedBitXorExpression(Parser::ConditionBreakClosedBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedBitXorExpression(Parser::ConditionBreakClosedBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakBitAndExpression(Parser::ConditionBreakBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakBitAndExpression(Parser::ConditionBreakBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedBitAndExpression(Parser::ConditionBreakClosedBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedBitAndExpression(Parser::ConditionBreakClosedBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakShiftExpression(Parser::ConditionBreakShiftExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakShiftExpression(Parser::ConditionBreakShiftExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedShiftExpression(Parser::ConditionBreakClosedShiftExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedShiftExpression(Parser::ConditionBreakClosedShiftExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakAdditiveExpression(Parser::ConditionBreakAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakAdditiveExpression(Parser::ConditionBreakAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedAdditiveExpression(Parser::ConditionBreakClosedAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedAdditiveExpression(Parser::ConditionBreakClosedAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakMultiplicativeExpression(Parser::ConditionBreakMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakMultiplicativeExpression(Parser::ConditionBreakMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedMultiplicativeExpression(Parser::ConditionBreakClosedMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedMultiplicativeExpression(Parser::ConditionBreakClosedMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakCastExpression(Parser::ConditionBreakCastExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakCastExpression(Parser::ConditionBreakCastExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakClosedCastExpression(Parser::ConditionBreakClosedCastExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakClosedCastExpression(Parser::ConditionBreakClosedCastExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakUnaryExpression(Parser::ConditionBreakUnaryExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakUnaryExpression(Parser::ConditionBreakUnaryExpressionContext * /*ctx*/) override { }

  virtual void enterConditionBreakPostfixExpression(Parser::ConditionBreakPostfixExpressionContext * /*ctx*/) override { }
  virtual void exitConditionBreakPostfixExpression(Parser::ConditionBreakPostfixExpressionContext * /*ctx*/) override { }

  virtual void enterStatementExpression(Parser::StatementExpressionContext * /*ctx*/) override { }
  virtual void exitStatementExpression(Parser::StatementExpressionContext * /*ctx*/) override { }

  virtual void enterStatementAssignmentExpression(Parser::StatementAssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitStatementAssignmentExpression(Parser::StatementAssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterStatementLogicalOrExpression(Parser::StatementLogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitStatementLogicalOrExpression(Parser::StatementLogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterStatementLogicalAndExpression(Parser::StatementLogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitStatementLogicalAndExpression(Parser::StatementLogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterStatementComparisonExpression(Parser::StatementComparisonExpressionContext * /*ctx*/) override { }
  virtual void exitStatementComparisonExpression(Parser::StatementComparisonExpressionContext * /*ctx*/) override { }

  virtual void enterStatementBitOrExpression(Parser::StatementBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitStatementBitOrExpression(Parser::StatementBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedBitOrExpression(Parser::StatementClosedBitOrExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedBitOrExpression(Parser::StatementClosedBitOrExpressionContext * /*ctx*/) override { }

  virtual void enterStatementBitXorExpression(Parser::StatementBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitStatementBitXorExpression(Parser::StatementBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedBitXorExpression(Parser::StatementClosedBitXorExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedBitXorExpression(Parser::StatementClosedBitXorExpressionContext * /*ctx*/) override { }

  virtual void enterStatementBitAndExpression(Parser::StatementBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitStatementBitAndExpression(Parser::StatementBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedBitAndExpression(Parser::StatementClosedBitAndExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedBitAndExpression(Parser::StatementClosedBitAndExpressionContext * /*ctx*/) override { }

  virtual void enterStatementShiftExpression(Parser::StatementShiftExpressionContext * /*ctx*/) override { }
  virtual void exitStatementShiftExpression(Parser::StatementShiftExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedShiftExpression(Parser::StatementClosedShiftExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedShiftExpression(Parser::StatementClosedShiftExpressionContext * /*ctx*/) override { }

  virtual void enterStatementAdditiveExpression(Parser::StatementAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitStatementAdditiveExpression(Parser::StatementAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedAdditiveExpression(Parser::StatementClosedAdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedAdditiveExpression(Parser::StatementClosedAdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterStatementMultiplicativeExpression(Parser::StatementMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitStatementMultiplicativeExpression(Parser::StatementMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedMultiplicativeExpression(Parser::StatementClosedMultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedMultiplicativeExpression(Parser::StatementClosedMultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterStatementCastExpression(Parser::StatementCastExpressionContext * /*ctx*/) override { }
  virtual void exitStatementCastExpression(Parser::StatementCastExpressionContext * /*ctx*/) override { }

  virtual void enterStatementClosedCastExpression(Parser::StatementClosedCastExpressionContext * /*ctx*/) override { }
  virtual void exitStatementClosedCastExpression(Parser::StatementClosedCastExpressionContext * /*ctx*/) override { }

  virtual void enterStatementUnaryExpression(Parser::StatementUnaryExpressionContext * /*ctx*/) override { }
  virtual void exitStatementUnaryExpression(Parser::StatementUnaryExpressionContext * /*ctx*/) override { }

  virtual void enterStatementPostfixExpression(Parser::StatementPostfixExpressionContext * /*ctx*/) override { }
  virtual void exitStatementPostfixExpression(Parser::StatementPostfixExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(Parser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(Parser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterNonBlockPrimary(Parser::NonBlockPrimaryContext * /*ctx*/) override { }
  virtual void exitNonBlockPrimary(Parser::NonBlockPrimaryContext * /*ctx*/) override { }

  virtual void enterConditionPrimary(Parser::ConditionPrimaryContext * /*ctx*/) override { }
  virtual void exitConditionPrimary(Parser::ConditionPrimaryContext * /*ctx*/) override { }

  virtual void enterConditionPrimaryWithoutBareBlock(Parser::ConditionPrimaryWithoutBareBlockContext * /*ctx*/) override { }
  virtual void exitConditionPrimaryWithoutBareBlock(Parser::ConditionPrimaryWithoutBareBlockContext * /*ctx*/) override { }

  virtual void enterLiteralExpression(Parser::LiteralExpressionContext * /*ctx*/) override { }
  virtual void exitLiteralExpression(Parser::LiteralExpressionContext * /*ctx*/) override { }

  virtual void enterStructExprFields(Parser::StructExprFieldsContext * /*ctx*/) override { }
  virtual void exitStructExprFields(Parser::StructExprFieldsContext * /*ctx*/) override { }

  virtual void enterStructExprField(Parser::StructExprFieldContext * /*ctx*/) override { }
  virtual void exitStructExprField(Parser::StructExprFieldContext * /*ctx*/) override { }

  virtual void enterArrayExpression(Parser::ArrayExpressionContext * /*ctx*/) override { }
  virtual void exitArrayExpression(Parser::ArrayExpressionContext * /*ctx*/) override { }

  virtual void enterPostfixSuffix(Parser::PostfixSuffixContext * /*ctx*/) override { }
  virtual void exitPostfixSuffix(Parser::PostfixSuffixContext * /*ctx*/) override { }

  virtual void enterDotSuffix(Parser::DotSuffixContext * /*ctx*/) override { }
  virtual void exitDotSuffix(Parser::DotSuffixContext * /*ctx*/) override { }

  virtual void enterCallArguments(Parser::CallArgumentsContext * /*ctx*/) override { }
  virtual void exitCallArguments(Parser::CallArgumentsContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(Parser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(Parser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterMultiplicativeOperator(Parser::MultiplicativeOperatorContext * /*ctx*/) override { }
  virtual void exitMultiplicativeOperator(Parser::MultiplicativeOperatorContext * /*ctx*/) override { }

  virtual void enterAdditiveOperator(Parser::AdditiveOperatorContext * /*ctx*/) override { }
  virtual void exitAdditiveOperator(Parser::AdditiveOperatorContext * /*ctx*/) override { }

  virtual void enterShiftRight(Parser::ShiftRightContext * /*ctx*/) override { }
  virtual void exitShiftRight(Parser::ShiftRightContext * /*ctx*/) override { }

  virtual void enterComparisonExceptLt(Parser::ComparisonExceptLtContext * /*ctx*/) override { }
  virtual void exitComparisonExceptLt(Parser::ComparisonExceptLtContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(Parser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(Parser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterEqualsSign(Parser::EqualsSignContext * /*ctx*/) override { }
  virtual void exitEqualsSign(Parser::EqualsSignContext * /*ctx*/) override { }

  virtual void enterIdentifier(Parser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(Parser::IdentifierContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace rx
