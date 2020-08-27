#include <set>
#include <iostream>
#include <limits>
#include <cstdlib>
#include "application.h"

//const int CHAR_BIT = 25;

bool application::run()
{
    std::set<int> local_set;

    for(int i=0; i<__SCHAR_MAX__/__CHAR_BIT__; ++i)
    {
        local_set.insert(std::rand() % (__SCHAR_MAX__/__CHAR_BIT__*2));
    }

    for(auto& i : local_set)
    {
        std::cout<<i<<"\n";
    }
}