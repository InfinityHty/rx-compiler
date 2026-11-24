#pragma once
#include<memory>
#include<string>
#include<map>
#include <unordered_map>
class IRBaseType{
public:
    enum Type{I1,I8,I32,Ptr,Struct,Array,Void};
    Type type = Void;
    IRBaseType();
    IRBaseType(Type type_) : type(type_){}
};
class IRPrimaryType : public IRBaseType{
    // I1,I8,I32
public:
    IRPrimaryType(Type type) : IRBaseType(type){}
};
class IRPointerType : public IRBaseType{
    // ptr
public:
    std::shared_ptr<IRBaseType> element;
    IRPointerType(Type type) : IRBaseType(type){}
};
class IRStructType : public IRBaseType{
    // 结构体
public:
    std::string name;
    std::unordered_map<std::string,std::shared_ptr<IRBaseType>> fields;
    IRStructType(Type type) : IRBaseType(type){}
};
class IRArrayType : public IRBaseType {
    // array
public:
    uint32_t length;
    std::shared_ptr<IRBaseType> element;
    IRArrayType(Type type) : IRBaseType(type){}
};