#include <vector>

#include "class_1.hpp"



int main(int argc, char** argv)
{

    std::vector<Class_1> v1;

    std::cout<<"we had reserve\n";

    for(int i=0; i<8; i++)
    {
        std::cout<<"b: "<<v1.capacity()<<"\n";
        v1.push_back(Class_1());
        std::cout<<"a: "<<v1.capacity()<<"\n";
    } 

    return 0;
}