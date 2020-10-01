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

    std::cout<<INT_MAX<<"\n";
    int a = INT_MAX;
    unsigned char c;
    for(int i=0; i<32; i += 4)
    {
        c = 0;
        c = (INT_MAX<<i) | c;
        std::cout<<"(INT_MAX<<"<<i<<")="<<(INT_MAX<<i)<<"\n";
        std::cout<<c<<"\n";
    }


    return 0;
}