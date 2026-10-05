#include "Semantic.h"
#include "AST.h"
bool SemanticCheck::hasSemanticError(CrateNode* node){
    // 第一遍扫描所有items 检查是否有重名
    for(auto item : node->items){
        if(item->kind == FnItem){
            FnItemNode* child_node = static_cast<FnItemNode*>(item);
            FunctionInfo* func = new FunctionInfo;
            for(auto param : child_node->parameters){
                func->params.push_back(GetTypeInfo(param));
            }
            if(child_node->returnType != nullptr){
                func->return_type = GetTypeInfo(child_node->returnType);
            }
            // 检查命名相关错误
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
                if(struc->fields.find(field_.first) != struc->fields.end()){
                    return true; // struct里有重复field名
                }
                else{
                    struc->fields[field_.first] = field_.second;
                }
            }
            if(structs_table.find(child_node->name) != structs_table.end()){
                return true; // 重复结构体名
            }
            else{
                structs_table[child_node->name] = struc;
            }
        }
        else if(item->kind == ConstItem){
            auto child_node = static_cast<ConstItemNode*>(item);
            ConstantInfo* const_ = new ConstantInfo;
            const_->type = GetTypeInfo(child_node->type);
            const_->value = child_node->value; // 先在里面存一下ASTNode*
            if(constants_table.find(child_node->name) != constants_table.end()){
                return true; // 重复常量名
            }
            else{
                constants_table[child_node->name] = const_;
            }
        }
        else if(item->kind == ImplItem){
            auto child_node = static_cast<ImplItemNode*>(item);
            std::string target_type_name = GetTypeInfo(child_node->type)->name;
            if(structs_table.find(target_type_name) == structs_table.end()){
                return true; // 不存在这个结构体
            }
            for(auto associated : child_node->associatedItems){
                StructInfo* struct_info = structs_table[target_type_name];
                if(associated->kind == FnItem){
                    auto func_ptr = static_cast<FnItemNode*>(associated);
                    if(struct_info->methods.find(func_ptr->name) != struct_info->methods.end()){
                        return true; // 一个struct中impl同名函数
                    }
                    else{
                        // 加入methods中
                        FunctionInfo* func_in_struct = new FunctionInfo;
                        for(auto param : func_ptr->parameters){
                            func_in_struct->params.push_back(GetTypeInfo(param));
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
    // 第二遍扫描整个AST
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
        default:
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

}
bool SemanticCheck::IsTypeEqual(const TypeInfo& a, const TypeInfo& b){

}