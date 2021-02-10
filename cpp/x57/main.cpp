#include <iostream>
#include "config.h"
#include "my_library/client.h"

int main()
{
    std::cout<<"application uses library version: "<<my_library_VERSION_MAJOR<<"."<<my_library_VERSION_MINOR<<"\n";
}