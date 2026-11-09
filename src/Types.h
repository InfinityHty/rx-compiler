#include<string>
enum TypeKind{I32,U32,Usize,Isize,Bool,Box,Vec,Unit,Struct,Array,Refer,Never,Unknown};
class TypeInfo{
public:
    TypeKind kind;
    TypeInfo(TypeKind kind_){
        kind = kind_;
    }
    virtual ~TypeInfo();
};
class PrimaryType : public TypeInfo{
    // I32,U32,Usize,Isize,Bool
public:
    PrimaryType(TypeKind kind_) : TypeInfo(kind_){}
    ~PrimaryType();
};
class BoxType : public TypeInfo{
    // Box
public:
    TypeInfo* element; // 内部包裹的内容
    BoxType(TypeInfo element_) : TypeInfo(TypeKind::Box){
        element = new TypeInfo(element_);
    }
    ~BoxType(){
        delete element;
    }
};
class VecType : public TypeInfo{
    // Vec
public:
    TypeInfo* element;
    VecType(TypeInfo element_) : TypeInfo(TypeKind::Vec){
        element = new TypeInfo(element_);
    }
    ~VecType(){
        delete element;
    }
};
class UnitType : public TypeInfo{
    // Unit
public:
    UnitType() : TypeInfo(TypeKind::Unit){}
    ~UnitType();
};
class NeverType : public TypeInfo{
    // Never
public:
    NeverType() : TypeInfo(TypeKind::Never){}
    ~NeverType();
};
class UnknownType : public TypeInfo{
    // Unknown(Error)
public:
    UnknownType() : TypeInfo(TypeKind::Unknown){}
    ~UnknownType();
};
class StructType : public TypeInfo{
    // Struct
public:
    std::string name; // Struct名
    StructType(std::string name_) : TypeInfo(TypeKind::Struct){
        name = name_;
    }
    ~StructType();
};
class ArrayType : public TypeInfo{
    // Array
public:
    TypeInfo* element;
    int length = 0;
    ArrayType(TypeInfo element_,int len) : TypeInfo(TypeKind::Array){
        element = new TypeInfo(element_);
        length = len;
    }
    ~ArrayType(){
        delete element;
    }
};
class RefType : public TypeInfo{
    TypeInfo* element;
    bool is_mut = false;
    RefType(TypeInfo element_,bool is_mut_) : TypeInfo(TypeKind::Refer){
        element = new TypeInfo(element_);
        is_mut = is_mut_;
    }
    ~RefType(){
        delete element;
    }
};
