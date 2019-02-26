#include <cstdio>
#include <algorithm>

#include "func.h"

std::string to_binary(int number)
{
    std::string ret;
    char c;
    do
    {  
        std::sprintf(&c,"%d", number % 2);
        ret.push_back(c);
        number /= 2;
    } while (number);

    std::reverse(ret.begin(),ret.end());

    return ret;
}