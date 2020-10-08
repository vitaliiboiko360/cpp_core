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

    A& operator= (const A& other)
    {
        print_id("A& oeprator= (const A& other)", other.myid);
        if (this == &other)
            return *this;
        
        std::cout<<"this.myid= "<<myid<<" other.myid= "<<other.myid<<"\n";
        return *this;
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

bool operator<(const A& lhs, const A& rhs)
{
    return reinterpret_cast<intptr_t>(&lhs) < reinterpret_cast<intptr_t>(&rhs);
}


int main()
{

    std::set<A> s;
    for(int i=0; i<5; ++i)
        s.insert(A());

}