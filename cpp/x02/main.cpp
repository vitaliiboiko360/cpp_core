#include <iostream>
#include "func.hpp"


int main(int argc, char** argv)
{


    for(int i=0; i<10; ++i)
    {
        std::cout<<"i="<<i<<"\t"<<to_binary(i)<<"\n";
    }

    return 0;
}