#include <set>
#include <iostream>
#include <cstdlib>
#include "application.h"

const int REAZONABLE_SIZE = 256;

bool application::run()
{

    std::set<int> local_set;

    for(int i=0; i<REAZONABLE_SIZE; ++i)
    {
        local_set.insert(std::rand() % (REAZONABLE_SIZE*2));
    }

    for(auto& i : local_set)
    {
        std::cout<<i<<"\n";
    }
}