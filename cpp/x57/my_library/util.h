#include <iostream>
#include <cstdlib>

void if_error_exit(bool error_check, const char* msg)
{
    if (error_check)
    {
        std::cerr<<msg<<"\n";
        std::exit(1);
    }
}