#include "Semantic.h"
#include "AST.h"
bool SemanticCheck::hasSemanticError(CrateNode* node){
    // 1. 扫描所有items构建symbol table 检查同类重名
    for(auto item : node->items){
        if(item->kind == FnItem){
            FnItemNode* child_node = static_cast<FnItemNode*>(item);
            FunctionInfo* func = new FunctionInfo;
            for(auto param : child_node->parameters){
                if(param->kind == FnParam){
                    auto fn_param_node = static_cast<FnParamNode*>(param);
                    if(IsBuiltInValues(fn_param_node->name)) return true; // value关键字
                    for(auto p : func->params){
                        if(p.first == fn_param_node->name) return true; // 重复变量名
                    }
                    Symbol* param_symbol = new Symbol;
                    param_symbol->type = GetTypeInfo(fn_param_node->type);
                    if(param_symbol->type->kind == TypeInfo::Unknown){
                        return true; // 无法解析
                    }
                    if(fn_param_node->mut){
                        param_symbol->mut = true;
                    }
                    else param_symbol->mut = false;
                    func->params.push_back(std::pair(fn_param_node->name,param_symbol));
                }
                else if(param->kind == FnSelfParam){
                    return true; // 全局函数不可以用self作为参数
                }
            }
            if(child_node->returnType != nullptr){
                func->return_type = GetTypeInfo(child_node->returnType);
                if(func->return_type->kind == TypeInfo::Unknown) return true; // 未知类型
            }
            else{
                func->return_type = new TypeInfo;
                func->return_type->kind = TypeInfo::Unit;
                // 没有返回值时统一成Unit
            }
            if(functions_table.find(child_node->name) != functions_table.end()){
                return true; // 重复函数名
            }
            else if(IsBuiltInValues(child_node->name)){
                return true; // value关键字
            }
            else{
                functions_table[child_node->name] = func;
            }
        }
        else if(item->kind == StructItem){
            StructItemNode* child_node = static_cast<StructItemNode*>(item);
            StructInfo* struc = new StructInfo;
            for(auto derive : child_node->derives){
                Derived trait = StringToDerived(derive);
                if(trait == Other){
                    return true; // 引入了其它trait
                }
                else if(struc->derived.find(trait) != struc->derived.end()){
                    return true; // 重复导入相同的trait
                }
                else{
                    struc->derived.insert(trait);
                }
            }
            // 检查：有Copy必须有Clone，有Eq必须有PartialEq
            if(struc->derived.find(Copy) != struc->derived.end() && struc->derived.find(Clone) == struc->derived.end()){
                return true; // 有Copy没有Clone
            }
            if(struc->derived.find(Eq) != struc->derived.end() && struc->derived.find(PartialEq) == struc->derived.end()){
                return true; // 有Eq没有PartialEq
            }
            auto fields = child_node->structField;
            for(auto field : fields){
                std::pair<std::string,TypeInfo*> field_;
                field_.first = static_cast<StructFieldNode*>(field)->name;
                field_.second = GetTypeInfo(static_cast<StructFieldNode*>(field)->type);
                if(field_.second->kind == TypeInfo::Unknown) return true; // 未知类型
                if(struc->fields.find(field_.first) != struc->fields.end()){
                    return true; // struct里有重复field名
                }
                else if(IsBuiltInValues(field_.first)){
                    return true; // field变量使用保留value关键字做名字
                }
                else{
                    struc->fields[field_.first] = field_.second;
                }
            }
            if(structs_table.find(child_node->name) != structs_table.end()){
                return true; // 重复结构体名
            }
            else if(IsBuiltInTypes(child_node->name)){
                return true; // 保留关键字
            }
            else{
                structs_table[child_node->name] = struc;
            }
        }
        else if(item->kind == ConstItem){
            auto child_node = static_cast<ConstItemNode*>(item);
            ConstantInfo* const_info = new ConstantInfo;
            const_info->type = GetTypeInfo(child_node->type);
            if(const_info->type->kind == TypeInfo::Unknown) return true; // 未知类型
            if(child_node->value->kind == IntLit){
                if(const_info->type->kind != TypeInfo::I32 && const_info->type->kind != TypeInfo::U32
                && const_info->type->kind != TypeInfo::Isize && const_info->type->kind != TypeInfo::Usize){
                    return true; // 类型不匹配
                }
                const_info->int_value = static_cast<IntLitNode*>(child_node->value)->value;
                if(const_info->int_value < 0){
                    if(const_info->type->kind == TypeInfo::U32 || const_info->type->kind == TypeInfo::Usize){
                        return true; // 常量类型和值不匹配
                    }
                }
            }
            else if(child_node->value->kind == BoolLit){
                if(const_info->type->kind != TypeInfo::Bool) return true; // 类型不匹配
                const_info->bool_value = static_cast<BoolLitNode*>(child_node->value)->value;
            }

            if(constants_table.find(child_node->name) != constants_table.end()){
                return true; // 重复常量名
            }
            else if(IsBuiltInValues(child_node->name)){
                return true; // 保留关键字
            }
            else{
                constants_table[child_node->name] = const_info;
            }
        }
        else if(item->kind == ImplItem){
            auto child_node = static_cast<ImplItemNode*>(item);
            TypeInfo* target_type = GetTypeInfo(child_node->type);
            if(target_type->kind == TypeInfo::Unknown) return true; // 未知类型
            std::string target_type_name = target_type->name;
            if(structs_table.find(target_type_name) == structs_table.end()){
                return true; // 没有在前面定义这个struct
            }
            for(auto associated : child_node->associatedItems){
                StructInfo* struct_info = structs_table[target_type_name];
                if(associated->kind == FnItem){
                    auto func_ptr = static_cast<FnItemNode*>(associated);
                    if(struct_info->methods.find(func_ptr->name) != struct_info->methods.end()){
                        return true; // 结构体中impl函数重名
                    }
                    else if(struct_info->consts.find(func_ptr->name) != struct_info->consts.end()){
                        return true; // 函数和常量重名
                    }
                    else if(IsBuiltInValues(func_ptr->name)){
                        return true; // 保留关键字
                    }
                    else{
                        // 加入methods中
                        FunctionInfo* func_in_struct = new FunctionInfo;
                        for(auto param : func_ptr->parameters){
                            if(param->kind == FnParam){
                                auto fn_param_node = static_cast<FnParamNode*>(param);
                                if(IsBuiltInValues(fn_param_node->name)){
                                    return true; // 关键字
                                }
                                for(auto p : func_in_struct->params){
                                    if(p.first == fn_param_node->name) return true; // 重复参数名
                                }
                                Symbol* param_symbol = new Symbol;
                                param_symbol->type = GetTypeInfo(fn_param_node->type);
                                if(fn_param_node->mut){
                                    param_symbol->mut = true;
                                }
                                else param_symbol->mut = false;
                                func_in_struct->params.push_back(std::pair(fn_param_node->name,param_symbol));
                            }
                            else if(param->kind == FnSelfParam){
                                if(param != func_ptr->parameters[0]) return true; // self不在第一个
                                auto fn_self_param_node = static_cast<FnSelfParamNode*>(param);
                                Symbol* param_symbol = new Symbol;
                                param_symbol->type = GetSelfTypeInfo(fn_self_param_node,target_type_name);
                                if(fn_self_param_node->mut && !fn_self_param_node->amp){
                                    param_symbol->mut = true;
                                }
                                else{
                                    param_symbol->mut = false;
                                }
                                func_in_struct->params.push_back(std::pair("self",param_symbol)); // self没有参数名，先填一个"self"
                            }
                        }
                        if(func_ptr->returnType != nullptr){
                            func_in_struct->return_type = GetTypeInfo(func_ptr->returnType);
                        }
                        else{
                            func_in_struct->return_type = new TypeInfo;
                            func_in_struct->return_type->kind = TypeInfo::Unit; // 没有返回值统一为Unit
                        }
                        struct_info->methods[func_ptr->name] = func_in_struct;
                        structs_table[target_type_name] = struct_info; // 更新
                    }
                }
                else if(associated->kind == ConstItem){
                    auto const_ptr = static_cast<ConstItemNode*>(associated);
                    if(struct_info->consts.find(const_ptr->name) != struct_info->consts.end()){
                        return true; // 一个struct中impl同名常量
                    }
                    else if(struct_info->methods.find(const_ptr->name) != struct_info->methods.end()){
                        return true; // 常量和函数重名
                    }
                    else if(IsBuiltInValues(const_ptr->name)){
                        return true; // 关键字
                    }
                    else{
                        // 加入consts中
                        ConstantInfo* const_in_struct = new ConstantInfo;
                        const_in_struct->type = GetTypeInfo(const_ptr->type);
                        if(const_ptr->value->kind == IntLit){
                            if(const_in_struct->type->kind != TypeInfo::I32 && const_in_struct->type->kind != TypeInfo::U32
                            && const_in_struct->type->kind != TypeInfo::Isize && const_in_struct->type->kind != TypeInfo::Usize){
                                return true; // 类型不匹配
                            }
                            const_in_struct->int_value = static_cast<IntLitNode*>(const_ptr->value)->value;
                            if(const_in_struct->int_value < 0){
                                if(const_in_struct->type->kind == TypeInfo::U32 || const_in_struct->type->kind == TypeInfo::Usize){
                                    return true; // 类型不匹配
                                }
                            }
                        }
                        else if(const_ptr->value->kind == BoolLit){
                            const_in_struct->bool_value = static_cast<BoolLitNode*>(const_ptr->value)->value;
                        }
                        struct_info->consts[const_ptr->name] = const_in_struct;
                        structs_table[target_type_name] = struct_info; // 更新
                    }
                }
            }
        }
    }
    // 2. 检查跨类型的重名
    bool has_main = false;
    for(auto it = functions_table.begin(); it != functions_table.end(); it++){
        if(it->first == "main"){
            has_main = true;
            // 检查main的合法性
            if(it->second->params.size() > 0){
                return true; // main函数有参数
            }
            if(it->second->return_type != nullptr && it->second->return_type->kind != TypeInfo::Unit){
                return true; // main函数返回值不是nullptr或者Unit
            }
        }
        if(constants_table.find(it->first) != constants_table.end()){
            return true; // 函数和常量重名
        }
        // 检查函数里每个Type是否存在
        if(it->second->return_type != nullptr){
            if(it->second->return_type->kind == TypeInfo::Struct){
                if(structs_table.find(it->second->return_type->name) == structs_table.end()){
                    return true; // 未定义Type
                }
            }
        }
        for(auto it2 = it->second->params.begin(); it2 != it->second->params.end(); it2++){
            if(it2->second->type->kind == TypeInfo::Struct){
                if(structs_table.find(it2->second->type->name) == structs_table.end()){
                    return true; // 未定义Type
                }
            }
        }
    }
    for(auto it = constants_table.begin(); it != constants_table.end(); it++){
        if(it->second->type->kind == TypeInfo::Struct){
            if(structs_table.find(it->second->type->name) == structs_table.end()){
                return true; // 未定义Type
            }
        }
    }
    if(!has_main) return true; // 不存在main函数
    // 3.二次扫描所有函数体
    VisitCrate(node);
    if(error) return true;
    // 全部检查完没有问题
    return false;
}
// dispatch 用Visit统一分发给不同节点类型
void SemanticCheck::Visit(ASTNode* node){
    switch(node->kind){
        case Crate: VisitCrate(static_cast<CrateNode*>(node));return;
        // items
        case FnItem: VisitFnItem(static_cast<FnItemNode*>(node));return;
        case StructItem: VisitStructItem(static_cast<StructItemNode*>(node));return;            
        case ConstItem: VisitConstItem(static_cast<ConstItemNode*>(node));return;
        case ImplItem: VisitImplItem(static_cast<ImplItemNode*>(node));return;
        // statements
        case LetStmt: VisitLetStmt(static_cast<LetStmtNode*>(node));return;            
        case ExprStmt: VisitExprStmt(static_cast<ExprStmtNode*>(node));return;
        default: return;
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitAndGetType(ASTNode* node){
    switch(node->kind){
        // expression
        case IntLit: return VisitIntLit(static_cast<IntLitNode*>(node));
        case BoolLit: return VisitBoolLit(static_cast<BoolLitNode*>(node));
        case BinaryExpr: return VisitBinaryExpr(static_cast<BinaryExprNode*>(node));
        case AssignExpr: return VisitAssignExpr(static_cast<AssignExprNode*>(node));
        case BlockExpr: return VisitBlockExpr(static_cast<BlockExprNode*>(node));
        case IfExpr: return VisitIfExpr(static_cast<IfExprNode*>(node));
        case LoopExpr: return VisitLoopExpr(static_cast<LoopExprNode*>(node));
        case WhileExpr: return VisitWhileExpr(static_cast<WhileExprNode*>(node));
        case BreakExpr: return VisitBreakExpr(static_cast<BreakExprNode*>(node));
        case ContinueExpr: return VisitContinueExpr(static_cast<ContinueExprNode*>(node));
        // // others
        // case FnSelfParam:
        // case FnParam:
        // case StructField:
        default:
            return TypeInfo(); // 默认Unknown
    }   
}
void SemanticCheck::VisitCrate(CrateNode* node){
    for(auto item : node->items){
        if(item->kind == FnItem){
            // 检查每个函数体
            scopes.clear();
            top_params.clear();
            layer = -1;
            Visit(item);
        }
        if(item->kind == ImplItem){
            auto associated = static_cast<ImplItemNode*>(item);
            for(auto associated_item : associated->associatedItems){
                if(associated_item->kind == FnItem){
                    scopes.clear();
                    top_params.clear();
                    layer = -1;
                    Visit(associated_item);
                }
            }
        }
    }
}
void SemanticCheck::VisitFnItem(FnItemNode* node){
    FunctionInfo* func_info = functions_table[node->name];
    // 把参数放进作用域
    for(auto p : func_info->params){
        top_params[p.first] = p.second;
    }
    TypeInfo return_ = VisitAndGetType(node->blockExpr);
    if(return_.kind == TypeInfo::Unknown) error = true;
    if(!IsTypeEqual(return_,*func_info->return_type)) error = true; // 返回类型不匹配
}
void SemanticCheck::VisitStructItem(StructItemNode* node){}
void SemanticCheck::VisitConstItem(ConstItemNode* node){

}
void SemanticCheck::VisitImplItem(ImplItemNode* node){}
void SemanticCheck::VisitLetStmt(LetStmtNode* node){
    // 允许name shadowing
    Symbol* symbol = new Symbol;
    if(node->mut) symbol->mut = true;
    if(node->type != nullptr){
        TypeInfo defined_type = VisitAndGetType(node->type);
        if(defined_type.kind == TypeInfo::Unknown) error = true; // 不存在的type
        TypeInfo expr_type = VisitAndGetType(node->expr);
        if(expr_type.kind == TypeInfo::Unknown) error = true; // 不存在的type
        if(!IsTypeEqual(defined_type,expr_type)) error = true;
        else{
            TypeInfo* type = new TypeInfo;
            *type = expr_type;
            symbol->type = type;
        }
    }
    else{
        TypeInfo expr_type = VisitAndGetType(node->expr);
        if(expr_type.kind == TypeInfo::Unknown) error = true;
        else{
            TypeInfo* type = new TypeInfo;
            *type = expr_type;
            symbol->type = type;
        }
    }
    scopes[layer][node->name] = symbol; // 加入作用域  
}
void SemanticCheck::VisitExprStmt(ExprStmtNode* node){
    if(node->expr != nullptr){
        TypeInfo type = VisitAndGetType(node->expr);
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitBlockExpr(BlockExprNode* node){
    scopes.emplace_back();
    layer++;
    for(auto stmt : node->statements){
        Visit(stmt);
    }
    TypeInfo return_type;
    if(node->return_expression == nullptr) return_type.kind = TypeInfo::Unit;
    else return_type = VisitAndGetType(node->return_expression);
    scopes.pop_back();
    layer--;
    return return_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitIntLit(IntLitNode* node){
    TypeInfo type;
    if(node->suffix == "i32" || node->suffix.size() == 0) type.kind = TypeInfo::I32;
    else if(node->suffix == "u32") type.kind = TypeInfo::U32;
    else if(node->suffix == "isize") type.kind = TypeInfo::Isize;
    else if(node->suffix == "usize") type.kind = TypeInfo::Usize;
    else error = true; // 不存在的整数类型
    return type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitBoolLit(BoolLitNode* node){
    TypeInfo type;
    type.kind = TypeInfo::Bool;
    return type;
}

SemanticCheck::TypeInfo SemanticCheck::VisitAssignExpr(AssignExprNode* node){
    if(node->right == nullptr){
        // 没有赋值
        TypeInfo type = VisitAndGetType(node->left);
        if(type.kind == TypeInfo::Unknown) error = true;
        return type;
    }
    else{
        TypeInfo left_type = VisitAndGetType(node->left);
        TypeInfo right_type = VisitAndGetType(node->right);
        if(!CanWrite(node->left)){
            error = true; // 等号左边不是合法的左值
        }
        if(!IsTypeEqual(left_type,right_type)){
            error = true; // 左右type不一致
        }
        return left_type;
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitBinaryExpr(BinaryExprNode* node){
    if(node->op.size() == 0){
        return VisitAndGetType(node->operands[0]);
    }
    else{
        TypeInfo type;
        switch(node->level){
            case 0:case 1:{
                for(auto op : node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind != TypeInfo::Bool) error = true;
                }
                type.kind = TypeInfo::Bool;
                break;
            }
            case 2:{
                TypeInfo prev_type = VisitAndGetType(node->operands[0]);
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind == TypeInfo::Unknown){
                        error = true;
                        break;
                    }
                    if(!IsTypeEqual(prev_type,op_type)){
                        error = true;
                        break;
                    }
                    if(op_type.kind == TypeInfo::Struct){
                        if(structs_table[op_type.name]->derived.find(Derived::PartialEq) == structs_table[op_type.name]->derived.end()){
                            error = true; // 没有PartialEq trait
                            break;
                        }
                    }
                    prev_type = op_type;
                }
                type.kind = TypeInfo::Bool;
                break;
            }
            case 3: case 4: case 5:{
                TypeInfo prev_type = VisitAndGetType(node->operands[0]);
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind != TypeInfo::I32 && op_type.kind != TypeInfo::U32
                    && op_type.kind != TypeInfo::Isize && op_type.kind != TypeInfo::Usize && op_type.kind != TypeInfo::Bool){
                        error = true; // 类型不匹配
                        break;
                    }
                    if(!IsTypeEqual(prev_type,op_type)){
                        error = true;
                        break;
                    }
                }
                type = prev_type;
                break;
            }
            case 6:{
                TypeInfo first_type =  VisitAndGetType(node->operands[0]);
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind != TypeInfo::I32 && op_type.kind != TypeInfo::U32
                    && op_type.kind != TypeInfo::Isize && op_type.kind != TypeInfo::Usize){
                        error = true;
                        break;
                    }
                }
                type = first_type;
                break;
            }
            case 7: case 8:{
                TypeInfo prev_type = VisitAndGetType(node->operands[0]);
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind != TypeInfo::I32 && op_type.kind != TypeInfo::U32
                    && op_type.kind != TypeInfo::Isize && op_type.kind != TypeInfo::Usize){
                        error = true;
                        break;
                    }
                    if(!IsTypeEqual(prev_type,op_type)){
                        error = true;
                        break;
                    }
                    prev_type = op_type;
                }
                type = prev_type;
                break;
            }
        }
        return type;
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitIfExpr(IfExprNode* node){
    TypeInfo condition = VisitAndGetType(node->condition);
    if(condition.kind != TypeInfo::Bool) error = true;
    TypeInfo if_type = VisitAndGetType(node->if_block);
    if(if_type.kind == TypeInfo::Unknown) error = true;
    if(node->else_block != nullptr){
        TypeInfo else_type = VisitAndGetType(node->else_block);
        if(else_type.kind == TypeInfo::Unknown) error = true;
        if(!IsTypeEqual(if_type,else_type)){
            error = true;
        }
    }
    return if_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitLoopExpr(LoopExprNode* node){
    if(node->content != nullptr){
        TypeInfo loop_type = VisitAndGetType(node->content);
        if(loop_type.kind == TypeInfo::Unknown) error = true;
        return loop_type;
    }
    TypeInfo type;
    type.kind = TypeInfo::Unit;
    return type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitWhileExpr(WhileExprNode* node){
    TypeInfo condition = VisitAndGetType(node->condition);
    if(condition.kind != TypeInfo::Bool){
        error = true;
    }
    TypeInfo while_type = VisitAndGetType(node->content);
    if(while_type.kind == TypeInfo::Unknown) error = true;
    return while_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitBreakExpr(BreakExprNode* node){
    if(node->expr != nullptr){
        TypeInfo break_type = VisitAndGetType(node->expr);
        if(break_type.kind == TypeInfo::Unknown) error = true;
        return break_type;
    }
    TypeInfo type;
    type.kind = TypeInfo::Unit;
    return type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitContinueExpr(ContinueExprNode* node){
    TypeInfo type;
    type.kind = TypeInfo::Unit;
    return type;
}
// Tools
bool SemanticCheck::IsBuiltInTypes(std::string name_){
    for(auto name : builtin_types){
        if(name_ == name) return true;
    }
    return false;
}
bool SemanticCheck::IsBuiltInValues(std::string name_){
    for(auto name : builtin_values){
        if(name_ == name) return true;
    }
    return false;
}
SemanticCheck::Derived SemanticCheck::StringToDerived(std::string trait){
    if(trait == "Copy") return Copy;
    else if(trait == "Clone") return Clone;
    else if(trait == "PartialEq") return PartialEq;
    else if(trait == "Eq") return Eq;
    else return Other;
}
SemanticCheck::TypeInfo* SemanticCheck::GetTypeInfo(ASTNode* node){
    assert(node != nullptr); // 不允许传入空指针
    TypeInfo* type_info = new TypeInfo;
    if(node->kind == UnitType){
        type_info->kind = TypeInfo::Kind::Unit;
    }
    else if(node->kind == RefType){
        RefTypeNode* ref_ptr = static_cast<RefTypeNode*>(node);
        type_info->kind = TypeInfo::Kind::Ref;
        if(ref_ptr->mut){
            type_info->is_mut = true;
        }
        type_info->element = GetTypeInfo(ref_ptr->type);
    }
    else if(node->kind == ArrayType){
        type_info->kind = TypeInfo::Kind::Array;
        ArrayTypeNode* array_ptr = static_cast<ArrayTypeNode*>(node);
        type_info->element = GetTypeInfo(array_ptr->type);
        if(array_ptr->length->kind != IntLit){
            error = true; // 不是int类型
        }
        else{
            auto int_ptr = static_cast<IntLitNode*>(array_ptr->length);
            type_info->length = int_ptr->value;
            if(type_info->length <= 0) error = true; // 数组长度为负数
        }
    }
    else if(node->kind == PathType){
        PathTypeNode* path_ptr = static_cast<PathTypeNode*>(node);
        std::string seg_type = path_ptr->segments[0];
        if(path_ptr->segments.size() == 1){
            if(seg_type == "i32"){
                type_info->kind = TypeInfo::I32;
            }
            else if(seg_type == "u32"){
                type_info->kind = TypeInfo::U32;
            }
            else if(seg_type == "isize"){
                type_info->kind = TypeInfo::Isize;
            }
            else if(seg_type == "usize"){
                type_info->kind = TypeInfo::Usize;
            }
            else if(seg_type == "bool"){
                type_info->kind = TypeInfo::Bool;
            }
            else{
                // 允许前向引用，先默认存在这个Struct
                type_info->kind = TypeInfo::Struct;
                type_info->name = seg_type;
            }
        }
        else{
            // Vec and Box TODO
            if(seg_type == "Vec"){
                // PathTypeNode* path_ptr = static_cast<PathTypeNode*>(node);
                type_info->kind = TypeInfo::Vec;
            }
            else if(seg_type == "Box"){
                // PathTypeNode* path_ptr = static_cast<PathTypeNode*>(node);
                type_info->kind = TypeInfo::Box;
            }
        }
    }
    return type_info;
}
SemanticCheck::TypeInfo* SemanticCheck::GetSelfTypeInfo(ASTNode* node,std::string struct_name){
    assert(node != nullptr);
    TypeInfo* type_info = new TypeInfo;
    auto self_param_node = static_cast<FnSelfParamNode*>(node);
    if(!self_param_node->amp){
        // self, mut self
        type_info->kind = TypeInfo::Struct;
        type_info->name = struct_name;
    } 
    else{
        type_info->kind = TypeInfo::Ref;
        type_info->element = new TypeInfo;
        type_info->element->kind = TypeInfo::Struct;
        type_info->element->name = struct_name;
        if(self_param_node->mut){
            type_info->is_mut = true;
        }
        else{
            type_info->is_mut = false;
        }
    }
    return type_info;
    // self：By-value receiver
    // mut self：Mutable by-value receiver
    // &self or &'a self：Shared reference
    // &mut self or &'a mut self：Mutable reference
}
bool SemanticCheck::IsTypeEqual(const TypeInfo& a, const TypeInfo& b){
    if(a.kind != b.kind) return false;
    if(a.kind == TypeInfo::Struct){
        if(a.name != b.name) return false;
    }
    if(a.kind == TypeInfo::Ref){
        if(a.is_mut != b.is_mut) return false;
        return IsTypeEqual(*a.element,*b.element);
    }
    if(a.kind == TypeInfo::Array){
        if(a.length != b.length) return false;
        return IsTypeEqual(*a.element,*b.element);
    }
    return true;
}
bool SemanticCheck::CanWrite(ASTNode* node){
    // 用于判断合法Assign Destination
    Symbol symbol;
    while(node->kind == BinaryExpr){
        auto binary_ptr = static_cast<BinaryExprNode*>(node);
        if(binary_ptr->operands.size() > 1){
            error = true; // 左值是表达式 不合法
        }
        node = binary_ptr->operands[0];
    }
    if(node->kind == CastExpr){
        auto cast_ptr = static_cast<CastExprNode*>(node);
        if(cast_ptr->types.size() > 0){
            error = true; // 左值cast
        }
        node = cast_ptr->expr;
    }
    else if(node->kind == UnaryExpr){
        auto unary_ptr = static_cast<UnaryExprNode*>(node);
        if(unary_ptr->op.size() > 0){
            error = true; // 左值带符号
        }
        node = unary_ptr->expr;
    }
    else if(node->kind == CallExpr){
        auto call_ptr = static_cast<CallExprNode*>(node);
    }
    else if(node->kind == IndexExpr){

    }
    else if(node->kind == FieldExpr){

    }
    else if(node->kind == MethodCallExpr){
        auto method_call_ptr = static_cast<MethodCallExprNode*>(node);
        TypeInfo receiver = VisitAndGetType(method_call_ptr->receiver);
        if(receiver.kind != TypeInfo::Struct){
            error = true;
        }
        StructInfo* struct_info = structs_table[receiver.name];
        if(struct_info->methods.find(method_call_ptr->name) == struct_info->methods.end()){
            error = true; // 不存在这个method
        }
        else{
            auto params = struct_info->methods[method_call_ptr->name]->params;
            if(params.size() != method_call_ptr->args.size()){
                error = true; // 参数不匹配
            }
            else{
                int cnt = 0;
                for(auto param : params){
                    if(!IsTypeEqual(*param.second->type,*GetTypeInfo(method_call_ptr->args[cnt]))){
                        error = true;
                        break;
                    }
                }
            }
        }
    }
    else{
        if(node->kind == PathExpr){

        }
        else{
            // 其它类型都不能做左值
            error = true;
        }
    }
    return false;
}
