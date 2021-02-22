
#include "../utils.h"

#include <string.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>

void if_error_exit(bool error_check, std::string msg)
{
    std::cout<<msg<<" "<<strerror(errno)<<std::endl;
    std::exit(1);
}