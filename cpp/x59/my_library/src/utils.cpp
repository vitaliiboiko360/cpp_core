
#include "../utils.h"

#include <iostream>
#include <cstdlib>

void if_error_exit(bool error_check, std::string msg)
{
    std::cout<<msg<<std::endl;
    std::exit(1);
}