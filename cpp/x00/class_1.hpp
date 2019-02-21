#include <iostream>

class Class_1
{
public:

    Class_1();
    Class_1(const Class_1& ref);
    Class_1(Class_1& ref);
    Class_1(Class_1&& rref);
    ~Class_1();
};

Class_1::Class_1()
{
    std::cout<<"Class_1() "<<std::hex<<this<<"\n";
}   

Class_1::Class_1(const Class_1& ref)
{
    std::cout<<"Class_1(const Class_1& ref)\n";
}

Class_1::Class_1(Class_1& ref)
{
    std::cout<<"Class_1(Class_1& ref)\n";
}

Class_1::Class_1(Class_1&& rref)
{
    std::cout<<"Class_1(Class_1&& rref)\n";
}

Class_1::~Class_1()
{
    std::cout<<"~Class_1()\n";
}