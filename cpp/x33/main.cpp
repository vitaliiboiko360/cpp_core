#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>

class A
{
public:
    A()
    : myid(++id)
    {
        print_id("A()");
    }
    ~A()
    {
        print_id("~A()");
    }
    A(const A& a)
    : myid(++id)
    {
        print_id("A(const A& a)", a.myid);
    }
    A(A&& a)
    : myid(++id)
    {
        print_id("A(A&& a)", a.myid);
    }

    A& operator= (A&& rref)
    {
        print_id("A& operator= (A&& rref)", rref.myid);
        return *this;
    }

    int myid;
    
private:
    static int id;

    void print_id(const std::string& str = "", int others_id = -1)
    {
        std::cout<<myid<<" "<<str;
        if (others_id != -1)
            std::cout<<" "<<others_id;
        std::cout<<"\n";
    }
};

int A::id = 0;

int main()
{

    std::vector<A> s;
    for(int i=0; i<5; ++i)
        s.push_back(A());

}