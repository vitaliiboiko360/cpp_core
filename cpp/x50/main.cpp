#include <iostream>
#include "http_srv.h"

int main(int argc, char* argv[])
{
    http_server hs;
    hs.serve();

    std::cout<<"end\n";

    return 0;
}