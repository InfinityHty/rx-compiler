#include "Semantic.h"
#include "AST.h"
SemanticCheck::TypeInfo::TypeInfo() = default;
bool SemanticCheck::hasSemanticError(CrateNode* node){
    // 0. 加入built-in I/O functions
    FunctionInfo* get_i32 = new FunctionInfo;
    get_i32->return_type = new TypeInfo(TypeInfo::I32);
    functions_table["get_i32"] = get_i32;

    FunctionInfo* print_i32 = new FunctionInfo;
    print_i32->return_type = new TypeInfo(TypeInfo::Unit);
    Symbol* symbol1 = new Symbol;
    symbol1->type = new TypeInfo(TypeInfo::I32);
    print_i32->params.push_back(std::pair("value",symbol1));
    functions_table["print_i32"] = print_i32;

    FunctionInfo* println_i32 = new FunctionInfo;
    println_i32->return_type = new TypeInfo(TypeInfo::Unit);
    Symbol* symbol2 = new Symbol;
    symbol2->type = new TypeInfo(TypeInfo::I32);
    println_i32->params.push_back(std::pair("value",symbol2));
    functions_table["println_i32"] = println_i32;

    // 1. 扫描所有items构建symbol table 检查同类重名
    for(auto item : node->items){
        if(item->kind == FnItem){
            FnItemNode* child_node = static_cast<FnItemNode*>(item);
            FunctionInfo* func = new FunctionInfo;
            if(child_node->has_generic) func->has_generic = true;
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
                // ResolveSelfType(field_.second,child_node->name);
                // field 的类型检查放在全部扫描完一遍之后
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
            if(const_info->type->kind == TypeInfo::Default) const_info->type->kind = TypeInfo::I32;
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
            else if(child_node->value->kind == PathExpr){
                // 常量表达式是路径
                auto path_expr_ptr = static_cast<PathExprNode*>(child_node->value);
                for(auto seg : path_expr_ptr->segments){
                    const_info->path_value.push_back(seg.first);
                }
            }
            // 检查命名合法性
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
                        if(const_in_struct->type->kind == TypeInfo::Default){
                            const_in_struct->type->kind = TypeInfo::I32;
                        }
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
                        else if(const_ptr->value->kind == PathExpr){
                            auto path_expr_ptr = static_cast<PathExprNode*>(const_ptr->value);
                            for(auto seg : path_expr_ptr->segments){
                                const_in_struct->path_value.push_back(seg.first);
                            }
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
            if(it->second->return_type->kind != TypeInfo::Unit){
                return true; // main函数返回值不是Unit
            }
            if(it->second->has_generic){
                return true; // main不能有泛型参数
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
        if(it->second->path_value.size() > 0){
            // 检查path的合法性 是否存在循环
            std::vector<std::string> beg{};
            beg.push_back(it->first);
            if(!CheckRecursiveConst(beg,beg)) return true;
        }
    }

    for(auto it = structs_table.begin(); it != structs_table.end(); it++){
        auto fields = it->second->fields;
        std::set<std::string> type_list{};
        for(auto it2 = fields.begin(); it2 != fields.end(); it2++){
            // field里的类型和trait相对应的检查
            if(it2->second->kind == TypeInfo::Struct){
                // 检查这个类型是否存在
                if(structs_table.find(it2->second->name) == structs_table.end()){
                    // 不存在
                    return true;
                }
                // 检查是否存在类型循环
                std::set<std::string> history{};
                history.insert(it->first);
                if(!CheckRecursiveField(history,it2->second->name)){
                    return true; // 循环类型
                }
            }
            else if(it2->second->kind == TypeInfo::Array){
                // Array的element type也要检查
                TypeInfo inner = *it2->second->element;
                while(inner.kind == TypeInfo::Array){
                    // 处理Array的多层嵌套
                    inner = *inner.element;
                }
                if(inner.kind == TypeInfo::Struct){
                    if(structs_table.find(inner.name) == structs_table.end()){
                        return true;
                    }
                    // 类似的检查是否存在循环类型
                    std::set<std::string> history{};
                    history.insert(it->first);
                    if(!CheckRecursiveField(history,inner.name)){
                        return true; // 循环类型
                    }
                }
            }
            else if(it2->second->kind == TypeInfo::Ref || it2->second->kind == TypeInfo::Vec || it2->second->kind == TypeInfo::Box){
                TypeInfo* inner = it2->second->element;
                while(inner->kind == TypeInfo::Ref || inner->kind == TypeInfo::Vec || inner->kind == TypeInfo::Box){
                    inner = inner->element;
                }
                if(inner->kind == TypeInfo::Struct && inner->name == "Self"){
                    inner->name = it->first;
                }
            }
            if(!CheckDerivedTrait(it->second->derived,it2->second)) return true;
        }
        auto consts = it->second->consts;
        for(auto const_ : consts){
            if(const_.second->path_value.size() > 0){
                // 是path类型的常量值 检查这个path是否合法
                std::vector<std::string> beg{};
                beg.push_back(it->first);
                beg.push_back(const_.first);
                if(!CheckRecursiveConst(beg,beg)) return true;
            }
        }
        auto methods = it->second->methods;
        for(auto method : methods){
            auto func_info = method.second;
            // 检查参数
            for(auto param : func_info->params){
                if(param.second->type->kind == TypeInfo::Struct && structs_table.find(param.second->type->name) == structs_table.end()){
                    return true;
                }
            }
            // 检查返回值
            if(func_info->return_type->kind == TypeInfo::Struct && func_info->return_type->name == "Self"){
                it->second->methods[method.first]->return_type = new TypeInfo(TypeInfo::Struct);
                it->second->methods[method.first]->return_type->name = it->first;
            }
            if(func_info->return_type->kind == TypeInfo::Struct && structs_table.find(func_info->return_type->name) == structs_table.end()){
                return true; // 不存在的类型
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
        case UnaryExpr: return VisitUnaryExpr(static_cast<UnaryExprNode*>(node));
        case CastExpr: return VisitCastExpr(static_cast<CastExprNode*>(node));
        case PathExpr: return VisitPathExpr(static_cast<PathExprNode*>(node));
        case StructExpr: return VisitStructExpr(static_cast<StructExprNode*>(node));
        case ArrayExpr: return VisitArrayExpr(static_cast<ArrayExprNode*>(node));
        case ArrayRepeat: return VisitArrayRepeat(static_cast<ArrayRepeatNode*>(node));
        case FieldExpr: return VisitFieldExpr(static_cast<FieldExprNode*>(node));
        case IndexExpr: return VisitIndexExpr(static_cast<IndexExprNode*>(node));
        case CallExpr: return VisitCallExpr(static_cast<CallExprNode*>(node));
        case MethodCallExpr: return VisitMethodCallExpr(static_cast<MethodCallExprNode*>(node));
        case ReturnExpr: return VisitReturnExpr(static_cast<ReturnExprNode*>(node));
        // types
        case UnitType: return VisitUnitType(static_cast<UnitTypeNode*>(node));
        case PathType: return VisitPathType(static_cast<PathTypeNode*>(node));
        case ArrayType: return VisitArrayType(static_cast<ArrayTypeNode*>(node));
        case RefType: return VisitRefType(static_cast<RefTypeNode*>(node));
        // others
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
        // 会分派到全局Fn那里导致找不到 TODO
        // if(item->kind == ImplItem){
        //     auto associated = static_cast<ImplItemNode*>(item);
        //     for(auto associated_item : associated->associatedItems){
        //         if(associated_item->kind == FnItem){
        //             scopes.clear();
        //             top_params.clear();
        //             layer = -1;
        //             Visit(associated_item);
        //         }
        //     }
        // }
    }
}
void SemanticCheck::VisitFnItem(FnItemNode* node){
    FunctionInfo* func_info = functions_table[node->name];
    // 把参数放进作用域
    for(auto p : func_info->params){
        top_params[p.first] = p.second;
    }
    function_return_types.clear(); // 记录多个return type
    TypeInfo return_ = VisitAndGetType(node->blockExpr);
    if(return_.kind == TypeInfo::Unknown) error = true;
    if(return_.kind != TypeInfo::Never && !IsTypeEqual(return_,*func_info->return_type)) error = true; // 返回类型不匹配
    for(auto type : function_return_types){
        if(type.kind != TypeInfo::Never && !IsTypeEqual(type,*func_info->return_type)){
            error = true;
        }
    }
}
void SemanticCheck::VisitStructItem(StructItemNode* node){}
void SemanticCheck::VisitConstItem(ConstItemNode* node){}
void SemanticCheck::VisitImplItem(ImplItemNode* node){}
void SemanticCheck::VisitLetStmt(LetStmtNode* node){
    // 允许name shadowing
    Symbol* symbol = new Symbol;
    symbol->type = new TypeInfo(TypeInfo::Unknown);
    if(node->mut) symbol->mut = true;
    if(node->type != nullptr){
        TypeInfo defined_type = VisitAndGetType(node->type);
        if(defined_type.kind == TypeInfo::Unknown) error = true; // 不存在的type
        TypeInfo expr_type = VisitAndGetType(node->expr);
        if(expr_type.kind == TypeInfo::Unknown) error = true; // 不存在的type
        if(expr_type.kind != TypeInfo::Never && !IsTypeEqual(defined_type,expr_type) && !CanCoerce(expr_type,defined_type)) error = true;
        PlaceInfo expr_place = AnalyzePlace(node->expr);
        if(defined_type.kind == TypeInfo::Ref && defined_type.is_mut){
            if(expr_place.has_pass_shared_ref){
                error = true;
            }
        }
        *symbol->type = defined_type;
    }
    else{
        TypeInfo expr_type = VisitAndGetType(node->expr);
        if(expr_type.kind == TypeInfo::Unknown) error = true;
        // if(expr_type.kind == TypeInfo::Default) expr_type.kind = TypeInfo::I32;
        *symbol->type = expr_type;
    }
    scopes[layer][node->name] = symbol; // 加入作用域  
}
void SemanticCheck::VisitExprStmt(ExprStmtNode* node){
    if(node->expr != nullptr){
        TypeInfo type = VisitAndGetType(node->expr);
        if(node->expr->kind == BlockExpr){
            if(type.kind != TypeInfo::Unit) error = true;
        }
        if(type.kind == TypeInfo::Never && !diverge.empty()){
            diverge.back() = true;
        }
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitBlockExpr(BlockExprNode* node){
    scopes.emplace_back();
    layer++;
    diverge.push_back(false);
    for(auto stmt : node->statements){
        Visit(stmt);
    }
    TypeInfo return_type;
    if(node->return_expression == nullptr) return_type.kind = TypeInfo::Unit;
    else return_type = VisitAndGetType(node->return_expression);
    if(return_type.kind == TypeInfo::Unknown){
        error = true;
        return TypeInfo();
    }
    if(return_type.kind == TypeInfo::Unit && diverge.back() == true){
        return_type = TypeInfo::Never;
    }
    diverge.pop_back();
    scopes.pop_back();
    layer--;
    return return_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitIntLit(IntLitNode* node){
    TypeInfo type;
    type.int_val = node->value;
    if(node->suffix.size() == 0) type.kind = TypeInfo::Default;
    else if(node->suffix == "i32") type.kind = TypeInfo::I32;
    else if(node->suffix == "u32") type.kind = TypeInfo::U32;
    else if(node->suffix == "isize") type.kind = TypeInfo::Isize;
    else if(node->suffix == "usize") type.kind = TypeInfo::Usize;
    else error = true; // 不存在的整数类型
    return type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitBoolLit(BoolLitNode* node){
    TypeInfo type;
    type.kind = TypeInfo::Bool;
    type.bool_val = node->value;
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
            error = true; // 等号左边不是合法的左值place
        }
        if(right_type.kind != TypeInfo::Never && !IsTypeEqual(left_type,right_type)){
            while(!IsTypeEqual(left_type,right_type)){
                // RHS auto-deref
                if(right_type.kind == TypeInfo::Ref || right_type.kind == TypeInfo::Box){
                    right_type = *right_type.element;
                }
                else break;
            }
            if(!IsTypeEqual(left_type,right_type)){
                error = true; // 左右type不一致
            }
        }
        return left_type;
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitBinaryExpr(BinaryExprNode* node){
    if(node->op.size() == 0){
        return VisitAndGetType(node->operands[0]);
    }
    else{
        // accept one shared-reference layer
        TypeInfo type;
        switch(node->level){
            case 0:case 1:{
                for(auto op : node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    // if(op_type.kind == TypeInfo::Ref && !op_type.is_mut) op_type = *op_type.element;
                    if(op_type.kind != TypeInfo::Bool) error = true;
                }
                type.kind = TypeInfo::Bool;
                break;
            }
            case 2:{
                TypeInfo prev_type = VisitAndGetType(node->operands[0]);
                // if(prev_type.kind == TypeInfo::Ref && !prev_type.is_mut) prev_type = *prev_type.element;
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    // if(op_type.kind == TypeInfo::Ref && !op_type.is_mut) op_type = *op_type.element;
                    if(op_type.kind == TypeInfo::Unknown){
                        error = true;
                        break;
                    }
                    if(!IsTypeEqual(prev_type,op_type)){
                        // 只允许右操作数向左操作数的类型强制转换（如 &mut T -> &T）
                        if(CanCoerce(op_type,prev_type)){
                            op_type = prev_type;
                        }
                        else{
                            error = true;
                            break;
                        }
                    }
                    if(!CanPartialEq(prev_type)){
                        error = true;
                        break;
                    }
                    prev_type = op_type;
                }
                type.kind = TypeInfo::Bool;
                break;
            }
            case 3: case 4: case 5:{
                TypeInfo prev_type = VisitAndGetType(node->operands[0]);
                if(prev_type.kind == TypeInfo::Ref && !prev_type.is_mut) prev_type = *prev_type.element;
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind == TypeInfo::Ref && !op_type.is_mut) op_type = *op_type.element;
                    if(op_type.kind == TypeInfo::Default) op_type.kind = TypeInfo::I32;
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
                if(first_type.kind == TypeInfo::Ref && !first_type.is_mut) first_type = *first_type.element;
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind == TypeInfo::Ref && !op_type.is_mut) op_type = *op_type.element;
                    if(op_type.kind == TypeInfo::Default) op_type.kind = TypeInfo::I32;
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
                if(prev_type.kind == TypeInfo::Ref && !prev_type.is_mut) prev_type = *prev_type.element;
                for(auto op: node->operands){
                    TypeInfo op_type = VisitAndGetType(op);
                    if(op_type.kind == TypeInfo::Ref && !op_type.is_mut) op_type = *op_type.element;
                    if(op_type.kind == TypeInfo::Default) op_type.kind = TypeInfo::I32;
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
SemanticCheck::TypeInfo SemanticCheck::VisitUnaryExpr(UnaryExprNode* node){
    if(node->op.size() == 0){
        return VisitAndGetType(node->expr);
    }
    else{
        if(node->op == "*"){
            // 解引用
            TypeInfo deref_type = VisitAndGetType(node->expr);
            if(deref_type.kind == TypeInfo::Ref || deref_type.kind == TypeInfo::Box){
                return *deref_type.element;
            }
            else{
                error = true;
                return TypeInfo();
            }
        }
        else if(node->op == "&" || node->op == "&mut"){
            // 引用
            TypeInfo ref_type;
            ref_type.kind = TypeInfo::Ref;
            ref_type.element = new TypeInfo;
            *ref_type.element = VisitAndGetType(node->expr);
            if(node->mut){
                ref_type.is_mut = true;
                // 对place取&mut要求可写；对右值取&mut会物化一个临时值，总是允许
                // &mut 作用于右值时会物化一个临时值（temporary materialization），总是允许；
                // 只有作用于指向已有存储的 place 表达式（变量、解引用、字段、索引）时才要求该 place 可写。
                if(IsPlaceExpr(node->expr) && !CanWrite(node->expr)){
                    error = true;
                }
            } 
            return ref_type;
        }
        else if(node->op == "&&"  || node->op == "&&mut"){
            TypeInfo ref_type;
            ref_type.kind = TypeInfo::Ref;
            TypeInfo inner_ref_type;
            inner_ref_type.kind = TypeInfo::Ref;
            if(node->mut){
                inner_ref_type.is_mut = true;
                // 内层&mut的规则与单层一致：place要求可写，右值物化为临时值
                if(IsPlaceExpr(node->expr) && !CanWrite(node->expr)){
                    error = true;
                }
            }
            inner_ref_type.element = new TypeInfo(VisitAndGetType(node->expr));
            ref_type.element = new TypeInfo(inner_ref_type);
            return ref_type;
        }
        else{
            TypeInfo type = VisitAndGetType(node->expr);
            // 允许一层共享引用作为算术/位运算的操作数
            if(type.kind == TypeInfo::Ref && !type.is_mut && type.element != nullptr) type = *type.element;
            if(type.kind == TypeInfo::Default) type.kind = TypeInfo::I32;
            if(node->op == "-"){
                if(type.kind != TypeInfo::I32 && type.kind != TypeInfo::Isize){
                    error = true;
                }
            }
            if(node->op == "!"){
                if(type.kind != TypeInfo::Bool && type.kind != TypeInfo::I32 && type.kind != TypeInfo::U32 && type.kind != TypeInfo::Isize && type.kind != TypeInfo::Usize){
                    error = true;
                }
            }
            return type;
        }
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitCastExpr(CastExprNode* node){
    if(node->types.size() == 0){
        return VisitAndGetType(node->expr);
    }
    else{
        // cast支持： integer-to-integer casts and bool-to-integer casts
        TypeInfo cur_type = VisitAndGetType(node->expr);
        if(cur_type.kind == TypeInfo::Default) cur_type.kind = TypeInfo::I32;
        for(auto type : node->types){
            if(cur_type.kind == TypeInfo::I32 || cur_type.kind == TypeInfo::U32
            || cur_type.kind == TypeInfo::Isize || cur_type.kind == TypeInfo::Usize){
                TypeInfo cast_type = VisitAndGetType(type);
                if(cast_type.kind == TypeInfo::I32 || cast_type.kind == TypeInfo::U32
                || cast_type.kind == TypeInfo::Isize || cast_type.kind == TypeInfo::Usize){
                    // integer-to-integer
                    cur_type = cast_type;
                }
                else{
                    error = true;
                    break;
                }
            }
            else if(cur_type.kind == TypeInfo::Bool){
                TypeInfo cast_type = VisitAndGetType(type);
                if(cast_type.kind == TypeInfo::I32 || cast_type.kind == TypeInfo::U32
                || cast_type.kind == TypeInfo::Isize || cast_type.kind == TypeInfo::Usize){
                    // bool-to-integer
                    cur_type = cast_type;
                }
                else{
                    error = true;
                    break;
                }
            }
            else{
                error = true;
                break;
            }
        }
        return cur_type;
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitIfExpr(IfExprNode* node){
    TypeInfo condition = VisitAndGetType(node->condition);
    if(condition.kind != TypeInfo::Never && condition.kind != TypeInfo::Bool){
        error = true;
    }
    TypeInfo if_type = VisitAndGetType(node->if_block);
    TypeInfo else_type;
    else_type.kind = TypeInfo::Unit;
    if(if_type.kind == TypeInfo::Unknown) error = true;
    if(node->else_block != nullptr){
        // 有else分支
        else_type = VisitAndGetType(node->else_block);
        if(else_type.kind == TypeInfo::Unknown) error = true;
        if(if_type.kind != TypeInfo::Never && else_type.kind != TypeInfo::Never && !IsTypeEqual(if_type,else_type)){
            if(CanCoerce(if_type,else_type)){
                return else_type;
            }
            if(CanCoerce(else_type,if_type)){
                return if_type;
            }
            error = true;
        }
        if(if_type.kind == TypeInfo::Never && else_type.kind == TypeInfo::Never){
            TypeInfo never_type;
            never_type.kind  = TypeInfo::Never;
            return never_type;
        }
        else{
            if(if_type.kind == TypeInfo::Never){
                return else_type;
            }
            else return if_type;
        }
    }
    else{
        // 没有else分支时，条件为假会正常结束，因此整个if始终为Unit
        if(if_type.kind != TypeInfo::Never && !IsTypeEqual(if_type,else_type)){
            if(CanCoerce(if_type,else_type)){
                return else_type;
            }
            if(CanCoerce(else_type,if_type)){
                return if_type;
            }
            error = true;
            return TypeInfo();
        }
        return else_type;
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitLoopExpr(LoopExprNode* node){
    TypeInfo loop_type;
    if(node->content != nullptr){
        CycleInfo loop_info;
        loop_info.is_loop = true;
        cycles_stack.push_back(loop_info); // cycles_stack记录当前最里层的循环
        bool outer_condition = analysize_condition;
        analysize_condition = false;
        loop_type = VisitAndGetType(node->content);
        analysize_condition = outer_condition;
        loop_info = cycles_stack.back();
        cycles_stack.pop_back();
        // loop体可以正常结束为Unit，也可以因为break等发散为Never
        if(loop_type.kind != TypeInfo::Unit && loop_type.kind != TypeInfo::Never) error = true;
        if(loop_info.exit_types.size() == 0){
            // 没有break
            diverge.back() = true;
        }
        bool all_never = true;
        TypeInfo lub_type = TypeInfo::Never;
        for(auto exit_type : loop_info.exit_types){
            // 检查exit_type是否兼容
            if(exit_type.kind == TypeInfo::Never) continue;
            else{
                all_never = false;
                if(lub_type.kind == TypeInfo::Never) lub_type = exit_type;
                else if(!IsTypeEqual(lub_type,exit_type)){
                    if(CanCoerce(exit_type,lub_type)) continue;
                    else if(CanCoerce(lub_type,exit_type)){
                        lub_type = exit_type;
                    }
                    else{
                        error = true;
                        return TypeInfo();
                    }
                }
            }
        }
        if(all_never) diverge.back() = true; // 所有break对应的操作数都发散
        loop_type = lub_type;
    }
    return loop_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitWhileExpr(WhileExprNode* node){
    CycleInfo while_info;
    while_info.is_loop = false;
    bool outer_condition = analysize_condition;
    analysize_condition = true;
    TypeInfo condition = VisitAndGetType(node->condition);
    analysize_condition = false;
    cycles_stack.push_back(while_info);
    if(condition.kind != TypeInfo::Never && condition.kind != TypeInfo::Bool){
        error = true;
    }
    TypeInfo while_type = VisitAndGetType(node->content);
    analysize_condition = outer_condition;
    while_info = cycles_stack.back();
    cycles_stack.pop_back();
    if(while_type.kind != TypeInfo::Unit) error = true;
    if(while_info.exit_types.size() != 0){
        for(auto exit_type : while_info.exit_types){
            if(exit_type.kind != TypeInfo::Unit){
                error = true;
                break;
            }
        }
    }
    return while_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitBreakExpr(BreakExprNode* node){
    if(cycles_stack.size() == 0){
        error = true; // 在循环外面break
        return TypeInfo(TypeInfo::Never);
    }
    if(analysize_condition){
        error = true;
    }
    CycleInfo &cycle = cycles_stack.back();
    TypeInfo break_type;
    if(node->expr != nullptr){
        break_type = VisitAndGetType(node->expr);
        if(break_type.kind == TypeInfo::Unknown) error = true;
        cycle.exit_types.push_back(break_type);
    }
    else{
        break_type.kind = TypeInfo::Unit; // 默认为()
        cycle.exit_types.push_back(break_type);
    }
    return TypeInfo(TypeInfo::Never); // break的类型总是为never
}
SemanticCheck::TypeInfo SemanticCheck::VisitContinueExpr(ContinueExprNode* node){
    if(cycles_stack.size() == 0 || analysize_condition){
        error = true;
        // return TypeInfo(TypeInfo::Never);
    }
    // CycleInfo &cycle = cycles_stack.back();
    // cycle.exit_types.push_back(TypeInfo(TypeInfo::Never));
    return TypeInfo(TypeInfo::Never);
}
SemanticCheck::TypeInfo SemanticCheck::VisitPathExpr(PathExprNode* node){ 
    if(node->segments.size() == 1){
        // const
        if(constants_table.find(node->segments[0].first) != constants_table.end()){
            return *constants_table[node->segments[0].first]->type;
        }
        // scope里找
        for(auto it = scopes.rbegin(); it != scopes.rend(); it++){
            if(it->find(node->segments[0].first) != it->end()){
                in_scope = true;
                Symbol* symbol = (*it)[node->segments[0].first];
                return *symbol->type;
            }
        }
        // top_params里找
        if(top_params.find(node->segments[0].first) != top_params.end()){
            in_scope = true;
            return *top_params[node->segments[0].first]->type;
        }
        // 如果存在同名的结构体和函数 优先查找函数表 但是可能是结构体！
        // 函数表里找
        if(functions_table.find(node->segments[0].first) != functions_table.end()){
            if(node->segments[0].second.size() != 0){
                error = true; // 函数没有泛型参数
                return TypeInfo();
            }
            call_path.push_back(node->segments[0].first);
            auto func_info = functions_table[node->segments[0].first];
            return *func_info->return_type;
        }
        // 结构体表里查
        if(structs_table.find(node->segments[0].first) != structs_table.end()){
            if(node->segments[0].second.size() != 0){
                error = true; // 结构体没有泛型参数
                return TypeInfo();
            }
            TypeInfo type(TypeInfo::Struct);
            type.name = node->segments[0].first;
            return type;
        }
        error = true;
        return TypeInfo(TypeInfo::Unknown);
    }
    else if(node->segments.size() == 2){
        std::string first = node->segments[0].first;
        std::string second = node->segments[1].first;
        if(structs_table.find(first) != structs_table.end()){
            // 结构体里的const
            auto const_in_struct = structs_table[first]->consts;
            if(const_in_struct.find(second) != const_in_struct.end()){
                return *const_in_struct[second]->type;
            }
            // 结构体里的method
            auto method_in_struct = structs_table[first]->methods;
            if(method_in_struct.find(second) != method_in_struct.end()){
                call_path.push_back(first);
                call_path.push_back(second);
                return *method_in_struct[second]->return_type;
            }
            if(second == "clone" && structs_table[first]->derived.find(Clone) != structs_table[first]->derived.end()){
                call_path.push_back(first);
                call_path.push_back(second);
                TypeInfo type(TypeInfo::Struct);
                type.name = first;
                return type;
            }
        }
        else if(first == "Vec"){
            if(second == "new" || second == "len" || second == "push" || second == "clone"){
                auto generic = node->segments[0].second;
                if(generic.size() != 1 || node->segments[1].second.size() != 0){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo inner = VisitAndGetType(generic[0]);
                TypeInfo vec_type;
                vec_type.kind = TypeInfo::Vec;
                vec_type.element = new TypeInfo(inner);
                call_path.push_back(first);
                call_path.push_back(second);
                return vec_type;
            }
            else{
                error = true;
                return TypeInfo();
            }
        }
        else if(first == "Box"){
            if(second == "new"){
                auto generic = node->segments[0].second;
                if(generic.size() != 1 || node->segments[1].second.size() != 0){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo inner = VisitAndGetType(generic[0]);
                TypeInfo box_type;
                box_type.kind = TypeInfo::Box;
                box_type.element = new TypeInfo(inner);
                call_path.push_back(first);
                call_path.push_back(second);
                return box_type;
            }
            else if(second == "clone"){
                auto generic = node->segments[0].second;
                if(generic.size() != 1 || node->segments[1].second.size() != 0){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo inner = VisitAndGetType(generic[0]);
                TypeInfo box_type;
                box_type.kind = TypeInfo::Box;
                box_type.element = new TypeInfo(inner);
                call_path.push_back(first);
                call_path.push_back(second);
                return box_type; // 和new一样
            }
            else{
                error = true;
                return TypeInfo();
            }
        }
        error = true;
        return TypeInfo(TypeInfo::Unknown);
    }
    else{
        error = true;
        return TypeInfo(TypeInfo::Unknown);
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitStructExpr(StructExprNode* node){
    auto path = static_cast<PathExprNode*>(node->struct_name);
    if(path->segments.size() != 1 || path->segments[0].second.size() != 0){
        error = true; // 多段路径 有泛型参数
        return TypeInfo();
    }
    if(structs_table.find(path->segments[0].first) == structs_table.end()){
        error = true; // 不存在
        return TypeInfo();
    }
    TypeInfo type = TypeInfo(TypeInfo::Struct);
    type.name = path->segments[0].first;
    
    auto struct_fields = structs_table[type.name]->fields;
    if(node->member_name.size() != node->expr.size() || node->member_name.size() != struct_fields.size()){
        error = true; // 参数数量不匹配
        return TypeInfo(TypeInfo::Unknown);
    }
    int cnt = 0;
    for(auto name : node->member_name){
        if(struct_fields.find(name) == struct_fields.end()){
            error = true; // 不存在这个成员变量
            return TypeInfo(TypeInfo::Unknown);
        }
        else{
            auto field_type = struct_fields[name];
            TypeInfo expr_type = VisitAndGetType(node->expr[cnt]);
            if(!IsTypeEqual(*field_type,expr_type)){
                error = true; // 赋值类型不匹配
                return TypeInfo(TypeInfo::Unknown);
            }
        }
        cnt++;
    }
    return type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitArrayExpr(ArrayExprNode* node){
    TypeInfo array_type = TypeInfo(TypeInfo::Array);
    TypeInfo lub_type = TypeInfo(TypeInfo::Never); // 数组类型最终取类型的least upper bound
    array_type.length = node->elements.size();
    if(array_type.length == 1){
        lub_type = VisitAndGetType(node->elements[0]);
    }
    else{
        for(auto element : node->elements){
            TypeInfo cur_type = VisitAndGetType(element);
            if(lub_type.kind == TypeInfo::Never){
               lub_type = cur_type;
            }
            else{
                if(!IsTypeEqual(lub_type,cur_type)){
                    if(CanCoerce(cur_type,lub_type)){
                        continue;
                    }
                    else if(CanCoerce(lub_type,cur_type)){
                        lub_type = cur_type;
                    }
                    else{
                        error = true;
                        return TypeInfo();
                    }
                }
            }
        }
    }
    array_type.element = new TypeInfo(lub_type);
    return array_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitArrayRepeat(ArrayRepeatNode* node){
    TypeInfo array_type = TypeInfo(TypeInfo::Array);
    TypeInfo inner_type = VisitAndGetType(node->element);
    if(inner_type.kind == TypeInfo::Unknown){
        error = true; // 未知类型
        return TypeInfo();
    }
    array_type.element = new TypeInfo(inner_type);
    in_scope = false;
    TypeInfo num_type = VisitAndGetType(node->num);
    if(in_scope){
        error = true; // 不是编译期常量
    }
    if(num_type.kind == TypeInfo::Default) num_type.kind = TypeInfo::Usize;
    // 判断num是否大于1
    if(num_type.kind != TypeInfo::Usize){
        error = true;
        return TypeInfo();
    }
    array_type.length = num_type.int_val;
    if(array_type.length > 1){
        // 检查数组元素是否满足Copy trait
        if(!CanCopy(inner_type)){
            error = true;
            return TypeInfo();
        }
    }
    return array_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitCallExpr(CallExprNode* node){
    call_path.clear();
    TypeInfo call_type = VisitAndGetType(node->func);
    if(call_type.kind == TypeInfo::Unknown){
        error = true;
        return TypeInfo();
    }
    // PathExpr里优先判断函数 可能和struct重名
    if(call_path.size() == 1){
        if(functions_table.find(call_path[0]) == functions_table.end()){
            error = true;
            return TypeInfo();
        }
        auto func_info = functions_table[call_path[0]];
        if(func_info->params.size() != node->args.size()){
            error = true;
            return TypeInfo();
        }
        int cnt = 0;
        for(auto param : func_info->params){
            TypeInfo param_type = VisitAndGetType(node->args[cnt]); // 调用node里存的参数类型
            // if(param_type.kind == TypeInfo::Default) param_type.kind = TypeInfo::I32;
            // 尝试强制转换
            if(!IsTypeEqual(param_type,*param.second->type) && !CanCoerce(param_type,*param.second->type)){
                error = true;
                return TypeInfo();
            }
            TypeInfo expected_type = *param.second->type; // 函数签名里写的参数类型
            if(expected_type.kind == TypeInfo::Ref && expected_type.is_mut){
                PlaceInfo argument_place = AnalyzePlace(node->args[cnt]);
                if(argument_place.has_pass_shared_ref){
                    error = true; // 不能通过共享/不可变路径提供 &mut 参数
                    return TypeInfo();
                }
            }
            cnt++;
        }
    }
    else if(call_path.size() == 2){
        // 检查一下这个associated function有没有self这个参数
        std::string first = call_path[0];
        std::string second = call_path[1];
        if(first == "Vec"){
            if(second == "new"){
                if(node->args.size() != 0){
                    error = true;
                    return TypeInfo();
                }
                return call_type;
            }
            else if(second == "len"){
                if(node->args.size() != 1){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo receiver_type = VisitAndGetType(node->args[0]);
                if(receiver_type.kind != TypeInfo::Ref || receiver_type.element == nullptr ||
                   !IsTypeEqual(*receiver_type.element,call_type)){
                    error = true;
                    return TypeInfo();
                }
                return TypeInfo(TypeInfo::Usize);
            }
            else if(second == "clone"){
                if(node->args.size() != 1){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo receiver_type = VisitAndGetType(node->args[0]);
                if(receiver_type.kind != TypeInfo::Ref || receiver_type.element == nullptr ||
                   !IsTypeEqual(*receiver_type.element,call_type)){
                    error = true;
                    return TypeInfo();
                }
                if(!CanClone(call_type)) error = true;
                return call_type;
            }
            else if(second == "push"){
                if(node->args.size() != 2){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo receiver_type = VisitAndGetType(node->args[0]);
                if(receiver_type.kind != TypeInfo::Ref || !receiver_type.is_mut ||
                   receiver_type.element == nullptr || !IsTypeEqual(*receiver_type.element,call_type)){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo value_type = VisitAndGetType(node->args[1]);
                if(value_type.kind != TypeInfo::Never &&
                   !IsTypeEqual(value_type,*call_type.element)){
                    error = true;
                    return TypeInfo();
                }
                return TypeInfo(TypeInfo::Unit);
            }
            else{
                error = true;
                return TypeInfo();
            }
        }
        if(first == "Box"){
            if(second == "new"){
                if(node->args.size() != 1){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo arg_type = VisitAndGetType(node->args[0]);
                if(arg_type.kind == TypeInfo::Unknown || !IsTypeEqual(arg_type,*call_type.element)){
                    error = true;
                    return TypeInfo();
                }
                return call_type;
            }
            else if(second == "clone"){
                if(node->args.size() != 1){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo arg_type = VisitAndGetType(node->args[0]);
                // 进行类型的合法性检查
                if(arg_type.kind == TypeInfo::Unknown || !IsTypeEqual(*arg_type.element,call_type)){
                    error = true;
                    return TypeInfo();
                }
                return call_type;
            }
            else{
                error = true;
                return TypeInfo();
            }
        }
        if(structs_table.find(first) == structs_table.end()){
            error = true; // 不存在的结构体
            return TypeInfo();
        }
        auto struct_info = structs_table[first];
        // 固有方法优先于derive生成的clone
        if(second == "clone" && struct_info->methods.find(second) == struct_info->methods.end()
           && struct_info->derived.find(Clone) != struct_info->derived.end()){
            if(node->args.size() != 1){
                error = true;
                return TypeInfo();
            }
            TypeInfo receiver_type = VisitAndGetType(node->args[0]);
            if(receiver_type.kind != TypeInfo::Ref || receiver_type.element == nullptr ||
               !IsTypeEqual(*receiver_type.element,call_type)){
                error = true;
                return TypeInfo();
            }
            return call_type;
        }
        if(struct_info->methods.find(second) == struct_info->methods.end()){
            error = true; // 不存在的methhod
            return TypeInfo();
        }
        auto method = struct_info->methods[second];
        if(method->params.size() != node->args.size()){
            error = true;
            return TypeInfo();
        }
        int cnt = 0;
        for(auto param : method->params){
            TypeInfo param_type = VisitAndGetType(node->args[cnt]);
            if(!IsTypeEqual(param_type,*param.second->type) && !CanCoerce(param_type,*param.second->type)){
                error = true;
                return TypeInfo();
            }
            cnt++;
        }
    }
    else{
        error = true;
        return TypeInfo();
    }
    return call_type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitMethodCallExpr(MethodCallExprNode* node){
    // 解引用之前先检查是不是clone()，如果是不需要先解引用
    TypeInfo receiver_type = VisitAndGetType(node->receiver);
    if(node->name.first == "clone"){
        if(node->args.size() != 0){
            error = true;
            return TypeInfo();
        }
        if(receiver_type.kind == TypeInfo::Ref && receiver_type.element != nullptr &&
           CanClone(*receiver_type.element)){
            receiver_type = *receiver_type.element;
        }
        if(!CanClone(receiver_type)){
            error = true;
            return TypeInfo();
        }
        return receiver_type;
    }
    // auto dereference
    while(receiver_type.kind == TypeInfo::Ref || receiver_type.kind == TypeInfo::Box){
        receiver_type = *receiver_type.element;
    }
    if(receiver_type.kind == TypeInfo::Array){
        // 内建方法len
        if(node->name.first == "len"){
            if(node->args.size() != 0){
                error = true;
                return TypeInfo();
            }
            else return TypeInfo(TypeInfo::Usize);
        }
        else{
            error = true;
            return TypeInfo();
        }
    }
    else if(receiver_type.kind == TypeInfo::Vec){
        if(node->name.first == "len"){
            if(node->args.size() != 0 || node->name.second.size() != 0){
                error = true;
                return TypeInfo();
            }
            else return TypeInfo(TypeInfo::Usize);
        }
        else if(node->name.first == "is_empty"){
            if(node->args.size() != 0){
                error = true;
                return TypeInfo();
            }
            else return TypeInfo(TypeInfo::Bool);
        }
        else if(node->name.first == "push"){
            // 接收者可能是存储在不可变数组/Box里的&mut Vec，先穿透引用层再判断可变性
            PlaceInfo receiver_place = AnalyzePlace(node->receiver);
            while(receiver_place.type.kind == TypeInfo::Ref || receiver_place.type.kind == TypeInfo::Box){
                receiver_place = DereferencePlace(receiver_place);
            }
            if(!receiver_place.can_mutate_contents){
                error = true;
                return TypeInfo();
            }
            if(node->args.size() != 1){
                error = true;
                return TypeInfo();
            }
            else{
                TypeInfo add_type = VisitAndGetType(node->args[0]);
                if(add_type.kind != TypeInfo::Never && !IsTypeEqual(add_type,*receiver_type.element)){
                    error = true;
                    return TypeInfo();
                }
                else return TypeInfo(TypeInfo::Unit);
            }
        }
        else if(node->name.first == "remove"){
            PlaceInfo receiver_place = AnalyzePlace(node->receiver);
            while(receiver_place.type.kind == TypeInfo::Ref || receiver_place.type.kind == TypeInfo::Box){
                receiver_place = DereferencePlace(receiver_place);
            }
            if(!receiver_place.can_mutate_contents){
                error = true;
                return TypeInfo();
            }
            if(node->args.size() != 1){
                error = true;
                return TypeInfo();
            }
            else{
                TypeInfo remove_type = VisitAndGetType(node->args[0]);
                if(remove_type.kind != TypeInfo::Default && remove_type.kind != TypeInfo::Usize){
                    error = true;
                    return TypeInfo();
                }
                else{
                    return *receiver_type.element;
                }
            }
        }
        else{
            error = true;
            return TypeInfo();
        }
    }
    else if(receiver_type.kind == TypeInfo::Struct){
        call_path.clear();
        auto struct_info = structs_table[receiver_type.name];
        if(struct_info->methods.find(node->name.first) == struct_info->methods.end()){
            error = true; // 不存在这个method
            return TypeInfo();
        }
        auto method_info = struct_info->methods[node->name.first];
        if(method_info->params.size() == 0){
            error = true; // 没有self参数
            return TypeInfo();
        }
        if(method_info->params[0].first != "self" || method_info->params.size() - 1 != node->args.size()){
            error = true;
            return TypeInfo();
        }
        TypeInfo* self_type = method_info->params[0].second->type;
        // 如果method第一个参数是&mut self 需要检查receiver是否具有can_mut_content性质
        // 包括自动解引用之后是否可写（同样不能穿透共享引用）
        if(self_type->kind == TypeInfo::Ref && self_type->is_mut){
            PlaceInfo receiver_place = AnalyzePlace(node->receiver);
            while(receiver_place.type.kind == TypeInfo::Ref || receiver_place.type.kind == TypeInfo::Box){
                receiver_place = DereferencePlace(receiver_place);
            }
            if(receiver_place.type.kind != TypeInfo::Struct || !receiver_place.can_mutate_contents){
                error = true;
                return TypeInfo();
            }
        }
        int cnt = 1;
        for(auto arg : node->args){
            TypeInfo arg_type = VisitAndGetType(arg);
            if(!IsTypeEqual(arg_type,*method_info->params[cnt].second->type) && !CanCoerce(arg_type,*method_info->params[cnt].second->type)){
                error = true;
                return TypeInfo();
            }
            cnt++;
        }
        return *method_info->return_type;
    }
    return TypeInfo();
}
SemanticCheck::TypeInfo SemanticCheck::VisitFieldExpr(FieldExprNode* node){
    TypeInfo receiver = VisitAndGetType(node->receiver);
    // auto deref
    while(receiver.kind == TypeInfo::Box || receiver.kind == TypeInfo::Ref){
        receiver = *receiver.element;
    }
    if(receiver.kind != TypeInfo::Struct){
        error = true; // 不是结构体
        return TypeInfo();
    }
    StructInfo* struct_info = structs_table[receiver.name];
    if(struct_info->fields.find(node->name) == struct_info->fields.end()){
        // 不存在这个成员
        error = true;
        return TypeInfo();
    }
    else{
        return *struct_info->fields[node->name];
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitIndexExpr(IndexExprNode* node){
    TypeInfo base_type = VisitAndGetType(node->base);
    // auto dereference
    while(base_type.kind == TypeInfo::Ref || base_type.kind == TypeInfo::Box){
         base_type = *base_type.element;
    }
    if(base_type.kind == TypeInfo::Array || base_type.kind == TypeInfo::Vec){
        // 数组类型
        TypeInfo index_type = VisitAndGetType(node->index);
        if(index_type.kind != TypeInfo::Usize && index_type.kind != TypeInfo::Default){
            error = true;
            return TypeInfo();
        }
        return *base_type.element;
    }
    error = true;
    return TypeInfo();
}
SemanticCheck::TypeInfo SemanticCheck::VisitReturnExpr(ReturnExprNode* node){
    TypeInfo return_type(TypeInfo::Never);
    if(node->expr == nullptr){
        function_return_types.push_back(TypeInfo(TypeInfo::Unit));
        return return_type;
    } 
    else{
        function_return_types.push_back(VisitAndGetType(node->expr));
        return return_type;
    }
}
// types
SemanticCheck::TypeInfo SemanticCheck::VisitUnitType(UnitTypeNode* node){
    return TypeInfo(TypeInfo::Unit);
}
SemanticCheck::TypeInfo SemanticCheck::VisitPathType(PathTypeNode* node){
    if(node->segments.size() == 1){
        std::string name = node->segments[0].first;
        auto generics = node->segments[0].second;
        if(name == "i32" && generics.size() == 0){
            return TypeInfo(TypeInfo::I32);
        }
        else if(name == "u32" && generics.size() == 0){
            return TypeInfo(TypeInfo::U32);
        }
        else if(name == "isize" && generics.size() == 0){
            return TypeInfo(TypeInfo::Isize);
        }
        else if(name == "usize" && generics.size() == 0){
            return TypeInfo(TypeInfo::Usize);
        }
        else if(name == "bool" && generics.size() == 0){
            return TypeInfo(TypeInfo::Bool);
        }
        else if(name == "Vec" && generics.size() == 1){
            TypeInfo vec_type;
            vec_type.kind = TypeInfo::Vec;
            vec_type.element = new TypeInfo(VisitAndGetType(generics[0]));
            return vec_type;
        }
        else if(name == "Box" && generics.size() == 1){
            TypeInfo box_type;
            box_type.kind = TypeInfo::Box;
            box_type.element = new TypeInfo(VisitAndGetType(generics[0]));
            return box_type;
        }
        else{
            if(structs_table.find(name) != structs_table.end()){
                if(node->segments[0].second.size() != 0){
                    error = true;
                    return TypeInfo();
                }
                TypeInfo type;
                type.kind = TypeInfo::Struct;
                type.name = name;
                return type;
            }
            else return TypeInfo();
        }
    }
    else{
        return TypeInfo();
    }
}
SemanticCheck::TypeInfo SemanticCheck::VisitArrayType(ArrayTypeNode* node){
    TypeInfo type,element;
    type.kind = TypeInfo::Array;
    element = VisitAndGetType(node->type);
    type.element = new TypeInfo;
    *type.element = element;
    in_scope = false;
    TypeInfo num_type = VisitAndGetType(node->length);
    if(in_scope) error = true;
    if(num_type.kind == TypeInfo::Default) num_type.kind = TypeInfo::Usize;
    if(num_type.kind != TypeInfo::Usize) error = true;
    else{
        type.length = num_type.int_val;
    }
    return type;
}
SemanticCheck::TypeInfo SemanticCheck::VisitRefType(RefTypeNode* node){
    TypeInfo type;
    type.kind = TypeInfo::Ref;
    if(node->mut) type.is_mut = true;
    type.element = new TypeInfo;
    *type.element = VisitAndGetType(node->type);
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
    TypeInfo* type_info = new TypeInfo(TypeInfo::Unknown);
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
        std::string seg_type = path_ptr->segments[0].first;
        if(path_ptr->segments.size() == 1){
            auto generics = path_ptr->segments[0].second;
            if(seg_type == "i32" && generics.size() == 0){
                type_info->kind = TypeInfo::I32;
            }
            else if(seg_type == "u32" && generics.size() == 0){
                type_info->kind = TypeInfo::U32;
            }
            else if(seg_type == "isize" && generics.size() == 0){
                type_info->kind = TypeInfo::Isize;
            }
            else if(seg_type == "usize" && generics.size() == 0){
                type_info->kind = TypeInfo::Usize;
            }
            else if(seg_type == "bool" && generics.size() == 0){
                type_info->kind = TypeInfo::Bool;
            }
            else if(seg_type == "Vec" && generics.size() == 1){
                type_info->kind = TypeInfo::Vec;
                type_info->element = GetTypeInfo(generics[0]);
            }
            else if(seg_type == "Box" && generics.size() == 1){
                type_info->kind = TypeInfo::Box;
                type_info->element = GetTypeInfo(generics[0]);
            }
            else{
                // 允许前向引用，先默认存在这个Struct
                type_info->kind = TypeInfo::Struct;
                type_info->name = seg_type;
            }
        }
    }
    return type_info;
}
// void SemanticCheck::ResolveSelfType(TypeInfo* type,const std::string& struct_name){
//     if(type == nullptr) return;
//     if(type->kind == TypeInfo::Struct && type->name == "Self"){
//         type->name = struct_name;
//     }
//     ResolveSelfType(type->element,struct_name);
// }
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
bool SemanticCheck::IsTypeEqual(const TypeInfo& a,const TypeInfo& b){
    if(a.kind == TypeInfo::Never || b.kind == TypeInfo::Never){
        return true;
    }
    if(a.kind == TypeInfo::Default){
        if(b.kind == TypeInfo::I32 || b.kind == TypeInfo::U32 || b.kind == TypeInfo::Isize || b.kind == TypeInfo::Usize || b.kind == TypeInfo::Default){
            return true;
        }
        else return false;
    }
    if(b.kind == TypeInfo::Default){
        if(a.kind == TypeInfo::I32 || a.kind == TypeInfo::U32 || a.kind == TypeInfo::Isize || a.kind == TypeInfo::Usize || a.kind == TypeInfo::Default){
            return true;
        }
        else return false;
    }
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
    if(a.kind == TypeInfo::Vec || a.kind == TypeInfo::Box){
        return IsTypeEqual(*a.element,*b.element);
    }
    return true;
}
// 可以作为左值的expression：路径，解引用，struct字段，index，临时物化（Call的返回值）
// 不能穿过可变引用
bool SemanticCheck::CanWrite(ASTNode* node){
    return AnalyzePlace(node).can_write;
}
bool SemanticCheck::IsPlaceExpr(ASTNode* node){
    // 解开AST里的多层封装，与AnalyzePlace一致
    while(node != nullptr){
        if(node->kind == BinaryExpr){
            auto binary = static_cast<BinaryExprNode*>(node);
            if(binary->operands.size() != 1) break;
            node = binary->operands[0];
            continue;
        }
        if(node->kind == CastExpr){
            auto cast = static_cast<CastExprNode*>(node);
            if(!cast->types.empty()) break;
            node = cast->expr;
            continue;
        }
        if(node->kind == UnaryExpr){
            auto unary = static_cast<UnaryExprNode*>(node);
            if(!unary->op.empty()) break;
            node = unary->expr;
            continue;
        }
        if(node->kind == AssignExpr){
            auto assign = static_cast<AssignExprNode*>(node);
            if(assign->right != nullptr) break;
            node = assign->left;
            continue;
        }
        break;
    }
    if(node == nullptr) return false;
    if(node->kind == PathExpr || node->kind == FieldExpr || node->kind == IndexExpr) return true;
    if(node->kind == UnaryExpr){
        return static_cast<UnaryExprNode*>(node)->op == "*";
    }
    return false;
}
// 解引用
SemanticCheck::PlaceInfo SemanticCheck::DereferencePlace(const PlaceInfo& base){
    PlaceInfo result;
    if(base.type.element == nullptr) return result;
    if(base.type.kind == TypeInfo::Ref){
        result.type = *base.type.element;
        if(base.type.is_mut && !base.has_pass_shared_ref){
            // 是可变引用
            result.can_write = true;
            result.can_mutate_contents = true;
        }
        else{
            // 穿过了共享引用
            result.has_pass_shared_ref = true;
        }
    }
    else if(base.type.kind == TypeInfo::Box){
        result.type = *base.type.element;
        result.can_write = base.can_mutate_contents;
        result.can_mutate_contents = base.can_mutate_contents;
        result.has_pass_shared_ref = base.has_pass_shared_ref;
    }
    return result;
}
SemanticCheck::PlaceInfo SemanticCheck::AnalyzePlace(ASTNode* node){
    PlaceInfo result;
    // 解开AST里的多层封装
    while(node != nullptr){
        if(node->kind == BinaryExpr){
            auto binary = static_cast<BinaryExprNode*>(node);
            if(binary->operands.empty()) return result;
            if(binary->operands.size() > 1) break;
            node = binary->operands[0];
            continue;
        }
        if(node->kind == CastExpr){
            auto cast = static_cast<CastExprNode*>(node);
            if(!cast->types.empty()) break;
            node = cast->expr;
            continue;
        }
        if(node->kind == UnaryExpr){
            auto unary = static_cast<UnaryExprNode*>(node);
            if(!unary->op.empty()) break;
            node = unary->expr;
            continue;
        }
        if(node->kind == AssignExpr){
            auto assign = static_cast<AssignExprNode*>(node);
            if(assign->right != nullptr) break;
            node = assign->left;
            continue;
        }
        break;
    }
    if(node == nullptr) return result;
    if(node->kind == PathExpr){
        // 最底层
        auto path = static_cast<PathExprNode*>(node);
        if(path->segments.size() != 1) return result;
        const std::string& name = path->segments[0].first;
        Symbol* symbol = nullptr;
        for(auto it = scopes.rbegin(); it != scopes.rend(); ++it){
            auto found = it->find(name);
            if(found != it->end()){
                symbol = found->second;
                break;
            }
        }
        if(symbol == nullptr){
            auto found = top_params.find(name);
            if(found != top_params.end()) symbol = found->second;
        }
        if(symbol == nullptr || symbol->type == nullptr) return result; // 不存在
        result.type = *symbol->type;
        result.can_write = symbol->mut && !symbol->is_const;
        result.can_mutate_contents = result.can_write;
        return result;
    }
    else if(node->kind == CallExpr){
        // struct array vec box 临时值可以物化作为place
        result.type = VisitAndGetType(node);
        if(result.type.kind == TypeInfo::Struct || result.type.kind == TypeInfo::Array ||
           result.type.kind == TypeInfo::Vec || result.type.kind == TypeInfo::Box){
            result.can_mutate_contents = true;
        }
        return result;
    }
    else if(node->kind == UnaryExpr){
        auto unary = static_cast<UnaryExprNode*>(node);
        if(unary->op == "*"){
            return DereferencePlace(AnalyzePlace(unary->expr));
        }
    }
    else if(node->kind == FieldExpr){
        auto field = static_cast<FieldExprNode*>(node);
        PlaceInfo base = AnalyzePlace(field->receiver);
        while(base.type.kind == TypeInfo::Ref || base.type.kind == TypeInfo::Box){
            base = DereferencePlace(base);
        }
        if(base.type.kind != TypeInfo::Struct) return result;
        auto struct_it = structs_table.find(base.type.name);
        if(struct_it == structs_table.end() || struct_it->second == nullptr){
            return result;
        } // 不存在这个结构体
        auto field_it = struct_it->second->fields.find(field->name); 
        if(field_it == struct_it->second->fields.end() || field_it->second == nullptr){
            return result;
        } // 不存在这个field
        result.type = *field_it->second;
        result.can_write = base.can_mutate_contents;
        result.can_mutate_contents = base.can_mutate_contents;
        result.has_pass_shared_ref = base.has_pass_shared_ref;
        return result;
    }
    else if(node->kind == IndexExpr){
        auto index = static_cast<IndexExprNode*>(node);
        PlaceInfo base = AnalyzePlace(index->base);
        while(base.type.kind == TypeInfo::Ref || base.type.kind == TypeInfo::Box){
            base = DereferencePlace(base);
        }
        if(base.type.kind != TypeInfo::Array && base.type.kind != TypeInfo::Vec) return result;
        if(base.type.element == nullptr) return result;
        if(base.type.kind == TypeInfo::Vec){
            // 穿过不可变的Vec会插入共享引用
            if(!base.can_mutate_contents){
                result.has_pass_shared_ref = true;
            }
            else{
                result.has_pass_shared_ref = base.has_pass_shared_ref;
            }
        }
        else{
            result.has_pass_shared_ref = base.has_pass_shared_ref;
        }
        result.type = *base.type.element;
        result.can_write = base.can_mutate_contents;
        result.can_mutate_contents = base.can_mutate_contents;
        return result;
    }
    else if(node->kind == ExprStmt){
        auto statement = static_cast<ExprStmtNode*>(node);
        if(statement->expr == nullptr) return result;
        result.type = VisitAndGetType(statement->expr);
    }
    else if(node->kind == BlockExpr){
        // 块表达式作为值会物化成临时值，获得新place的可变性
        result.type = VisitAndGetType(node);
        if(result.type.kind == TypeInfo::Struct || result.type.kind == TypeInfo::Array ||
           result.type.kind == TypeInfo::Vec || result.type.kind == TypeInfo::Box){
            result.can_mutate_contents = true;
        }
        return result;
    }
    // 如果上述都不是 就不是左值
    return result;
}
bool SemanticCheck::CheckDerivedTrait(std::set<Derived> &derived, TypeInfo* &field){
    if(field->kind == TypeInfo::Box || field->kind == TypeInfo::Vec){
        if(derived.find(Copy) != derived.end()){
            return false; // Box 不支持 Copy，否则可能double free
        }
        if(derived.find(Clone) != derived.end()){
            return CheckDerivedTrait(derived,field->element);
        }
    }
    if(field->kind == TypeInfo::Ref && field->is_mut){
        if(derived.find(Clone) != derived.end()){
            return false; // &mut T 不支持 Clone，可变引用最多一个
        }
    }
    if(field->kind == TypeInfo::Array){
        return CheckDerivedTrait(derived,field->element);
    }
    if(field->kind == TypeInfo::Struct){
        // field里不能有自己 不能形成循环 前面已经检查了
        auto other_struct = structs_table[field->name];
        for(auto trait : derived){
            if(other_struct->derived.find(trait) == other_struct->derived.end()){
                // field里的这个结构体不满足这个triat
                return false;
            }
        }
        return true;
    }
    return true;
}
bool SemanticCheck::CheckRecursiveConst(const std::vector<std::string> &begin,std::vector<std::string> &cur){
    ConstantInfo* val_ptr;
    if(cur.size() == 1){
        // 目前是普通const
        val_ptr = constants_table[cur[0]];
    }
    else{
        val_ptr = structs_table[cur[0]]->consts[cur[1]];
    }
    // 判断下一步
    if(val_ptr->path_value.size() == 0){
        // 到达了int或者bool
        return true;
    }
    else if(val_ptr->path_value.size() == 1){
        std::string const_name = val_ptr->path_value[0];
        if(constants_table.find(const_name) == constants_table.end()){
            // 不存在这个路径
            return false;
        }
        if(begin.size() == 1 && begin[0] == const_name){
            // 循环
            return false;
        }
        return CheckRecursiveConst(begin,val_ptr->path_value);
    }
    else{
        std::string struct_name = val_ptr->path_value[0];
        std::string const_name = val_ptr->path_value[1];
        if(struct_name == "Self" && cur.size() == 1){
            // 普通变量不能有Self路径
            if(cur.size() == 1){
                return false;
            }
            else{
                // 把Self替换成现在的结构体名
                struct_name = cur[0];
            }
        }

        if(structs_table.find(struct_name) == structs_table.end()){
            return false; // 不存在的结构体
        }
        if(structs_table[struct_name]->consts.find(const_name) == structs_table[struct_name]->consts.end()){
            return false; // 不存在的结构体内const
        }
        if(begin.size() == 2 && begin[0] == struct_name && begin[1] == const_name){
            // 循环
            return false;
        }
        std::vector<std::string> nex;
        nex.push_back(struct_name);
        nex.push_back(const_name);
        return CheckRecursiveConst(begin,nex);
    }
}
bool SemanticCheck::CheckRecursiveField(std::set<std::string>& history,const std::string& cur_typename){
    if(structs_table.find(cur_typename) == structs_table.end()){
        return false; // 不存在的类型
    }
    if(history.find(cur_typename) != history.end()) return false; // 依赖关系构成环
    history.insert(cur_typename);
    auto type_fields = structs_table[cur_typename]->fields;
    for(auto field : type_fields){
        if(field.second->kind == TypeInfo::Struct){
            if(!CheckRecursiveField(history,field.second->name)){
                return false;
            }
        }
        else if(field.second->kind == TypeInfo::Array){
            TypeInfo inner = *field.second->element;
            while(inner.kind == TypeInfo::Array){
                inner = *inner.element;
            }
            if(inner.kind == TypeInfo::Struct){
                if(!CheckRecursiveField(history,inner.name)){
                    return false;
                }
            }
        }
    }
    return true;
}
bool SemanticCheck::CanCopy(TypeInfo type){
    if(type.kind == TypeInfo::Struct){
        auto struct_info = structs_table[type.name];
        if(struct_info->derived.find(Copy) == struct_info->derived.end()){
            return false;
        }
        return true;
    }
    else if(type.kind == TypeInfo::Array){
        return CanCopy(*type.element);
    }
    else if(type.kind == TypeInfo::Ref){
        if(type.is_mut) return false;
        else return true;
    }
    else if(type.kind == TypeInfo::Vec || type.kind == TypeInfo::Box){
        return false;
    }
    return true;
}
bool SemanticCheck::CanClone(TypeInfo type){
    if(type.kind == TypeInfo::Struct){
        auto struct_info = structs_table[type.name];
        if(struct_info->derived.find(Clone) != struct_info->derived.end()){
            return true;
        }
        else return false;
    }
    if(type.kind == TypeInfo::Vec || type.kind == TypeInfo::Box){
        return CanClone(*type.element);
    }
    if(type.kind == TypeInfo::Ref && type.is_mut){
        return false;
    }
    return true;
}
bool SemanticCheck::CanPartialEq(TypeInfo type){
    while(type.kind == TypeInfo::Ref || type.kind == TypeInfo::Vec || type.kind == TypeInfo::Box){
        type = *type.element;
    }
    if(type.kind == TypeInfo::Struct){
        if(structs_table[type.name]->derived.find(PartialEq) != structs_table[type.name]->derived.end()){
            return true;
        }
        return false;
    }
    else{
        return true;
    }
}
bool SemanticCheck::CanTypeMut(TypeInfo type){
    if(type.kind != TypeInfo::Ref && type.kind != TypeInfo::Box) return false;
    while(type.kind == TypeInfo::Box){
        type = *type.element;
    }
    if(type.kind != TypeInfo::Ref) return false;
    if(type.kind == TypeInfo::Ref && type.is_mut) return true;
    else return false;
}
bool SemanticCheck::CanCoerce(TypeInfo start,TypeInfo target){
    if(start.kind == TypeInfo::Never) return true; // Never type可以强制转换为任意类型
    if(start.kind == TypeInfo::Ref && target.kind == TypeInfo::Ref){
        if(IsTypeEqual(*start.element,*target.element)){
            if(!target.is_mut) return true; // &mut T 可以强制转换为 & T
            else{
                if(!start.is_mut) return false;
                else return true;
            }
        }
        else{
            TypeInfo cur = *start.element;
            if(target.is_mut){
                // 目标函数可变
                // A mutable target requires an outer &mut 
                // and no shared reference along the path.
                if(!start.is_mut) return false;
                TypeInfo cur = *start.element;
                while(cur.kind == TypeInfo::Ref || cur.kind == TypeInfo::Box){
                    if(IsTypeEqual(cur,*target.element)) return true;
                    if(cur.kind == TypeInfo::Ref && !cur.is_mut){
                        // 穿越可变引用
                        return false;
                    }
                    cur = *cur.element;
                }
                if(IsTypeEqual(cur,*target.element)) return true;
                else return false;
            }
            else{
                // 目标函数不可变
                TypeInfo cur = *start.element;
                while(cur.kind == TypeInfo::Ref || cur.kind == TypeInfo::Box){
                    if(IsTypeEqual(cur,*target.element)) return true;
                    cur = *cur.element;
                }
                if(IsTypeEqual(cur,*target.element)) return true;
                else return false;
            }
        }
    }
    return false;
}