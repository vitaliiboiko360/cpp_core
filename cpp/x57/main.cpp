#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <thread>
#include "config.h"
#include "my_library/client.h"
#include "my_library/server.h"

const uint16_t port_number = 8888;
const char* localhost = "127.0.0.1";

int main()
{
    my_client cli(port_number);
    my_server srv(localhost, port_number);

    std::vector<std::thread> threads;

    threads.emplace_back(std::thread([&srv]{srv.run();}));
    threads.emplace_back(std::thread([&cli]{cli.run();}));

    std::this_thread::sleep_for(std::chrono::seconds(10));

    for_each(threads.begin(), threads.end(), [](std::thread& t){t.join();});

    return 0;
}