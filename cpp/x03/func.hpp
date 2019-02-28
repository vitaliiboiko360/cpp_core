#include <iostream>
#include <memory>

class MyClass
{
    int m_number;
public:
    MyClass();
    MyClass(int number);
    ~MyClass();
};

MyClass::MyClass()
{
    std::cout<<"MyClass()\n";
}

MyClass::MyClass(int number)
: m_number(number)
{
    std::cout<<"MyClass( number= "<<number<<" )\n";
}

MyClass::~MyClass()
{
    std::cout<<"~MyClass()\n";
}

std::unique_ptr<MyClass> CreateMyClass(int n)
{
    if(n > 0)
        return std::make_unique<MyClass>(n);
    
    return {};
}