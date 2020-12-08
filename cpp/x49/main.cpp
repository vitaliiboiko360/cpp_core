#include <iostream>
#include <string.h>
#include "net_main.h"
void print_usage()
{
    std::cout<<"usage: ./app [-c|-s]\n";
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        print_usage();
        exit(1);
    }

    if (strcmp(argv[1], "-c") == 0)
    {
        client cli;
        return cli.run();
    }

    if (strcmp(argv[1], "-s") == 0)
    {
        server srv;
        return srv.run();
    }

    print_usage();
    exit(1);
}