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
                    if(IsBuiltIn(fn_param_node->name)) return true; // 关键字
                    Symbol* param_symbol = new Symbol;
                    param_symbol->type = GetTypeInfo(fn_param_node->type);
                    if(param_symbol->type->kind == TypeInfo::Unknown){
                        return true; // 无法解析
                    }
                    if(fn_param_node->mut){
                        param_symbol->mut = true;
                    }
                    else param_symbol->mut = false;
                    func->params.push_back(param_symbol);
                }
                else if(param->kind == FnSelfParam){
                    return true; // 全局函数不可以用self作为参数
                }
            }
            if(child_node->returnType != nullptr){
                func->return_type = GetTypeInfo(child_node->returnType);
                if(func->return_type->kind == TypeInfo::Unknown) return true; // 未知类型
            }
            if(functions_table.find(child_node->name) != functions_table.end()){
                return true; // 重复函数名
            }
            else if(IsBuiltIn(child_node->name)){
                return true; // 使用保留关键字作为名字
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
                else if(IsBuiltIn(field_.first)){
                    return true; // field变量使用保留关键字做名字
                }
                else{
                    struc->fields[field_.first] = field_.second;
                }
            }
            if(structs_table.find(child_node->name) != structs_table.end()){
                return true; // 重复结构体名
            }
            else if(IsBuiltIn(child_node->name)){
                return true; // 保留关键字
            }
            else{
                structs_table[child_node->name] = struc;
            }
        }
        else if(item->kind == ConstItem){
            auto child_node = static_cast<ConstItemNode*>(item);
            ConstantInfo* const_ = new ConstantInfo;
            const_->type = GetTypeInfo(child_node->type);
            if(const_->type->kind == TypeInfo::Unknown) return true; // 未知类型
            const_->value = child_node->value; // 先在里面存一下ASTNode*
            if(constants_table.find(child_node->name) != constants_table.end()){
                return true; // 重复常量名
            }
            else if(IsBuiltIn(child_node->name)){
                return true; // 保留关键字
            }
            else{
                constants_table[child_node->name] = const_;
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
                    else if(IsBuiltIn(func_ptr->name)){
                        return true; // 保留关键字
                    }
                    else{
                        // 加入methods中
                        FunctionInfo* func_in_struct = new FunctionInfo;
                        for(auto param : func_ptr->parameters){
                            if(param->kind == FnParam){
                                auto fn_param_node = static_cast<FnParamNode*>(param);
                                if(IsBuiltIn(fn_param_node->name)){
                                    return true; // 关键字
                                }
                                Symbol* param_symbol = new Symbol;
                                param_symbol->type = GetTypeInfo(fn_param_node->type);
                                if(fn_param_node->mut){
                                    param_symbol->mut = true;
                                }
                                else param_symbol->mut = false;
                                func_in_struct->params.push_back(param_symbol);
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
                                func_in_struct->params.push_back(param_symbol);
                            }
                        }
                        if(func_ptr->returnType != nullptr){
                            func_in_struct->return_type = GetTypeInfo(func_ptr->returnType);
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
                    else if(IsBuiltIn(const_ptr->name)){
                        return true; // 关键字
                    }
                    else{
                        // 加入consts中
                        ConstantInfo* const_in_struct = new ConstantInfo;
                        const_in_struct->type = GetTypeInfo(const_ptr->type);
                        const_in_struct->value = const_ptr->value;
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
        }
        if(constants_table.find(it->first) != constants_table.end()){
            return true; // 函数和常量重名
        }
        // 检查函数里每个Type是否存在

    }
    // 3.扫描整个AST

    // 全部检查完没有问题
    return false;
}
// dispatch
void SemanticCheck::Visit(ASTNode* node){
    switch(node->kind){
        case Crate: VisitCrate(static_cast<CrateNode*>(node));return;
        // items
        case FnItem: VisitFnItem(static_cast<FnItemNode*>(node));return;
        case StructItem: VisitStructItem(static_cast<StructItemNode*>(node));return;            case ConstItem: VisitConstItem(static_cast<ConstItemNode*>(node));return;
        case ImplItem: VisitImplItem(static_cast<ImplItemNode*>(node));return;
        // statements
        case LetStmt: Visit(static_cast<LetStmtNode*>(node));return;            case ExprStmt: Visit(static_cast<ExprStmtNode*>(node));return;
        // expressions
        case IntLit: Visit(static_cast<IntLitNode*>(node));return;
        case BoolLit: Visit(static_cast<BoolLitNode*>(node));return;
        case PathExpr: Visit(static_cast<PathExprNode*>(node));return;
        case StructExpr: Visit(static_cast<StructExprNode*>(node));return;
        case ArrayExpr: Visit(static_cast<ArrayExprNode*>(node));return;
        case ArrayRepeat: Visit(static_cast<ArrayRepeatNode*>(node));return;
        case UnaryExpr: Visit(static_cast<UnaryExprNode*>(node));return;
        case BinaryExpr: Visit(static_cast<BinaryExprNode*>(node));return;
        case AssignExpr: Visit(static_cast<AssignExprNode*>(node));return;
        case CastExpr: Visit(static_cast<CastExprNode*>(node));return;
        case CallExpr: Visit(static_cast<CallExprNode*>(node));return;
        case MethodCallExpr: Visit(static_cast<MethodCallExprNode*>(node));return;
        case FieldExpr: Visit(static_cast<FieldExprNode*>(node));return;
        case IndexExpr: Visit(static_cast<IndexExprNode*>(node));return;
        case BlockExpr: Visit(static_cast<BlockExprNode*>(node));return;
        case IfExpr: Visit(static_cast<IfExprNode*>(node));return;
        case LoopExpr: Visit(static_cast<LoopExprNode*>(node));return;
        case WhileExpr: Visit(static_cast<WhileExprNode*>(node));return;
        case BreakExpr: Visit(static_cast<BreakExprNode*>(node));return;
        case ContinueExpr: Visit(static_cast<ContinueExprNode*>(node));return;
        case ReturnExpr: Visit(static_cast<ReturnExprNode*>(node));return;
        // types
        case UnitType:
        case PathType:
        case RefType:
        case ArrayType:
        // others
        case FnSelfParam:
        case FnParam:
        case StructField:
        default: return;
    }
}
void SemanticCheck::VisitCrate(CrateNode* node){
    for(auto item : node->items){
        Visit(item);
    }
}
void SemanticCheck::VisitFnItem(FnItemNode* node){

}
void SemanticCheck::VisitStructItem(StructItemNode* node){

}
void SemanticCheck::VisitConstItem(ConstItemNode* node){

}
void SemanticCheck::VisitImplItem(ImplItemNode* node){
    
}
// Tools
bool SemanticCheck::IsBuiltIn(std::string name_){
    for(auto name : builtin_names){
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
        // 长度是一个表达式怎么办？
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
            // Vec and Box 
            // TODO
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

}