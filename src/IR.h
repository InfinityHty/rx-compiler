#pragma once
#include<memory> // 改用智能指针，防止内存泄漏
#include<string>
#include<vector>
#include "Semantic.h"
#include"IRType.h"
using SymbolID = uint32_t; // 赋值符号
using SlotID = uint32_t; // 内存位置
using BlockID = uint32_t; // 基本块编号
class IRBuilder{
public:
    void BuildIR(CrateNode* node,SemanticResult &result);
    void PrintIR(); // 打印IR
private:
    struct IRBasicBlock;
    class IRInstruction;
    struct IRFunction;
    struct IRFunction{
        // 每个函数内parameter，blockid和SSA assign id不重复
        std::string name;
        std::shared_ptr<IRBaseType> return_type;
        std::unordered_map<SymbolID,std::shared_ptr<IRBaseType>> params; // symbol_id到类型映射
        std::vector<std::shared_ptr<IRBasicBlock>> basic_blocks{};
    };
    std::map<std::string,std::shared_ptr<IRFunction>> functions; // 每一项都指向一个函数
    struct IRBasicBlock{
        BlockID id;
        std::vector<std::shared_ptr<IRInstruction>> instructions;
    };
    class IRValue{
    public:
        std::shared_ptr<IRBaseType> type;
        // 如果是立即数，不需要额外分配名字
        bool is_imm = false;
        uint32_t imm;
        // %v0 Symbol
        bool is_symbol = false;
        SymbolID symbol_id;
        // pointer
        bool is_ptr = false;
        SlotID slot_id;
    };
    // Instruction基类
    class IRInstruction{
    public:
        enum OpType{Add,Sub,Mul,Sdiv,And,Or,Xor,Shl,Shr,ICmp,
            Alloca,Load,Store,Br,CondBr,Ret,Call,Unknown};
        OpType op;
        IRInstruction(OpType op) : op(op){}
    };
    class ArithmeticInstruction : public IRInstruction{
    public:
        // add i32 %a, %b
        std::shared_ptr<IRBaseType> type; // 操作数类型
        IRValue left,right; // 两个操作数
        SymbolID id;
        ArithmeticInstruction(OpType op) : IRInstruction(op){}
    };
    class CompareInstruction : public IRInstruction{
    public:
        // %cmp = icmp eq i32 %a, %b
        std::shared_ptr<IRBaseType> type;
        IRValue left,right;
        SymbolID id;
        enum CompareType{Eq,Neq,Slt,Sle,Sgt,Sge,Ult,Ule,Ugt,Uge};
        CompareType cmp_type;
        CompareInstruction(OpType op) : IRInstruction(op){} 
    };
    class AllocateInstruction : public IRInstruction{
    public:
        // %p = alloca i32
        std::shared_ptr<IRBaseType> type;
        SlotID id;
        AllocateInstruction(OpType op) : IRInstruction(op){} 
    };
    class StoreInstruction : public IRInstruction{
    public:
        // store i32 42, ptr %p
        std::shared_ptr<IRBaseType> type;
        IRValue value;
        SlotID slot_id;
        StoreInstruction(OpType op) : IRInstruction(op){}
    };
    class LoadInstruction : public IRInstruction{
    public:
        // %x = load i32, ptr %p
        std::shared_ptr<IRBaseType> value_type;
        SlotID slot_id;
        SymbolID symbol_id;
        LoadInstruction(OpType op) : IRInstruction(op){}
    };
    class BranchInstruction : public IRInstruction{
    public:
        IRValue next_block;
        BranchInstruction(OpType op) : IRInstruction(op){}
    };
    class ConditionBranchInstruction : public IRInstruction{
    public:
        IRValue cond,true_branch,false_branch;
        ConditionBranchInstruction(OpType op) : IRInstruction(op){}
    };
    class ReturnInstruction : public IRInstruction{
        IRValue return_value;
        ReturnInstruction(OpType op) : IRInstruction(op){}
    };
    class CallInstruction : public IRInstruction{
    public:
        std::string name;
        std::vector<IRValue> params;
        CallInstruction(OpType op) : IRInstruction(op){}
    };
    // Tools
    std::shared_ptr<IRBaseType> GetIRType(SemanticCheck::TypeInfo type,SemanticResult& result);
    void BuildBasicBlocks(FnItemNode* node,SemanticResult &result);
    IRValue BuildInstructions(ASTNode* node,SemanticResult &result);

    std::unordered_map<SlotID,std::shared_ptr<IRBaseType>> memory; // 记录函数内被分配的内存的type
    // path
    std::vector<std::unordered_map<std::string,SlotID>> scopes; // 变量作用域维护
    std::unordered_map<std::string,SymbolID> top_params; // 函数传入参数
    int layer = 0;
    uint32_t symbol_id_counter = 0; // block编号和symbol编号共用同一套系统
    std::shared_ptr<IRBasicBlock> cur_block; // 记录当前block
    std::shared_ptr<IRFunction> cur_function; // 记录当前function名
};
