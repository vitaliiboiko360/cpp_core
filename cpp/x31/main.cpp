#include <iostream>
#include <cstdarg>
#include <climits>

const int ID_SIZE = 3;



class A 
{
public:
    A()
    : id()
    {
        std::cout<<std::hex<<this<<" A()\n";
    }

    ~A()
    {
        std::cout<<std::hex<<this<<" ~A()\n";
    }

    A(const A& a)
    {
        std::cout<<std::hex<<this<<" A(const A& a)\n";
    }

    A& operator=(const A& a)
    {
        std::cout<<std::hex<<this<<" A operator=(const A& a)\n";
        return *this;
    }

    A(A&& a)
    {
        std::cout<<std::hex<<this<<" A(A&& a)\n";
    }

    A& operator=(A&& a)
    {
        std::cout<<std::hex<<this<<" A& operator=(A&& a)\n";
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



int main(int argc, char* argv[])
{

    A a;
    A a1;

    func(a);
    func_2(a1);

    a = a1;
    A a2 = a;

    return 0;
}