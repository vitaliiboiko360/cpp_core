#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <thread>
#include <string.h>
#include "config.h"
#include "my_library/client.h"
#include "my_library/server.h"

const uint16_t port_number = 8888;
const char* localhost = "127.0.0.1";

int client_main();
int server_main();

int main(int argc, char* argv[])
{
    auto print_usage = [](){        
        std::cout<<"usage: ./app -s | -c\n";
        return 1;
    };
    if(argc < 2)
    {
        return print_usage();
    }

    if(0 == strcmp(argv[1],"-s"))
    {
        return server_main();
    }
    else if(0 == strcmp(argv[1],"-c"))
    {
        return client_main();
    }
    else
    {
        return print_usage();
    }
    

    return 0;
}

int client_main()
{
    my_client cli0(port_number);
    my_client cli1(port_number);
    my_client cli2(port_number);
    my_client cli3(port_number);

    std::vector<std::thread> threads;
    threads.emplace_back(std::thread([&cli0]{cli0.run();}));
    threads.emplace_back(std::thread([&cli1]{cli1.run();}));
    threads.emplace_back(std::thread([&cli2]{cli2.run();}));
    threads.emplace_back(std::thread([&cli3]{cli3.run();}));

    for_each(threads.begin(), threads.end(), [](std::thread& t){t.join();});

    return 0;
}

int server_main()
{
    my_server srv(localhost, port_number);
    std::vector<std::thread> threads;

    threads.emplace_back(std::thread([&srv]{srv.run();}));

    for_each(threads.begin(), threads.end(), [](std::thread& t){t.join();});
    return 0;
}