#include <iostream>
#include <memory>
#include <thread>

class A
{
public:
    A()
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
        std::cout<<"A& operator=(const A& a)\n";
        return *this;
    }
    A(A&& r)
    {
        std::cout<<"A(A&& r)\n";
    }
    A& operator=(A&& r)
    {
        std::cout<<"A&& operator=(A&& r)\n";
        return *this;
    }

    const A* id() const
    {
        return this;
    }
};

using namespace std;


int main()
{
    auto p = make_unique<A>();
    cout<<"before move= "<<p->id()<<"\n";

    thread t1{[mp = move(p)](){
        std::cout<<"moved obj= "<<mp->id()<<"\n";
        std::cout<<"thread about to end\n";
    }};

    t1.join();
}