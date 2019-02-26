#include <cstdlib>
#include <iostream>

#include "func.h"

int main(int argc, char** argv)
{
    // int32_t n1 = rand();
    // int32_t n2 = rand();
    // std::cout<<n1<<"\n";
    // std::cout<<n2<<"\n";


    std::cout<<"2 % 1 = "<<(2&1)<<"\n";

    for (int i=0; i<20; ++i)
        std::cout<<"i= "<<i<<"\t "<<to_binary(i)<<std::hex<<"\t "<<i<<"\n";
    
    for (int i=-20; i<1; ++i)
        std::cout<<"i= "<<i<<"\t "<<std::hex<<"\t "<<i<<"\n";

    return 0;
}