
#include <iostream>
#include <memory>

using std::cout;

struct Nout
{
public:
    std::ostream& operator<<(const char* str)
    {
        cout << str << "\n";
        return cout;
    }
} nout;

class Base
{

public:
    Base()
    {
        nout<<"Base()";
    }
    virtual ~Base()
    {
        nout<<"~Base()";
    }
};

class B : public Base
{

public:
    B()
    {
        nout<<"B()";
    }
    ~B()
    {
        nout<<"~B()";
    }
};

int main()
{
    std::unique_ptr<Base> p;
    p = std::make_unique<B>();
    p.reset();
    nout<<"===";
    p = std::make_unique<B>();
    p = nullptr;
    nout<<"end";
}