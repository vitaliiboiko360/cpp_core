#include "my_library/client.h"
#include "my_library/server.h"

#include <iostream>

const uint16_t port = 30000;

int main()
{
    std::cout<<"srv\n";
    my_server srv(port);
    std::cout<<"cli\n";
    my_client cli;
}