#include <iostream>
#include <cstdarg>

const int ID_SIZE = 3;



class A 
{
public:
    A()
    : id()
    {
        std::cout<<"A()\n";
    }

    ~A()
    {
        std::cout<<"~A()\n";
    }

    A(const A& a)
    {
        std::cout<<"A(const A& a)\n";
    }

    A& operator=(const A& a)
    {
        std::cout<<"A operator=(const A& a)\n";
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
    A* p_a1;
    std::cout<<"sizeof(ptr)= "<<sizeof(p_a1)<<"\n";
    A a;
    A a1;
    a1 = a;
    func(a);
    func_2(a);

    return 0;
}