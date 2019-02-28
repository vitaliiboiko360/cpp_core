#include <memory>

#include "func.hpp"

int main()
{
    std::cout<<"start\n";
    std::unique_ptr<MyClass> p1 = CreateMyClass(0);
    p1->~MyClass();
    std::cout<<"end\n";


    return 0;
}