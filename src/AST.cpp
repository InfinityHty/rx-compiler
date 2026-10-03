#include "AST.h"
#include "Parser.h"

ASTNode::~ASTNode() {}
// 工具函数
// 检查是什么Type并返回指针
ASTNode* ASTNode::CheckType(rx::Parser::TypeRefContext* ctx){
    assert(ctx != nullptr);
    rx::Parser::TypeRefContext* type = ctx;
    while(type->typeRef() != nullptr){
        type = type->typeRef();
    }
    rx::Parser::TypePathContext* is_path_type = type->typePath();
    rx::Parser::ReferenceTypeContext* is_ref_type = type->referenceType();
    rx::Parser::ArrayTypeContext* is_array_type = type->arrayType();
    if(is_path_type != nullptr){
        return new PathTypeNode(PathType,is_path_type);
    }
    else if(is_ref_type != nullptr){
       return new RefTypeNode(RefType,is_ref_type);
    }
    else if(is_array_type != nullptr){
        return new ArrayTypeNode(ArrayType,is_array_type);
    }
    else{
        return new UnitTypeNode(UnitType);
    }
}
ASTNode* ASTNode::CheckConstValue(rx::Parser::ConstValueContext* ctx){
    rx::Parser::ConstValueContext* tmp = ctx;
    while(tmp->constValue() != nullptr){
        tmp = tmp->constValue();
    }
    auto is_integer = tmp->INTEGER_LITERAL();
    auto is_true = tmp->TRUE();
    auto is_false = tmp->FALSE();
    auto is_path_in_expr = tmp->pathInExpression();
    if(is_integer != nullptr){
        return new IntLitNode(IntLit,is_integer->getText()); // 后续转为uint32
    }
    else if(is_true != nullptr){
        return new BoolLitNode(BoolLit,true);
    }
    else if(is_false != nullptr){
        return new BoolLitNode(BoolLit,false);
    }
    else if(is_path_in_expr != nullptr){
        return new PathExprNode(PathExpr,is_path_in_expr);
    }
    else{
        auto magnitude_ptr = tmp->magnitude();
        while(magnitude_ptr->magnitude() != nullptr){
            magnitude_ptr = magnitude_ptr->magnitude();
        }
        if(magnitude_ptr->INTEGER_LITERAL() != nullptr){
            return new IntLitNode(IntLit,"-" + magnitude_ptr->INTEGER_LITERAL()->getText());
        }
        auto node = new UnaryExprNode(UnaryExpr);
        node->op = "-";
        node->expr = new PathExprNode(PathExpr,magnitude_ptr->pathInExpression());
        return node;
    }
}
long long StringToInt(std::string& val,std::string& suffix){
    long long ans = 0;
    int digit = 0;
    int neg = 1;
    if(val[0] == '-'){
        neg = -1;
        digit++;
    }
    if(val[digit] == '0' && val[digit + 1] == 'b'){
        // 二进制
        digit += 2;
        while(val[digit] != 'i' && val[digit] != 'u'){
            if(val[digit] == '0' || val[digit] == '1'){
                ans = ans * 2 + val[digit] - '0';
            }
            digit++;
        }
    }
    else if(val[digit] == '0' && val[digit + 1] == 'o'){
        // 八进制
        digit += 2;
        while(val[digit] != 'i' && val[digit] != 'u'){
            if('0' <= val[digit] && val[digit] <= '7'){
                ans = ans * 8 + val[digit] - '0';
            }
            digit++;
        }
    }
    else if(val[digit] == '0' && val[digit + 1] == 'x'){
        // 十六进制
        digit += 2;
        while(val[digit] != 'i' && val[digit] != 'u'){
            if('0' <= val[digit] && val[digit] <= '9'){
                ans = ans * 16 + val[digit] - '0';
            }
            else if('A' <= val[digit] && val[digit] <= 'F'){
                ans = ans * 16 + val[digit] - 'A';
            }
            else if('a' <= val[digit] && val[digit] <= 'f'){
                ans = ans * 16 + val[digit] - 'a';
            }
            digit++;
        }
    }
    else{
        // 十进制
        while(val[digit] != 'i' && val[digit] != 'u'){
            if('0' <= val[digit] && val[digit] <= '9'){
                ans = ans * 10 + val[digit] - '0';
            }
            digit++;
        }
    }
    while(val[digit] != '\0'){
        suffix += val[digit++];
    }
    return ans * neg;
}
// 构建AST 各个派生类的构造函数
// items
CrateNode::CrateNode(const ASTNodeType kind_, rx::Parser::CrateContext* ctx) : ASTNode(kind_) {
    std::vector<rx::Parser::ItemContext*> items = ctx->item();
    for(auto item : items){
        rx::Parser::FunctionDefinitionContext* is_func = item->functionDefinition();            
        rx::Parser::StructDefinitionContext* is_struct = item->structDefinition();
        rx::Parser::ConstantItemContext* is_const = item->constantItem();
        rx::Parser::InherentImplContext* is_impl = item->inherentImpl();
        if(is_func != nullptr) {
            FnItemNode* item_ptr = new FnItemNode(FnItem,is_func);
            this->items.push_back(item_ptr);
        }
        else if(is_struct != nullptr) {
            StructItemNode* item_ptr = new StructItemNode(StructItem,is_struct);
            this->items.push_back(item_ptr);
        }
        else if(is_const != nullptr){
            ConstItemNode* item_ptr = new ConstItemNode(ConstItem,is_const);
            this->items.push_back(item_ptr);
        }
        else if(item->inherentImpl() != nullptr){
            ImplItemNode* item_ptr = new ImplItemNode(ImplItem,is_impl);
            this->items.push_back(item_ptr);
        }
    }
}
FnItemNode::FnItemNode(const ASTNodeType kind_,rx::Parser::FunctionDefinitionContext* ctx) : ASTNode(kind_) {
    this->name = ctx->identifier()->getText();
    this->blockExpr = new BlockExprNode(BlockExpr,ctx->blockExpression());
    rx::Parser::TypeRefContext* return_type = ctx->typeRef();
    if(return_type != nullptr){
        this->returnType = CheckType(return_type);
    }
    rx::Parser::FunctionParametersContext* parameters = ctx->functionParameters();
    if(parameters != nullptr){
        if(parameters->selfParam() != nullptr){
            this->parameters.push_back(new FnSelfParamNode(FnSelfParam,parameters->selfParam()));
        }
        std::vector<rx::Parser::FunctionParamContext*> parameter = parameters->functionParam();
        for(auto param : parameter){
            this->parameters.push_back(new FnParamNode(FnParam,param));
        }
    }
}
StructItemNode::StructItemNode(const ASTNodeType kind_,rx::Parser::StructDefinitionContext* ctx) : ASTNode(kind_) {
    this->name = ctx->identifier()->getText();
    std::vector<rx::Parser::StructFieldContext*> struct_field = ctx->structField();
    for(auto field : struct_field){
        StructFieldNode* field_ptr = new StructFieldNode(StructField,field);
        this->structField.push_back(field_ptr);
    }
}
ConstItemNode::ConstItemNode(const ASTNodeType kind_,rx::Parser::ConstantItemContext* ctx) : ASTNode(kind_) {
    this->name = ctx->identifier()->getText();
    this->type = CheckType(ctx->typeRef());
    this->value = CheckConstValue(ctx->constValue());
}
ImplItemNode::ImplItemNode(const ASTNodeType kind_,rx::Parser::InherentImplContext* ctx) : ASTNode(kind_) {
    rx::Parser::TypeRefContext* type = ctx->typeRef();
    this->type = CheckType(type);
    std::vector<rx::Parser::AssociatedItemContext*> items = ctx->associatedItem();
    for(auto item : items){
        rx::Parser::ConstantItemContext* is_const_item = item->constantItem();
        rx::Parser::FunctionDefinitionContext* is_func_item = item->functionDefinition();
        if(is_const_item != nullptr){
            this->associatedItems.push_back(new ConstItemNode(ConstItem,is_const_item));
        }
        else if(is_func_item != nullptr){
            this->associatedItems.push_back(new FnItemNode(FnItem,is_func_item));
        }
    }
}
// statements
LetStmtNode::LetStmtNode(const ASTNodeType kind_,rx::Parser::LetStatementContext* ctx) : ASTNode(kind_) {
    this->name = ctx->identifierBinding()->identifier()->getText();
    if(ctx->typeRef() != nullptr){
        this->type = CheckType(ctx->typeRef());
    }
    if(ctx->identifierBinding()->MUT() != nullptr){
        this->mut = true;
    }
    else{
        this->mut = false;
    }
    rx::Parser::ExpressionContext* expr = ctx->expression();
    this->expr = new AssignExprNode(AssignExpr,expr->assignmentExpression());
}
ExprStmtNode::ExprStmtNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx) : ASTNode(kind_) {
    // dynamic_cast一下判断是那种expr
    auto is_expr_with_block = dynamic_cast<rx::Parser::ExpressionWithBlockContext*>(ctx);
    if(is_expr_with_block != nullptr){
        auto is_block_expr = is_expr_with_block->blockExpression();
        auto is_if_expr = is_expr_with_block->ifExpression();
        auto is_cond_expr = is_expr_with_block->conditionExpression();
        auto is_loop_expr = is_expr_with_block->LOOP();
        auto is_while_expr = is_expr_with_block->WHILE();
        if(is_while_expr != nullptr){
            this->expr = new WhileExprNode(WhileExpr,is_cond_expr,is_block_expr);
        }
        else if(is_loop_expr != nullptr){
            this->expr = new LoopExprNode(LoopExpr,is_block_expr);
        }
        else if(is_if_expr){
            this->expr = new IfExprNode(IfExpr,is_if_expr);
        }
        else{
            this->expr = new BlockExprNode(BlockExpr,is_block_expr);
        }
    }
    else{
        // assignment
        auto is_expr = dynamic_cast<rx::Parser::ExpressionContext*>(ctx);
        auto is_cond_expr = dynamic_cast<rx::Parser::ConditionExpressionContext*>(ctx);
        auto is_stmt_expr = dynamic_cast<rx::Parser::StatementExpressionContext*>(ctx);
        auto is_cb_expr = dynamic_cast<rx::Parser::ConditionBreakExpressionContext*>(ctx);
        if(is_expr != nullptr){
            this->expr = new AssignExprNode(AssignExpr,is_expr->assignmentExpression());
        }
        if(is_cond_expr != nullptr){
            this->expr = new AssignExprNode(AssignExpr,is_cond_expr->conditionAssignmentExpression());
        }
        if(is_stmt_expr != nullptr) {
            this->expr = new AssignExprNode(AssignExpr,is_stmt_expr->statementAssignmentExpression());
        }
        if(is_cb_expr != nullptr) {
            this->expr = new AssignExprNode(AssignExpr,is_cb_expr->conditionBreakAssignmentExpression());
        }
    }
}
// expressions
IntLitNode::IntLitNode(const ASTNodeType kind_,std::string value_) : ASTNode(kind_) {
    this->value = StringToInt(value_,this->suffix);
}
BoolLitNode::BoolLitNode(const ASTNodeType kind_,bool value_) : ASTNode(kind_) {
    this->value = value_;
}
AssignExprNode::AssignExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx) : ASTNode(kind_) {
    auto normal_ptr = dynamic_cast<rx::Parser::AssignmentExpressionContext*>(ctx);
    auto cond_ptr = dynamic_cast<rx::Parser::ConditionAssignmentExpressionContext*>(ctx);
    auto stmt_ptr = dynamic_cast<rx::Parser::StatementAssignmentExpressionContext*>(ctx);
    auto cb_ptr = dynamic_cast<rx::Parser::ConditionBreakAssignmentExpressionContext*>(ctx);
    if(normal_ptr != nullptr){
        this->left = new BinaryExprNode(BinaryExpr,normal_ptr->logicalOrExpression());
        if(normal_ptr->expression() != nullptr){
            this->right = new AssignExprNode(AssignExpr,normal_ptr->expression()->assignmentExpression());
        }
        if(normal_ptr->assignmentOperator() != nullptr){
            this->op = normal_ptr->assignmentOperator()->getText();
        }
    }
    if(cond_ptr != nullptr){
        this->left = new BinaryExprNode(BinaryExpr,cond_ptr->conditionLogicalOrExpression());
        if(cond_ptr->conditionExpression() != nullptr){
            this->right = new AssignExprNode(AssignExpr,cond_ptr->conditionExpression()->conditionAssignmentExpression());
        }
        if(cond_ptr->assignmentOperator() != nullptr){
            this->op = cond_ptr->assignmentOperator()->getText();
        }
    }
    if(stmt_ptr != nullptr){
        this->left = new BinaryExprNode(BinaryExpr,stmt_ptr->statementLogicalOrExpression());
        if(stmt_ptr->expression() != nullptr){
            this->right = new AssignExprNode(AssignExpr,stmt_ptr->expression()->assignmentExpression());
        }
        if(stmt_ptr->assignmentOperator() != nullptr){
            this->op = stmt_ptr->assignmentOperator()->getText();
        }
    }
    if(cb_ptr != nullptr){
        this->left = new BinaryExprNode(BinaryExpr,cb_ptr->conditionBreakLogicalOrExpression());
        if(cb_ptr->conditionExpression() != nullptr){
            this->right = new AssignExprNode(AssignExpr,cb_ptr->conditionExpression()->conditionAssignmentExpression());
        }
        if(cb_ptr->assignmentOperator() != nullptr){
            this->op = cb_ptr->assignmentOperator()->getText();
        }
    }
}
IfExprNode::IfExprNode(const ASTNodeType kind_,rx::Parser::IfExpressionContext* ctx) : ASTNode(kind_) {
    auto cond = ctx->conditionExpression();
    this->condition = new AssignExprNode(AssignExpr,cond->conditionAssignmentExpression());
    std::vector<rx::Parser::BlockExpressionContext*> blocks = ctx->blockExpression();
    int num_of_blocks = blocks.size();
    if(num_of_blocks >= 1){
        this->if_block = new BlockExprNode(BlockExpr,blocks[0]);
    }
    if(num_of_blocks == 2){
        this->else_block = new BlockExprNode(BlockExpr,blocks[1]);
    }
    if(ctx->ELSE() != nullptr && ctx->ifExpression() != nullptr){
        this->else_block = new IfExprNode(IfExpr,ctx->ifExpression());
    }
}
WhileExprNode::WhileExprNode(const ASTNodeType kind_,rx::Parser::ConditionExpressionContext* ctx1,rx::Parser::BlockExpressionContext* ctx2) : ASTNode(kind_) {
    this->condition = new AssignExprNode(AssignExpr,ctx1->conditionAssignmentExpression());
    this->content = new BlockExprNode(BlockExpr,ctx2);
}
LoopExprNode::LoopExprNode(const ASTNodeType kind_,rx::Parser::BlockExpressionContext* ctx) : ASTNode(kind_) {
    this->content = new BlockExprNode(BlockExpr,ctx);
}
BlockExprNode::BlockExprNode(const ASTNodeType kind_,rx::Parser::BlockExpressionContext* ctx) : ASTNode(kind_) {
    std::vector<rx::Parser::StatementContext*> statements = ctx->statement();
    for(auto statement : statements){
        auto is_let_stmt = statement->letStatement();
        auto is_expr_with_block = statement->expressionWithBlock();
        auto is_stmt_expr = statement->statementExpression();
        if(is_let_stmt != nullptr){
            this->statements.push_back(new LetStmtNode(LetStmt,is_let_stmt));
        }
        else if(is_expr_with_block != nullptr){
            this->statements.push_back(new ExprStmtNode(ExprStmt,is_expr_with_block));
        }
        else if(is_stmt_expr != nullptr) {
            this->statements.push_back(new ExprStmtNode(ExprStmt,is_stmt_expr));
        }
    }
    if(ctx->statementExpression() != nullptr){
        this->return_expression = new AssignExprNode(AssignExpr,ctx->statementExpression()->statementAssignmentExpression());
    }
}
BinaryExprNode::BinaryExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx) : ASTNode(kind_) {
    // OROR
    auto is_logic_or = dynamic_cast<rx::Parser::LogicalOrExpressionContext*>(ctx);
    auto is_cond_logic_or = dynamic_cast<rx::Parser::ConditionLogicalOrExpressionContext*>(ctx);
    auto is_stmt_logic_or = dynamic_cast<rx::Parser::StatementLogicalOrExpressionContext*>(ctx);
    auto is_cb_logic_or = dynamic_cast<rx::Parser::ConditionBreakLogicalOrExpressionContext*>(ctx);
    if(is_logic_or != nullptr){
        std::vector<rx::Parser::LogicalAndExpressionContext*> operands = is_logic_or->logicalAndExpression();
        for(auto operand : operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            this->op.push_back("||");
        }
        this->op.pop_back();
    }
    if(is_cond_logic_or != nullptr){
        std::vector<rx::Parser::ConditionLogicalAndExpressionContext*> operands = is_cond_logic_or->conditionLogicalAndExpression();
        for(auto operand : operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            this->op.push_back("||");
        }
        this->op.pop_back();
    }
    if(is_stmt_logic_or != nullptr){
        rx::Parser::StatementLogicalAndExpressionContext* first_operand = is_stmt_logic_or->statementLogicalAndExpression();
        std::vector<rx::Parser::LogicalAndExpressionContext*> following_operands = is_stmt_logic_or->logicalAndExpression();
        this->operands.push_back(new BinaryExprNode(BinaryExpr,first_operand));
        for(auto operand : following_operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            this->op.push_back("||");
        }
    }
    if(is_cb_logic_or != nullptr){
        rx::Parser::ConditionBreakLogicalAndExpressionContext* first_operand = is_cb_logic_or->conditionBreakLogicalAndExpression();
        std::vector<rx::Parser::ConditionLogicalAndExpressionContext*> following_operands = is_cb_logic_or->conditionLogicalAndExpression();
        this->operands.push_back(new BinaryExprNode(BinaryExpr,first_operand));
        for(auto operand : following_operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            this->op.push_back("||");
        }
    }
    // ANDAND
    auto is_logic_and = dynamic_cast<rx::Parser::LogicalAndExpressionContext*>(ctx);
    auto is_cond_logic_and = dynamic_cast<rx::Parser::ConditionLogicalAndExpressionContext*>(ctx);
    auto is_stmt_logic_and = dynamic_cast<rx::Parser::StatementLogicalAndExpressionContext*>(ctx);
    auto is_cb_logic_and = dynamic_cast<rx::Parser::ConditionBreakLogicalAndExpressionContext*>(ctx);
    if(is_logic_and != nullptr){
        std::vector<rx::Parser::ComparisonExpressionContext*> operands = is_logic_and->comparisonExpression();
        for(auto operand : operands){
            this->op.push_back("&&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_cond_logic_and != nullptr){
        std::vector<rx::Parser::ConditionComparisonExpressionContext*> operands = is_cond_logic_and->conditionComparisonExpression();
        for(auto operand : operands){
            this->op.push_back("&&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_stmt_logic_and != nullptr){
        rx::Parser::StatementComparisonExpressionContext* first_operand = is_stmt_logic_and->statementComparisonExpression();
        std::vector<rx::Parser::ComparisonExpressionContext*> following_operands = is_stmt_logic_and->comparisonExpression();
        this->operands.push_back(new BinaryExprNode(BinaryExpr,first_operand));
        for(auto operand : following_operands){
            this->op.push_back("&&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_cb_logic_and != nullptr){
        rx::Parser::ConditionBreakComparisonExpressionContext* first_operand = is_cb_logic_and->conditionBreakComparisonExpression();
        std::vector<rx::Parser::ConditionComparisonExpressionContext*> following_operands = is_cb_logic_and->conditionComparisonExpression();
        this->operands.push_back(new BinaryExprNode(BinaryExpr,first_operand));
        for(auto operand : following_operands){
            this->op.push_back("&&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    // Comparison
    auto is_cmp = dynamic_cast<rx::Parser::ComparisonExpressionContext*>(ctx);
    auto is_cond_cmp = dynamic_cast<rx::Parser::ConditionComparisonExpressionContext*>(ctx);
    auto is_stmt_cmp = dynamic_cast<rx::Parser::StatementComparisonExpressionContext*>(ctx);
    auto is_cb_cmp = dynamic_cast<rx::Parser::ConditionBreakComparisonExpressionContext*>(ctx);
    if(is_cmp != nullptr){
        if(is_cmp->closedBitOrExpression() != nullptr){
            this->op.push_back("<");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cmp->closedBitOrExpression()));
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cmp->bitOrExpression(0)));
        }
        else{
            if(is_cmp->comparisonExceptLt() != nullptr){
                this->op.push_back(is_cmp->comparisonExceptLt()->getText());
            }
            std::vector<rx::Parser::BitOrExpressionContext*> operands = is_cmp->bitOrExpression();
            for(auto operand : operands){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
        }
    }
    if(is_cond_cmp != nullptr){
        if(is_cond_cmp->conditionClosedBitOrExpression() != nullptr){
            this->op.push_back("<");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cond_cmp->conditionClosedBitOrExpression()));
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cond_cmp->conditionBitOrExpression(0)));
        }
        else{
            if(is_cond_cmp->comparisonExceptLt() != nullptr){
                this->op.push_back(is_cond_cmp->comparisonExceptLt()->getText());
            }
            std::vector<rx::Parser::ConditionBitOrExpressionContext*> operands = is_cond_cmp->conditionBitOrExpression();
            for(auto operand : operands){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
        }
    }
    if(is_stmt_cmp != nullptr){
        if(is_stmt_cmp->statementClosedBitOrExpression() != nullptr){
            this->op.push_back("<");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_cmp->statementClosedBitOrExpression()));
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_cmp->bitOrExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_cmp->statementBitOrExpression()));
            if(is_stmt_cmp->comparisonExceptLt() != nullptr){
                this->op.push_back(is_stmt_cmp->comparisonExceptLt()->getText());
            }
            if(is_stmt_cmp->bitOrExpression() != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_cmp->bitOrExpression()));
            }
        }
    }
    if(is_cb_cmp != nullptr){
        if(is_cb_cmp->conditionBreakClosedBitOrExpression() != nullptr){
            this->op.push_back("<");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_cmp->conditionBreakClosedBitOrExpression()));
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_cmp->conditionBitOrExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_cmp->conditionBreakBitOrExpression()));
            if(is_cb_cmp->comparisonExceptLt() != nullptr){
                this->op.push_back(is_cb_cmp->comparisonExceptLt()->getText());
            }
            if(is_cb_cmp->conditionBitOrExpression() != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_cmp->conditionBitOrExpression()));
            }
        }
    }
    // BitOr
    auto is_bit_or = dynamic_cast<rx::Parser::BitOrExpressionContext*>(ctx);
    auto is_closed_bit_or = dynamic_cast<rx::Parser::ClosedBitOrExpressionContext*>(ctx);
    auto is_cond_bit_or = dynamic_cast<rx::Parser::ConditionBitOrExpressionContext*>(ctx);
    auto is_cond_closed_bit_or = dynamic_cast<rx::Parser::ConditionClosedBitOrExpressionContext*>(ctx);
    auto is_stmt_bit_or = dynamic_cast<rx::Parser::StatementBitOrExpressionContext*>(ctx);
    auto is_stmt_closed_bit_or = dynamic_cast<rx::Parser::StatementClosedBitOrExpressionContext*>(ctx);
    auto is_cb_bit_or = dynamic_cast<rx::Parser::ConditionBreakBitOrExpressionContext*>(ctx);
    auto is_cb_closed_bit_or = dynamic_cast<rx::Parser::ConditionBreakClosedBitOrExpressionContext*>(ctx);
    if(is_bit_or != nullptr){
        std::vector<rx::Parser::BitXorExpressionContext*> operands = is_bit_or->bitXorExpression();
        for(auto operand : operands){
            this->op.push_back("|");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_closed_bit_or != nullptr){
        std::vector<rx::Parser::BitXorExpressionContext*> operands = is_closed_bit_or->bitXorExpression();
        for(auto operand : operands){
            this->op.push_back("|");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_closed_bit_or->closedBitXorExpression()));
    }
    if(is_cond_bit_or != nullptr){
        std::vector<rx::Parser::ConditionBitXorExpressionContext*> operands = is_cond_bit_or->conditionBitXorExpression();
        for(auto operand : operands){
            this->op.push_back("|");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_cond_closed_bit_or != nullptr){
        std::vector<rx::Parser::ConditionBitXorExpressionContext*> operands = is_cond_closed_bit_or->conditionBitXorExpression();
        for(auto operand : operands){
            this->op.push_back("|");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cond_closed_bit_or->conditionClosedBitXorExpression()));
    }
    if(is_stmt_bit_or != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_bit_or->statementBitXorExpression()));
        std::vector<rx::Parser::BitXorExpressionContext*> following_operands = is_stmt_bit_or->bitXorExpression();
        for(auto operand : following_operands){
            this->op.push_back("|");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_stmt_closed_bit_or != nullptr){
        if(is_stmt_closed_bit_or->statementClosedBitXorExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_or->statementClosedBitXorExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_or->statementBitXorExpression()));
            this->op.push_back("|");
            std::vector<rx::Parser::BitXorExpressionContext*> following_operands = is_stmt_closed_bit_or->bitXorExpression();
            for(auto operand : following_operands){
                this->op.push_back("|");
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_or->closedBitXorExpression()));
        }
    }
    if(is_cb_bit_or != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_bit_or->conditionBreakBitXorExpression()));
        std::vector<rx::Parser::ConditionBitXorExpressionContext*> following_operands = is_cb_bit_or->conditionBitXorExpression();
        for(auto operand : following_operands){
            this->op.push_back("|");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_cb_closed_bit_or != nullptr){
        if(is_cb_closed_bit_or->conditionBreakClosedBitXorExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_or->conditionBreakClosedBitXorExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_or->conditionBreakBitXorExpression()));
            this->op.push_back("|");
            std::vector<rx::Parser::ConditionBitXorExpressionContext*> following_operands = is_cb_closed_bit_or->conditionBitXorExpression();
            for(auto operand : following_operands){
                this->op.push_back("|");
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_or->conditionClosedBitXorExpression()));
        }
    }

    // BitXor
    auto is_bit_xor = dynamic_cast<rx::Parser::BitXorExpressionContext*>(ctx);
    auto is_closed_bit_xor = dynamic_cast<rx::Parser::ClosedBitXorExpressionContext*>(ctx);
    auto is_cond_bit_xor = dynamic_cast<rx::Parser::ConditionBitXorExpressionContext*>(ctx);
    auto is_cond_closed_bit_xor = dynamic_cast<rx::Parser::ConditionClosedBitXorExpressionContext*>(ctx);
    auto is_stmt_bit_xor = dynamic_cast<rx::Parser::StatementBitXorExpressionContext*>(ctx);
    auto is_stmt_closed_bit_xor = dynamic_cast<rx::Parser::StatementClosedBitXorExpressionContext*>(ctx);
    auto is_cb_bit_xor = dynamic_cast<rx::Parser::ConditionBreakBitXorExpressionContext*>(ctx);
    auto is_cb_closed_bit_xor = dynamic_cast<rx::Parser::ConditionBreakClosedBitXorExpressionContext*>(ctx);
    if(is_bit_xor != nullptr){
        std::vector<rx::Parser::BitAndExpressionContext*> operands = is_bit_xor->bitAndExpression();
        for(auto operand : operands){
            this->op.push_back("^");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_closed_bit_xor != nullptr){
        std::vector<rx::Parser::BitAndExpressionContext*> operands = is_closed_bit_xor->bitAndExpression();
        for(auto operand : operands){
            this->op.push_back("^");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_closed_bit_xor->closedBitAndExpression()));
    }
    if(is_cond_bit_xor != nullptr){
        std::vector<rx::Parser::ConditionBitAndExpressionContext*> operands = is_cond_bit_xor->conditionBitAndExpression();
        for(auto operand : operands){
            this->op.push_back("^");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_cond_closed_bit_xor != nullptr){
        std::vector<rx::Parser::ConditionBitAndExpressionContext*> operands = is_cond_closed_bit_xor->conditionBitAndExpression();
        for(auto operand : operands){
            this->op.push_back("^");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cond_closed_bit_xor->conditionClosedBitAndExpression()));
    }
    if(is_stmt_bit_xor != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_bit_xor->statementBitAndExpression()));
        std::vector<rx::Parser::BitAndExpressionContext*> following_operands = is_stmt_bit_xor->bitAndExpression();
        for(auto operand : following_operands){
            this->op.push_back("^");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_stmt_closed_bit_xor != nullptr){
        if(is_stmt_closed_bit_xor->statementClosedBitAndExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_xor->statementClosedBitAndExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_xor->statementBitAndExpression()));
            this->op.push_back("^");
            std::vector<rx::Parser::BitAndExpressionContext*> following_operands = is_stmt_closed_bit_xor->bitAndExpression();
            for(auto operand : following_operands){
                this->op.push_back("^");
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_xor->closedBitAndExpression()));
        }
    }
    if(is_cb_bit_xor != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_bit_xor->conditionBreakBitAndExpression()));
        std::vector<rx::Parser::ConditionBitAndExpressionContext*> following_operands = is_cb_bit_xor->conditionBitAndExpression();
        for(auto operand : following_operands){
            this->op.push_back("^");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_cb_closed_bit_xor != nullptr){
        if(is_cb_closed_bit_xor->conditionBreakClosedBitAndExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_xor->conditionBreakClosedBitAndExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_xor->conditionBreakBitAndExpression()));
            this->op.push_back("^");
            std::vector<rx::Parser::ConditionBitAndExpressionContext*> following_operands = is_cb_closed_bit_xor->conditionBitAndExpression();
            for(auto operand : following_operands){
                this->op.push_back("^");
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_xor->conditionClosedBitAndExpression()));
        }
    }

    // BitAnd
    auto is_bit_and = dynamic_cast<rx::Parser::BitAndExpressionContext*>(ctx);
    auto is_closed_bit_and = dynamic_cast<rx::Parser::ClosedBitAndExpressionContext*>(ctx);
    auto is_cond_bit_and = dynamic_cast<rx::Parser::ConditionBitAndExpressionContext*>(ctx);
    auto is_cond_closed_bit_and = dynamic_cast<rx::Parser::ConditionClosedBitAndExpressionContext*>(ctx);
    auto is_stmt_bit_and = dynamic_cast<rx::Parser::StatementBitAndExpressionContext*>(ctx);
    auto is_stmt_closed_bit_and = dynamic_cast<rx::Parser::StatementClosedBitAndExpressionContext*>(ctx);
    auto is_cb_bit_and = dynamic_cast<rx::Parser::ConditionBreakBitAndExpressionContext*>(ctx);
    auto is_cb_closed_bit_and = dynamic_cast<rx::Parser::ConditionBreakClosedBitAndExpressionContext*>(ctx);
    if(is_bit_and != nullptr){
        std::vector<rx::Parser::ShiftExpressionContext*> operands = is_bit_and->shiftExpression();
        for(auto operand : operands){
            this->op.push_back("&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_closed_bit_and != nullptr){
        std::vector<rx::Parser::ShiftExpressionContext*> operands = is_closed_bit_and->shiftExpression();
        for(auto operand : operands){
            this->op.push_back("&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_closed_bit_and->closedShiftExpression()));
    }
    if(is_cond_bit_and != nullptr){
        std::vector<rx::Parser::ConditionShiftExpressionContext*> operands = is_cond_bit_and->conditionShiftExpression();
        for(auto operand : operands){
            this->op.push_back("&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->op.pop_back();
    }
    if(is_cond_closed_bit_and != nullptr){
        std::vector<rx::Parser::ConditionShiftExpressionContext*> operands = is_cond_closed_bit_and->conditionShiftExpression();
        for(auto operand : operands){
            this->op.push_back("&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cond_closed_bit_and->conditionClosedShiftExpression()));
    }
    if(is_stmt_bit_and != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_bit_and->statementShiftExpression()));
        std::vector<rx::Parser::ShiftExpressionContext*> following_operands = is_stmt_bit_and->shiftExpression();
        for(auto operand : following_operands){
            this->op.push_back("&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_stmt_closed_bit_and != nullptr){
        if(is_stmt_closed_bit_and->statementClosedShiftExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_and->statementClosedShiftExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_and->statementShiftExpression()));
            this->op.push_back("&");
            std::vector<rx::Parser::ShiftExpressionContext*> following_operands = is_stmt_closed_bit_and->shiftExpression();
            for(auto operand : following_operands){
                this->op.push_back("&");
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_bit_and->closedShiftExpression()));
        }
    }
    if(is_cb_bit_and != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_bit_and->conditionBreakShiftExpression()));
        std::vector<rx::Parser::ConditionShiftExpressionContext*> following_operands = is_cb_bit_and->conditionShiftExpression();
        for(auto operand : following_operands){
            this->op.push_back("&");
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
    }
    if(is_cb_closed_bit_and != nullptr){
        if(is_cb_closed_bit_and->conditionBreakClosedShiftExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_and->conditionBreakClosedShiftExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_and->conditionBreakShiftExpression()));
            this->op.push_back("&");
            std::vector<rx::Parser::ConditionShiftExpressionContext*> following_operands = is_cb_closed_bit_and->conditionShiftExpression();
            for(auto operand : following_operands){
                this->op.push_back("&");
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_bit_and->conditionClosedShiftExpression()));
        }
    }

    // Shift
    auto is_shift = dynamic_cast<rx::Parser::ShiftExpressionContext*>(ctx);
    auto is_closed_shift = dynamic_cast<rx::Parser::ClosedShiftExpressionContext*>(ctx);
    auto is_cond_shift = dynamic_cast<rx::Parser::ConditionShiftExpressionContext*>(ctx);
    auto is_cond_closed_shift = dynamic_cast<rx::Parser::ConditionClosedShiftExpressionContext*>(ctx);
    auto is_stmt_shift = dynamic_cast<rx::Parser::StatementShiftExpressionContext*>(ctx);
    auto is_stmt_closed_shift = dynamic_cast<rx::Parser::StatementClosedShiftExpressionContext*>(ctx);
    auto is_cb_shift = dynamic_cast<rx::Parser::ConditionBreakShiftExpressionContext*>(ctx);
    auto is_cb_closed_shift = dynamic_cast<rx::Parser::ConditionBreakClosedShiftExpressionContext*>(ctx);
    if(is_shift != nullptr){
        // closedAdditiveExpression 与 additiveExpression 在 children 中按出现顺序排列
        for(auto child : is_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::AdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_closed_shift != nullptr){
        for(auto child : is_closed_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::AdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_cond_shift != nullptr){
        for(auto child : is_cond_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::ConditionAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_cond_closed_shift != nullptr){
        for(auto child : is_cond_closed_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::ConditionAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_stmt_shift != nullptr){
        for(auto child : is_stmt_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::StatementAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::StatementClosedAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::AdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_stmt_closed_shift != nullptr){
        for(auto child : is_stmt_closed_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::StatementAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::StatementClosedAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::AdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_cb_shift != nullptr){
        for(auto child : is_cb_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::ConditionBreakAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionBreakClosedAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }
    if(is_cb_closed_shift != nullptr){
        for(auto child : is_cb_closed_shift->children){
            auto operand = dynamic_cast<antlr4::ParserRuleContext*>(child);
            if(dynamic_cast<rx::Parser::ConditionBreakAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionBreakClosedAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionAdditiveExpressionContext*>(child) != nullptr ||
               dynamic_cast<rx::Parser::ConditionClosedAdditiveExpressionContext*>(child) != nullptr){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            auto shift_right = dynamic_cast<rx::Parser::ShiftRightContext*>(child);
            if(shift_right != nullptr){
                this->op.push_back(">>");
            }
            else{
                auto shift_left = dynamic_cast<antlr4::tree::TerminalNode*>(child);
                if(shift_left != nullptr && shift_left->getSymbol()->getType() == rx::Parser::SHL){
                    this->op.push_back("<<");
                }
            }
        }
    }

    // Additive
    auto is_add = dynamic_cast<rx::Parser::AdditiveExpressionContext*>(ctx);
    auto is_closed_add = dynamic_cast<rx::Parser::ClosedAdditiveExpressionContext*>(ctx);
    auto is_cond_add = dynamic_cast<rx::Parser::ConditionAdditiveExpressionContext*>(ctx);
    auto is_cond_closed_add = dynamic_cast<rx::Parser::ConditionClosedAdditiveExpressionContext*>(ctx);
    auto is_stmt_add = dynamic_cast<rx::Parser::StatementAdditiveExpressionContext*>(ctx);
    auto is_stmt_closed_add = dynamic_cast<rx::Parser::StatementClosedAdditiveExpressionContext*>(ctx);
    auto is_cb_add = dynamic_cast<rx::Parser::ConditionBreakAdditiveExpressionContext*>(ctx);
    auto is_cb_closed_add = dynamic_cast<rx::Parser::ConditionBreakClosedAdditiveExpressionContext*>(ctx);
    if(is_add != nullptr){
        std::vector<rx::Parser::MultiplicativeExpressionContext*> operands = is_add->multiplicativeExpression();
        for(auto operand : operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_closed_add != nullptr){
        std::vector<rx::Parser::MultiplicativeExpressionContext*> operands = is_closed_add->multiplicativeExpression();
        for(auto operand : operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_closed_add->closedMultiplicativeExpression()));
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_closed_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cond_add != nullptr){
        std::vector<rx::Parser::ConditionMultiplicativeExpressionContext*> operands = is_cond_add->conditionMultiplicativeExpression();
        for(auto operand : operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_cond_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cond_closed_add != nullptr){
        std::vector<rx::Parser::ConditionMultiplicativeExpressionContext*> operands = is_cond_closed_add->conditionMultiplicativeExpression();
        for(auto operand : operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cond_closed_add->conditionClosedMultiplicativeExpression()));
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_cond_closed_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_stmt_add != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_add->statementMultiplicativeExpression()));
        std::vector<rx::Parser::MultiplicativeExpressionContext*> following_operands = is_stmt_add->multiplicativeExpression();
        for(auto operand : following_operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_stmt_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_stmt_closed_add != nullptr){
        if(is_stmt_closed_add->statementClosedMultiplicativeExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_add->statementClosedMultiplicativeExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_add->statementMultiplicativeExpression()));
            std::vector<rx::Parser::MultiplicativeExpressionContext*> following_operands = is_stmt_closed_add->multiplicativeExpression();
            for(auto operand : following_operands){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_stmt_closed_add->closedMultiplicativeExpression()));
        }
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_stmt_closed_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cb_add != nullptr){
        this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_add->conditionBreakMultiplicativeExpression()));
        std::vector<rx::Parser::ConditionMultiplicativeExpressionContext*> following_operands = is_cb_add->conditionMultiplicativeExpression();
        for(auto operand : following_operands){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
        }
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_cb_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cb_closed_add != nullptr){
        if(is_cb_closed_add->conditionBreakClosedMultiplicativeExpression() != nullptr){
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_add->conditionBreakClosedMultiplicativeExpression()));
        }
        else{
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_add->conditionBreakMultiplicativeExpression()));
            std::vector<rx::Parser::ConditionMultiplicativeExpressionContext*> following_operands = is_cb_closed_add->conditionMultiplicativeExpression();
            for(auto operand : following_operands){
                this->operands.push_back(new BinaryExprNode(BinaryExpr,operand));
            }
            this->operands.push_back(new BinaryExprNode(BinaryExpr,is_cb_closed_add->conditionClosedMultiplicativeExpression()));
        }
        std::vector<rx::Parser::AdditiveOperatorContext*> ops = is_cb_closed_add->additiveOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }

    // Multiplicative
    auto is_mul = dynamic_cast<rx::Parser::MultiplicativeExpressionContext*>(ctx);
    auto is_closed_mul = dynamic_cast<rx::Parser::ClosedMultiplicativeExpressionContext*>(ctx);
    auto is_cond_mul = dynamic_cast<rx::Parser::ConditionMultiplicativeExpressionContext*>(ctx);
    auto is_cond_closed_mul = dynamic_cast<rx::Parser::ConditionClosedMultiplicativeExpressionContext*>(ctx);
    auto is_stmt_mul = dynamic_cast<rx::Parser::StatementMultiplicativeExpressionContext*>(ctx);
    auto is_stmt_closed_mul = dynamic_cast<rx::Parser::StatementClosedMultiplicativeExpressionContext*>(ctx);
    auto is_cb_mul = dynamic_cast<rx::Parser::ConditionBreakMultiplicativeExpressionContext*>(ctx);
    auto is_cb_closed_mul = dynamic_cast<rx::Parser::ConditionBreakClosedMultiplicativeExpressionContext*>(ctx);
    if(is_mul != nullptr){
        std::vector<rx::Parser::CastExpressionContext*> operands = is_mul->castExpression();
        for(auto operand : operands){
            this->operands.push_back(new CastExprNode(CastExpr,operand));
        }
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_closed_mul != nullptr){
        std::vector<rx::Parser::CastExpressionContext*> operands = is_closed_mul->castExpression();
        for(auto operand : operands){
            this->operands.push_back(new CastExprNode(CastExpr,operand));
        }
        this->operands.push_back(new CastExprNode(CastExpr,is_closed_mul->closedCastExpression()));
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_closed_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cond_mul != nullptr){
        std::vector<rx::Parser::ConditionCastExpressionContext*> operands = is_cond_mul->conditionCastExpression();
        for(auto operand : operands){
            this->operands.push_back(new CastExprNode(CastExpr,operand));
        }
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_cond_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cond_closed_mul != nullptr){
        std::vector<rx::Parser::ConditionCastExpressionContext*> operands = is_cond_closed_mul->conditionCastExpression();
        for(auto operand : operands){
            this->operands.push_back(new CastExprNode(CastExpr,operand));
        }
        this->operands.push_back(new CastExprNode(CastExpr,is_cond_closed_mul->conditionClosedCastExpression()));
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_cond_closed_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_stmt_mul != nullptr){
        this->operands.push_back(new CastExprNode(CastExpr,is_stmt_mul->statementCastExpression()));
        std::vector<rx::Parser::CastExpressionContext*> following_operands = is_stmt_mul->castExpression();
        for(auto operand : following_operands){
            this->operands.push_back(new CastExprNode(CastExpr,operand));
        }
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_stmt_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_stmt_closed_mul != nullptr){
        if(is_stmt_closed_mul->statementClosedCastExpression() != nullptr){
            this->operands.push_back(new CastExprNode(CastExpr,is_stmt_closed_mul->statementClosedCastExpression()));
        }
        else{
            this->operands.push_back(new CastExprNode(CastExpr,is_stmt_closed_mul->statementCastExpression()));
            std::vector<rx::Parser::CastExpressionContext*> following_operands = is_stmt_closed_mul->castExpression();
            for(auto operand : following_operands){
                this->operands.push_back(new CastExprNode(CastExpr,operand));
            }
            this->operands.push_back(new CastExprNode(CastExpr,is_stmt_closed_mul->closedCastExpression()));
        }
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_stmt_closed_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cb_mul != nullptr){
        this->operands.push_back(new CastExprNode(CastExpr,is_cb_mul->conditionBreakCastExpression()));
        std::vector<rx::Parser::ConditionCastExpressionContext*> following_operands = is_cb_mul->conditionCastExpression();
        for(auto operand : following_operands){
            this->operands.push_back(new CastExprNode(CastExpr,operand));
        }
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_cb_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
    if(is_cb_closed_mul != nullptr){
        if(is_cb_closed_mul->conditionBreakClosedCastExpression() != nullptr){
            this->operands.push_back(new CastExprNode(CastExpr,is_cb_closed_mul->conditionBreakClosedCastExpression()));
        }
        else{
            this->operands.push_back(new CastExprNode(CastExpr,is_cb_closed_mul->conditionBreakCastExpression()));
            std::vector<rx::Parser::ConditionCastExpressionContext*> following_operands = is_cb_closed_mul->conditionCastExpression();
            for(auto operand : following_operands){
                this->operands.push_back(new CastExprNode(CastExpr,operand));
            }
            this->operands.push_back(new CastExprNode(CastExpr,is_cb_closed_mul->conditionClosedCastExpression()));
        }
        std::vector<rx::Parser::MultiplicativeOperatorContext*> ops = is_cb_closed_mul->multiplicativeOperator();
        for(auto op : ops){
            this->op.push_back(op->getText());
        }
    }
}
PathExprNode::PathExprNode(const ASTNodeType kind_,rx::Parser::PathInExpressionContext* ctx) : ASTNode(kind_) {
    for(auto seg : ctx->pathExprSegment()){
        this->segments.push_back(seg->pathIdentSegment()->getText());
    }
}
StructExprNode::StructExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
ArrayExprNode::ArrayExprNode(const ASTNodeType kind_,rx::Parser::ArrayExpressionContext* ctx) : ASTNode(kind_) {
    for(auto expr : ctx->expression()){
        this->elements.push_back(new AssignExprNode(AssignExpr,expr->assignmentExpression()));
    }
}
ArrayRepeatNode::ArrayRepeatNode(const ASTNodeType kind_) : ASTNode(kind_) {}
BreakExprNode::BreakExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
ContinueExprNode::ContinueExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
ReturnExprNode::ReturnExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
CallExprNode::CallExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
MethodCallExprNode::MethodCallExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
FieldExprNode::FieldExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
IndexExprNode::IndexExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
// UnaryExpr辅助构建PostfixExpr函数
static ASTNode* BuildLiteral(rx::Parser::LiteralExpressionContext* ctx){
    if(ctx->INTEGER_LITERAL() != nullptr){
        return new IntLitNode(IntLit,ctx->INTEGER_LITERAL()->getText());
    }
    return new BoolLitNode(BoolLit,ctx->TRUE() != nullptr);
}
static ASTNode* BuildArray(rx::Parser::ArrayExpressionContext* ctx){
    if(ctx->SEMI() != nullptr){
        auto node = new ArrayRepeatNode(ArrayRepeat);
        node->element = new AssignExprNode(AssignExpr,ctx->expression()[0]->assignmentExpression());
        node->num = node->CheckConstValue(ctx->constValue());
        return node;
    }
    return new ArrayExprNode(ArrayExpr,ctx);
}
static ASTNode* BuildDotSuffix(ASTNode* base,rx::Parser::DotSuffixContext* dot){
    if(dot->identifier() != nullptr){
        auto node = new FieldExprNode(FieldExpr);
        node->receiver = base;
        node->name = dot->identifier()->getText();
        return node;
    }
    auto node = new MethodCallExprNode(MethodCallExpr);
    node->receiver = base;
    node->name = dot->pathExprSegment()->pathIdentSegment()->getText();
    for(auto arg : dot->callArguments()->expression()){
        node->args.push_back(new AssignExprNode(AssignExpr,arg->assignmentExpression()));
    }
    return node;
}
// 左结合折叠
static ASTNode* BuildPostfix(ASTNode* base,const std::vector<rx::Parser::PostfixSuffixContext*>& suffixes){
    ASTNode* cur = base;
    for(auto suf : suffixes){
        if(suf->callArguments() != nullptr){
            auto node = new CallExprNode(CallExpr);
            node->func = cur;
            for(auto arg : suf->callArguments()->expression()){
                node->args.push_back(new AssignExprNode(AssignExpr,arg->assignmentExpression()));
            }
            cur = node;
        }
        else if(suf->expression() != nullptr){
            auto node = new IndexExprNode(IndexExpr);
            node->base = cur;
            node->index = new AssignExprNode(AssignExpr,suf->expression()->assignmentExpression());
            cur = node;
        }
        else if(suf->dotSuffix() != nullptr){
            cur = BuildDotSuffix(cur,suf->dotSuffix());
        }
    }
    return cur;
}
// PrimaryExpr
static ASTNode* BuildPrimary(antlr4::ParserRuleContext* ctx){
    auto is_primary = dynamic_cast<rx::Parser::PrimaryExpressionContext*>(ctx);
    auto is_non_block = dynamic_cast<rx::Parser::NonBlockPrimaryContext*>(ctx);
    auto is_cond_primary = dynamic_cast<rx::Parser::ConditionPrimaryContext*>(ctx);
    auto is_cb_primary = dynamic_cast<rx::Parser::ConditionPrimaryWithoutBareBlockContext*>(ctx);
    if(is_primary != nullptr){
        if(is_primary->nonBlockPrimary() != nullptr){
            return BuildPrimary(is_primary->nonBlockPrimary());
        }
        return new ExprStmtNode(ExprStmt,is_primary->expressionWithBlock());
    }
    if(is_cond_primary != nullptr){
        if(is_cond_primary->conditionPrimaryWithoutBareBlock() != nullptr){
            return BuildPrimary(is_cond_primary->conditionPrimaryWithoutBareBlock());
        }
        return new BlockExprNode(BlockExpr,is_cond_primary->blockExpression());
    }
    if(is_non_block != nullptr){
        if(is_non_block->literalExpression() != nullptr){
            return BuildLiteral(is_non_block->literalExpression());
        }
        if(is_non_block->pathInExpression() != nullptr){
            ASTNode* cur = new PathExprNode(PathExpr,is_non_block->pathInExpression());
            if(is_non_block->structExprFields() != nullptr){
                auto node = new StructExprNode(StructExpr);
                for(auto field : is_non_block->structExprFields()->structExprField()){
                    node->member_name.push_back(field->identifier()->getText());
                    node->expr.push_back(new AssignExprNode(AssignExpr,field->expression()->assignmentExpression()));
                }
                node->struct_name = cur;
                cur = node;
            }
            return cur;
        }
        if(is_non_block->LPAREN() != nullptr && is_non_block->RPAREN() != nullptr){
            if(is_non_block->expression() != nullptr){
                return new AssignExprNode(AssignExpr,is_non_block->expression()->assignmentExpression());
            }
            return nullptr;
        }
        if(is_non_block->arrayExpression() != nullptr){
            return BuildArray(is_non_block->arrayExpression());
        }
        if(is_non_block->BREAK() != nullptr){
            auto node = new BreakExprNode(BreakExpr);
            if(is_non_block->expression() != nullptr){
                node->expr = new AssignExprNode(AssignExpr,is_non_block->expression()->assignmentExpression());
            }
            return node;
        }
        if(is_non_block->RETURN() != nullptr){
            auto node = new ReturnExprNode(ReturnExpr);
            if(is_non_block->expression() != nullptr){
                node->expr = new AssignExprNode(AssignExpr,is_non_block->expression()->assignmentExpression());
            }
            return node;
        }
        return new ContinueExprNode(ContinueExpr);
    }
    if(is_cb_primary != nullptr){
        if(is_cb_primary->literalExpression() != nullptr){
            return BuildLiteral(is_cb_primary->literalExpression());
        }
        if(is_cb_primary->pathInExpression() != nullptr){
            return new PathExprNode(PathExpr,is_cb_primary->pathInExpression());
        }
        if(is_cb_primary->LPAREN() != nullptr && is_cb_primary->RPAREN() != nullptr){
            if(is_cb_primary->expression() != nullptr){
                return new AssignExprNode(AssignExpr,is_cb_primary->expression()->assignmentExpression());
            }
            return nullptr; // 空括号 () 暂无对应节点
        }
        if(is_cb_primary->arrayExpression() != nullptr){
            return BuildArray(is_cb_primary->arrayExpression());
        }
        if(is_cb_primary->ifExpression() != nullptr){
            return new IfExprNode(IfExpr,is_cb_primary->ifExpression());
        }
        if(is_cb_primary->LOOP() != nullptr){
            return new LoopExprNode(LoopExpr,is_cb_primary->blockExpression());
        }
        if(is_cb_primary->WHILE() != nullptr){
            return new WhileExprNode(WhileExpr,is_cb_primary->conditionExpression(),is_cb_primary->blockExpression());
        }
        if(is_cb_primary->BREAK() != nullptr){
            auto node = new BreakExprNode(BreakExpr);
            if(is_cb_primary->conditionBreakExpression() != nullptr){
                node->expr = new AssignExprNode(AssignExpr,is_cb_primary->conditionBreakExpression()->conditionBreakAssignmentExpression());
            }
            return node;
        }
        if(is_cb_primary->RETURN() != nullptr){
            auto node = new ReturnExprNode(ReturnExpr);
            if(is_cb_primary->conditionExpression() != nullptr){
                node->expr = new AssignExprNode(AssignExpr,is_cb_primary->conditionExpression()->conditionAssignmentExpression());
            }
            return node;
        }
        return new ContinueExprNode(ContinueExpr);
    }
    return nullptr;
}
UnaryExprNode::UnaryExprNode(const ASTNodeType kind_) : ASTNode(kind_) {}
UnaryExprNode::UnaryExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx) : ASTNode(kind_) {
    auto is_unary = dynamic_cast<rx::Parser::UnaryExpressionContext*>(ctx);
    auto is_cond_unary = dynamic_cast<rx::Parser::ConditionUnaryExpressionContext*>(ctx);
    auto is_stmt_unary = dynamic_cast<rx::Parser::StatementUnaryExpressionContext*>(ctx);
    auto is_cb_unary = dynamic_cast<rx::Parser::ConditionBreakUnaryExpressionContext*>(ctx);
    if(is_unary != nullptr){
        if(is_unary->unaryOperator() != nullptr){
            this->op = is_unary->unaryOperator()->getText();
            this->expr = new UnaryExprNode(UnaryExpr,is_unary->unaryExpression());
        }
        else{
            // postfixExpression : primaryExpression postfixSuffix*
            auto postfix = is_unary->postfixExpression();
            this->expr = BuildPostfix(BuildPrimary(postfix->primaryExpression()),postfix->postfixSuffix());
        }
    }
    if(is_cond_unary != nullptr){
        if(is_cond_unary->unaryOperator() != nullptr){
            this->op = is_cond_unary->unaryOperator()->getText();
            this->expr = new UnaryExprNode(UnaryExpr,is_cond_unary->conditionUnaryExpression());
        }
        else{
            // conditionPostfixExpression : conditionPrimary postfixSuffix*
            auto postfix = is_cond_unary->conditionPostfixExpression();
            this->expr = BuildPostfix(BuildPrimary(postfix->conditionPrimary()),postfix->postfixSuffix());
        }
    }
    if(is_stmt_unary != nullptr){
        if(is_stmt_unary->unaryOperator() != nullptr){
            this->op = is_stmt_unary->unaryOperator()->getText();
            this->expr = new UnaryExprNode(UnaryExpr,is_stmt_unary->unaryExpression());
        }
        else{
            // statementPostfixExpression : nonBlockPrimary postfixSuffix*
            //                            | expressionWithBlock dotSuffix postfixSuffix*
            auto postfix = is_stmt_unary->statementPostfixExpression();
            if(postfix->nonBlockPrimary() != nullptr){
                this->expr = BuildPostfix(BuildPrimary(postfix->nonBlockPrimary()),postfix->postfixSuffix());
            }
            else{
                ASTNode* base = new ExprStmtNode(ExprStmt,postfix->expressionWithBlock());
                base = BuildDotSuffix(base,postfix->dotSuffix());
                this->expr = BuildPostfix(base,postfix->postfixSuffix());
            }
        }
    }
    if(is_cb_unary != nullptr){
        if(is_cb_unary->unaryOperator() != nullptr){
            this->op = is_cb_unary->unaryOperator()->getText();
            this->expr = new UnaryExprNode(UnaryExpr,is_cb_unary->conditionUnaryExpression());
        }
        else{
            // conditionBreakPostfixExpression : conditionPrimaryWithoutBareBlock postfixSuffix*
            auto postfix = is_cb_unary->conditionBreakPostfixExpression();
            this->expr = BuildPostfix(BuildPrimary(postfix->conditionPrimaryWithoutBareBlock()),postfix->postfixSuffix());
        }
    }
}
static ASTNode* BuildClosedCastType(rx::Parser::ClosedCastTypeContext* ctx){
    if(ctx->LPAREN()){
        if(ctx->typeRef()){
            auto node = ASTNode::CheckType(ctx->typeRef());
            return node;
        }
        else return new UnitTypeNode(UnitType);
    }
    else if(ctx->arrayType()){
        return new ArrayTypeNode(ArrayType,ctx->arrayType());
    }
    else if(ctx->pathIdentSegment()){
        auto node = new PathTypeNode(PathType);
        for(auto seg : ctx->typePathSegment()){
            node->segments.push_back(seg->pathIdentSegment()->getText());
        }
        node->segments.push_back(ctx->pathIdentSegment()->getText());
        return node;
    }
    else{
        auto node = new RefTypeNode(RefType);
        if(ctx->ANDAND() != nullptr){
            // ANDAND 是两重引用，MUT 属于内层
            auto inner = new RefTypeNode(RefType);
            inner->mut = (ctx->MUT() != nullptr);
            inner->type = BuildClosedCastType(ctx->closedCastType());
            node->mut = false;
            node->type = inner;
        }
        else{
            node->mut = (ctx->MUT() != nullptr);
            node->type = BuildClosedCastType(ctx->closedCastType());
        }
        return node;
    }
}
CastExprNode::CastExprNode(const ASTNodeType kind_,antlr4::ParserRuleContext* ctx) : ASTNode(kind_) {
    auto is_cast = dynamic_cast<rx::Parser::CastExpressionContext*>(ctx);
    auto is_closed_cast = dynamic_cast<rx::Parser::ClosedCastExpressionContext*>(ctx);
    auto is_cond_cast = dynamic_cast<rx::Parser::ConditionCastExpressionContext*>(ctx);
    auto is_cond_closed_cast = dynamic_cast<rx::Parser::ConditionClosedCastExpressionContext*>(ctx);
    auto is_stmt_cast = dynamic_cast<rx::Parser::StatementCastExpressionContext*>(ctx);
    auto is_stmt_closed_cast = dynamic_cast<rx::Parser::StatementClosedCastExpressionContext*>(ctx);
    auto is_cb_cast = dynamic_cast<rx::Parser::ConditionBreakCastExpressionContext*>(ctx);
    auto is_cb_closed_cast = dynamic_cast<rx::Parser::ConditionBreakClosedCastExpressionContext*>(ctx);
    if(is_cast != nullptr){
        this->expr = new UnaryExprNode(UnaryExpr,is_cast->unaryExpression());
        std::vector<rx::Parser::TypeRefContext*> types = is_cast->typeRef();
        for(auto type : types){
            this->types.push_back(CheckType(type));
        }
    }
    if(is_closed_cast != nullptr){
        if(is_closed_cast->unaryExpression() != nullptr){
            this->expr = new UnaryExprNode(UnaryExpr,is_closed_cast->unaryExpression());
        }
        else{
            this->expr = new CastExprNode(CastExpr,is_closed_cast->castExpression());
            auto type_ptr = is_closed_cast->closedCastType();
            // CloseCastType
            this->types.push_back(BuildClosedCastType(type_ptr));
        }
    }
    if(is_cond_cast != nullptr){
        this->expr = new UnaryExprNode(UnaryExpr,is_cond_cast->conditionUnaryExpression());
        std::vector<rx::Parser::TypeRefContext*> types = is_cond_cast->typeRef();
        for(auto type : types){
            this->types.push_back(CheckType(type));
        }
    }
    if(is_cond_closed_cast != nullptr){
        if(is_cond_closed_cast->conditionUnaryExpression() != nullptr){
            this->expr = new UnaryExprNode(UnaryExpr,is_cond_closed_cast->conditionUnaryExpression());
        }
        else{
            this->expr = new CastExprNode(CastExpr,is_cond_closed_cast->conditionCastExpression());
            auto type_ptr = is_cond_closed_cast->closedCastType();
            this->types.push_back(BuildClosedCastType(type_ptr));
        }
    }
    if(is_stmt_cast != nullptr){
        this->expr = new UnaryExprNode(UnaryExpr,is_stmt_cast->statementUnaryExpression());
        std::vector<rx::Parser::TypeRefContext*> types = is_stmt_cast->typeRef();
        for(auto type : types){
            this->types.push_back(CheckType(type));
        }
    }
    if(is_stmt_closed_cast != nullptr){
        if(is_stmt_closed_cast->statementUnaryExpression() != nullptr){
            this->expr = new UnaryExprNode(UnaryExpr,is_stmt_closed_cast->statementUnaryExpression());
        }
        else{
            this->expr = new CastExprNode(CastExpr,is_stmt_closed_cast->statementCastExpression());
            auto type_ptr = is_stmt_closed_cast->closedCastType();
            this->types.push_back(BuildClosedCastType(type_ptr));
        }
    }
    if(is_cb_cast != nullptr){
        this->expr = new UnaryExprNode(UnaryExpr,is_cb_cast->conditionBreakUnaryExpression());
        std::vector<rx::Parser::TypeRefContext*> types = is_cb_cast->typeRef();
        for(auto type : types){
            this->types.push_back(CheckType(type));
        }
    }
    if(is_cb_closed_cast != nullptr){
        if(is_cb_closed_cast->conditionBreakUnaryExpression() != nullptr){
            this->expr = new UnaryExprNode(UnaryExpr,is_cb_closed_cast->conditionBreakUnaryExpression());
        }
        else{
            this->expr = new CastExprNode(CastExpr,is_cb_closed_cast->conditionBreakCastExpression());
            auto type_ptr = is_cb_closed_cast->closedCastType();
            this->types.push_back(BuildClosedCastType(type_ptr));
        }
    }
}
// types
RefTypeNode::RefTypeNode(const ASTNodeType kind_) : ASTNode(kind_) {}
RefTypeNode::RefTypeNode(const ASTNodeType kind_,rx::Parser::ReferenceTypeContext* ctx) : ASTNode(kind_) {
    if(ctx->ANDAND() != nullptr){
        // ANDAND 是两重引用，MUT 属于内层
        auto inner = new RefTypeNode(RefType);
        inner->mut = (ctx->MUT() != nullptr);
        inner->type = CheckType(ctx->typeRef());
        this->mut = false;
        this->type = inner;
    }
    else{
        this->type = CheckType(ctx->typeRef());
        this->mut = (ctx->MUT() != nullptr);
    }
}
ArrayTypeNode::ArrayTypeNode(const ASTNodeType kind_,rx::Parser::ArrayTypeContext* ctx) : ASTNode(kind_) {
    this->type = CheckType(ctx->typeRef());
    this->length = CheckConstValue(ctx->constValue());
}
PathTypeNode::PathTypeNode(const ASTNodeType kind_) : ASTNode(kind_) {}
PathTypeNode::PathTypeNode(const ASTNodeType kind_,rx::Parser::TypePathContext* ctx) : ASTNode(kind_) {
    auto segments = ctx->typePathSegment();
    for(auto seg : segments){
        this->segments.push_back(seg->pathIdentSegment()->getText());
    }
}
UnitTypeNode::UnitTypeNode(const ASTNodeType kind_) : ASTNode(kind_) {}

// others
FnSelfParamNode::FnSelfParamNode(const ASTNodeType kind_,rx::Parser::SelfParamContext* ctx) : ASTNode(kind_) {
    if(ctx->MUT() != nullptr){
        this->mut = true;
    }
    else{
        this->mut = false;
    }
    if(ctx->AMP() != nullptr){
        this->amp = true;
    }
    else{
        this->amp = false;
    }
}
FnParamNode::FnParamNode(const ASTNodeType kind_,rx::Parser::FunctionParamContext* ctx) : ASTNode(kind_) {
    this->name = ctx->identifierBinding()->identifier()->getText();
    if(ctx->identifierBinding()->MUT() != nullptr){
        this->mut = true;
    }
    else{
        this->mut = false;
    }
    this->type = CheckType(ctx->typeRef());
}
StructFieldNode::StructFieldNode(const ASTNodeType kind_,rx::Parser::StructFieldContext* ctx) : ASTNode(kind_) {
    this->name = ctx->identifier()->getText();
    this->type = CheckType(ctx->typeRef());
}