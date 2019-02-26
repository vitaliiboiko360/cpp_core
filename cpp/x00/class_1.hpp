#include <iostream>

class Class_1
{
public:

    Class_1();
    Class_1(const Class_1& ref);
    Class_1(Class_1& ref);
    Class_1(Class_1&& rref);
    ~Class_1();

private:
    void OutId();
    void OutId2(Class_1& ref);
    void SetNewId();
    static int m_counter;
    int m_id;
};

Class_1::Class_1()
{
    std::cout<<"Class_1()";
    SetNewId();
    OutId();
}   

Class_1::Class_1(const Class_1& ref)
{
    std::cout<<"Class_1(const Class_1& ref)";
    SetNewId();
    OutId();
}

Class_1::Class_1(Class_1& ref)
{
    std::cout<<"Class_1(Class_1& ref)";
    SetNewId();
    OutId();
}

Class_1::Class_1(Class_1&& rref)
{
    std::cout<<"Class_1(Class_1&& rref)";
    SetNewId();
    OutId2(rref);
}

Class_1::~Class_1()
{
    std::cout<<"~Class_1()";
    OutId();
}

void Class_1::OutId()
{
    std::cout<<" "<<m_id<<"\n";
}

int Class_1::m_counter = 1;

void Class_1::SetNewId()
{
    m_id = Class_1::m_counter++;
}

void Class_1::OutId2(Class_1& ref)
{
    std::cout<<" "<<m_id<<" from "<<ref.m_id<<"\n";
}