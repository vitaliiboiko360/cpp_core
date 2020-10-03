#include <iostream>
#include <cstdarg>
#include <climits>

const int ID_SIZE = 3;

class A 
{
public:
    A()
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" A()\n";
    }

    ~A()
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" ~A()\n";
    }

    A(const A& a)
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" A(const A& a)\n";
    }

    A& operator=(const A& a)
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" A operator=(const A& a)\n";
        return *this;
    }

    A(A&& a)
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" A(A&& a)\n";
    }

    A& operator=(A&& a)
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" A& operator=(A&& a)\n";
        return *this;
    }

private:
    char id[ID_SIZE];
};

void func(A a)
{
    (void)a;
}

A func_2(A a)
{
    (void)a;
    return a;
}

class B
{
public:
    B(const A& a)
    : a(std::move(a))
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" B(const A& a)\n";
    }

    B(A&& aa)
    : a(aa)
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" B(A&& a)\n";
    }

    ~B()
    {
        std::cout<<std::hex<<(reinterpret_cast<intptr_t >(this) & 0xffff)<<" ~B()\n";
    }

private:
    A a;
};

int main(int argc, char* argv[])
{

    A a;
    A& ref_a = a;
    B b(ref_a);

    //A a2 = std::move(a);

    return 0;
}