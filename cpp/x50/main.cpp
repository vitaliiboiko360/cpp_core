#include <chrono>
#include <iostream>
#include <thread>
#include "http_srv.h"

int main(int argc, char* argv[])
{
    std::thread t([]{
        http_server hs;
        hs.serve();
    });
  
    for(int i=0; i<10; i++)
    {
        std::cout<<"pretend work "<<i<<"\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    t.join();

    return 0;
}