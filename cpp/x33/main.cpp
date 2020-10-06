#include <iostream>

static auto v = 7;

int main()
{


    int array[] = {1,2,3};

    auto i = array[2];
    auto* p = array;

    std::cout<<i<<"\n";
    std::cout<<*p<<"\n";
    std::cout<<v<<"\n";

}