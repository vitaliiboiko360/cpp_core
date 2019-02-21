#include <vector>

#include "class_1.hpp"



int main(int argc, char** argv)
{

    std::vector<Class_1> v1;
    v1.reserve(3);
    std::cout<<"we had reserve\n";

    for(int i=0; i<3; i++)
        v1.push_back(Class_1());

    return 0;
}