#include "IR.h"
#include "IRType.h"
#include <memory>
void IRBuilder::BuildIR(CrateNode* node,SemanticResult& result){
    // 构建所有函数块
    for(auto func : result.functions_table){
        auto ir_func = std::make_shared<IRFunction>();
        ir_func->name = func.first;
        ir_func->return_type = GetIRType(*func.second.return_type,result);
        functions[func.first] = ir_func; // 转移所有权
    }
    // 进入每个函数构建基本块
    for(auto item : node->items){
        if(item->kind == FnItem){
            auto func_node = static_cast<FnItemNode*>(item);
            scopes.clear();
            layer = 0;
            symbol_id_counter = 0;
            cur_function = functions[func_node->name]; // 全局函数名
            for(auto param : result.functions_table[func_node->name].params){
                cur_function->params[symbol_id_counter] = GetIRType(*param.second->type,result);
                top_params[param.first] = symbol_id_counter++; // 函数传入参数编号和临时变量同一个系统
            }
            BuildBasicBlocks(func_node,result);
        }
    }
}
std::shared_ptr<IRBaseType> IRBuilder::GetIRType(SemanticCheck::TypeInfo type,SemanticResult& result){
    // 基础的IR类型
    if(type.kind == SemanticCheck::TypeInfo::I32 || type.kind == SemanticCheck::TypeInfo::U32
    || type.kind == SemanticCheck::TypeInfo::Isize || type.kind == SemanticCheck::TypeInfo::Usize){
        return std::make_unique<IRPrimaryType>(IRBaseType::I32);
    }
    if(type.kind == SemanticCheck::TypeInfo::Bool){
        return std::make_unique<IRPrimaryType>(IRBaseType::I1);
    }
    if(type.kind == SemanticCheck::TypeInfo::Ref || type.kind == SemanticCheck::TypeInfo::Box){
        auto ptr = std::make_unique<IRPointerType>(IRBaseType::Ptr);
        ptr->element = GetIRType(*type.element,result);
        return ptr;
    }
    if(type.kind == SemanticCheck::TypeInfo::Struct){
        auto ptr = std::make_unique<IRStructType>(IRBaseType::Struct);
        ptr->name = type.name;
        SemanticCheck::StructInfo struct_info = result.structs_table[type.name];
        for(auto field : struct_info.fields){
            ptr->fields[field.first] = GetIRType(*field.second,result);
        }
        return ptr;
    }
    if(type.kind == SemanticCheck::TypeInfo::Array){
        auto ptr = std::make_unique<IRArrayType>(IRBaseType::Array);
        ptr->length = type.length;
        ptr->element = GetIRType(*type.element,result);
        return ptr;
    }
    return std::make_unique<IRBaseType>(IRBaseType::Void);
    
}
void IRBuilder::BuildBasicBlocks(FnItemNode* node,SemanticResult &result){
    // 默认第一个block是entry
    // 如果没有循环和分支，整个function顺序执行，就只需要1个block
    // 先处理最简单的情况 只有一个block
    auto block = std::make_shared<IRBasicBlock>();
    block->id = symbol_id_counter++;
    cur_block = block;
    auto block_ptr = static_cast<BlockExprNode*>(node->blockExpr);
    for(auto stmt : block_ptr->statements){
        BuildInstructions(stmt,result);
    }
    cur_function->basic_blocks.push_back(cur_block);
}
IRBuilder::IRValue IRBuilder::BuildInstructions(ASTNode* node,SemanticResult &result){
    if(node == nullptr) return IRValue();
    if(node->kind == LetStmt){
        // binding
        auto let_stmt_node = static_cast<LetStmtNode*>(node);
        // example: %p0 = alloca i32
        std::shared_ptr<AllocateInstruction> alloca_inst = std::make_shared<AllocateInstruction>(IRInstruction::Alloca);
        alloca_inst->type = GetIRType(result.bindings_table[let_stmt_node].type,result);
        alloca_inst->id = result.bindings_table[let_stmt_node].ptr_id;
        memory[alloca_inst->id] = alloca_inst->type;
        scopes[layer][let_stmt_node->name] = alloca_inst->id;
        // example: store i32 1, ptr %p0
        std::shared_ptr<StoreInstruction> store_inst = std::make_shared<StoreInstruction>(IRInstruction::Store);
        store_inst->type = alloca_inst->type;
        // store可能是一个%v 也可能是立即数 
        // AST越底层的在lowering时需要被优先调用
        store_inst->value = BuildInstructions(let_stmt_node->expr,result); // 递归调用 
        store_inst->slot_id = alloca_inst->id;
        cur_block->instructions.push_back(alloca_inst);
        cur_block->instructions.push_back(store_inst);
    }
    else if(node->kind == ExprStmt){
        BuildInstructions(static_cast<ExprStmtNode*>(node)->expr,result);
    }
    else if(node->kind == IntLit){
        IRValue value;
        value.type = std::make_shared<IRPrimaryType>(IRBaseType::I32);
        value.is_imm = true;
        value.imm = static_cast<IntLitNode*>(node)->value;
        return value;
    }
    else if(node->kind == BoolLit){
        IRValue value;
        value.type = std::make_shared<IRPrimaryType>(IRBaseType::I1);
        value.is_imm = true;
        value.imm = static_cast<BoolLitNode*>(node)->value;
        return value;
    }
    else if(node->kind == PathExpr){
        auto path_expr_node = static_cast<PathExprNode*>(node);
        if(path_expr_node->segments.size() == 1){
            // 先只考虑单变量情形
            // 是局部变量
            std::string &name = path_expr_node->segments[0].first;
            for(auto it = scopes.rbegin(); it != scopes.rend(); it++){
                // 倒序遍历
                if(it->find(name) != it->end()){
                    IRValue value;
                    value.is_ptr = true;
                    value.slot_id = (*it)[name];
                    value.type = memory[value.slot_id];
                    return value;
                }
            }
            // 是函数参数
            for(auto param : top_params){
                if(name == param.first){
                    IRValue value;
                    value.is_symbol = true;
                    value.symbol_id = param.second;
                    value.type = cur_function->params[value.symbol_id];
                    return value;
                }
            }

        }
        else if(path_expr_node->segments.size() == 2){
            // TODO
        }
    }
    else if(node->kind == BinaryExpr){
        auto binary_expr_node = static_cast<BinaryExprNode*>(node);
        if(binary_expr_node->operands.size() == 1){
            // 直接穿透
            return BuildInstructions(binary_expr_node->operands[0],result);
        }
        switch(binary_expr_node->level){
            case 0: case 1: break; // TODO
            case 2: {
                // compare
                IRValue left = BuildInstructions(binary_expr_node->operands[0],result);
                IRValue right = BuildInstructions(binary_expr_node->operands[1],result);

                if(left.is_ptr){
                    auto load_inst = std::make_shared<LoadInstruction>(IRInstruction::Load);
                    load_inst->value_type = left.type;
                    load_inst->slot_id = left.slot_id;
                    load_inst->symbol_id = symbol_id_counter++;
                    cur_block->instructions.push_back(load_inst);
                    left.is_ptr = false;
                    left.is_symbol = true;
                    left.symbol_id = load_inst->symbol_id;
                }
                if(right.is_ptr){
                    auto load_inst = std::make_shared<LoadInstruction>(IRInstruction::Load);
                    load_inst->value_type = right.type;
                    load_inst->slot_id = right.slot_id;
                    load_inst->symbol_id = symbol_id_counter++;
                    cur_block->instructions.push_back(load_inst);
                    right.is_ptr = false;
                    right.is_symbol = true;
                    right.symbol_id = load_inst->symbol_id;
                }

                auto cmp_inst = std::make_shared<CompareInstruction>(IRInstruction::ICmp);
                cmp_inst->type = left.type;
                cmp_inst->left = left;
                cmp_inst->right = right;
                const auto& op = binary_expr_node->op[0];
                const auto kind = result.expressions_table.at(binary_expr_node->operands[0]).kind;
                const bool is_unsigned = kind == SemanticCheck::TypeInfo::U32 ||
                                         kind == SemanticCheck::TypeInfo::Usize;
                if(op == "==") cmp_inst->cmp_type = CompareInstruction::Eq;
                else if(op == "!=") cmp_inst->cmp_type = CompareInstruction::Neq;
                else if(op == "<") cmp_inst->cmp_type = is_unsigned ? CompareInstruction::Ult : CompareInstruction::Slt;
                else if(op == "<=") cmp_inst->cmp_type = is_unsigned ? CompareInstruction::Ule : CompareInstruction::Sle;
                else if(op == ">") cmp_inst->cmp_type = is_unsigned ? CompareInstruction::Ugt : CompareInstruction::Sgt;
                else cmp_inst->cmp_type = is_unsigned ? CompareInstruction::Uge : CompareInstruction::Sge;
                cmp_inst->id = symbol_id_counter++;
                cur_block->instructions.push_back(cmp_inst);

                IRValue value;
                value.type = std::make_shared<IRPrimaryType>(IRBaseType::I1);
                value.is_symbol = true;
                value.symbol_id = cmp_inst->id;
                return value;
            }
            case 3: case 4: case 5: case 6: case 7: case 8: {
                // 左结合
                IRValue left = BuildInstructions(binary_expr_node->operands[0],result);
                size_t num_of_operand = binary_expr_node->operands.size();
                for(int i = 1; i < num_of_operand; i++){
                    IRValue right = BuildInstructions(binary_expr_node->operands[i],result);
                    if(left.is_ptr){
                        auto load_inst = std::make_shared<LoadInstruction>(IRInstruction::Load);
                        load_inst->value_type = memory[left.slot_id];
                        load_inst->slot_id = left.slot_id;
                        load_inst->symbol_id = symbol_id_counter++;
                        cur_block->instructions.push_back(load_inst);
                        // 
                        left.is_ptr = false;
                        left.is_symbol = true;
                        left.symbol_id = load_inst->symbol_id;
                    }
                    if(right.is_ptr){
                        auto load_inst = std::make_shared<LoadInstruction>(IRInstruction::Load);
                        load_inst->value_type = memory[right.slot_id];
                        load_inst->slot_id = right.slot_id;
                        load_inst->symbol_id = symbol_id_counter++;
                        cur_block->instructions.push_back(load_inst);
                        // 
                        right.is_ptr = false;
                        right.is_symbol = true;
                        right.symbol_id = load_inst->symbol_id;
                    }
                    
                    std::shared_ptr<ArithmeticInstruction> arithm_inst;
                    if(binary_expr_node->op[i - 1] == "+"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Add);
                    }
                    else if(binary_expr_node->op[i - 1] == "-"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Sub);
                    }
                    else if(binary_expr_node->op[i - 1] == "*"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Mul);
                    }
                    else if(binary_expr_node->op[i - 1] == "/"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Sdiv);
                    }
                    else if(binary_expr_node->op[i - 1] == "|"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Or);
                    }
                    else if(binary_expr_node->op[i - 1] == "^"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Xor);
                    }
                    else if(binary_expr_node->op[i - 1] == "&"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::And);
                    }
                    else if(binary_expr_node->op[i - 1] == "<<"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Shl);
                    }
                    else if(binary_expr_node->op[i - 1] == ">>"){
                        arithm_inst = std::make_shared<ArithmeticInstruction>(IRInstruction::Shr);
                    }
                    arithm_inst->type = left.type;
                    arithm_inst->left = left;
                    arithm_inst->right = right;
                    arithm_inst->id = symbol_id_counter++;
                    cur_block->instructions.push_back(arithm_inst);

                    left.is_symbol = true;
                    left.type = arithm_inst->type;
                    left.symbol_id = arithm_inst->id;
                }
                return left;
            }
            default: break;
        }
    }
    else if(node->kind == AssignExpr){
        auto assign_ptr = static_cast<AssignExprNode*>(node);
        if(assign_ptr->right == nullptr){
            return BuildInstructions(assign_ptr->left,result);
        }
        IRValue left = BuildInstructions(assign_ptr->left,result);
        IRValue right = BuildInstructions(assign_ptr->right,result);
        auto store_inst = std::make_shared<StoreInstruction>(IRInstruction::Store);
        if(right.is_ptr){
            // 把内存里的值load出来
            auto load_inst = std::make_shared<LoadInstruction>(IRInstruction::Load);
            load_inst->symbol_id = symbol_id_counter++;
            load_inst->value_type = right.type;
            load_inst->slot_id = right.slot_id;
            cur_block->instructions.push_back(load_inst);
            //
            IRValue value;
            value.is_symbol = true;
            value.type = right.type;
            value.symbol_id = load_inst->symbol_id;
            //
            store_inst->type = load_inst->value_type;
            store_inst->value = value;
            store_inst->slot_id = left.slot_id;
            
        }
        else if(right.is_imm || right.is_symbol){
            store_inst->type = right.type;
            store_inst->value = right;
            store_inst->slot_id = left.slot_id;
        }
        cur_block->instructions.push_back(store_inst);
    }
    else if(node->kind == CallExpr){
        auto call_ptr = static_cast<CallExprNode*>(node);
    }
    return IRValue();
}
