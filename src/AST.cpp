#include "AST.h"
// 构建AST 各个派生类的构造函数
CrateNode::CrateNode(const ASTNodeType kind_, rx::Parser::CrateContext* ctx) : ASTNode(kind_) {
    std::vector<rx::Parser::ItemContext*> items = ctx->item();
    for(auto item : items){
        rx::Parser::FunctionDefinitionContext* is_func = item->functionDefinition();            rx::Parser::StructDefinitionContext* is_struct = item->structDefinition();
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
    
}