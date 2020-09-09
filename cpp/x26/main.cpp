#include <thread>

#include "funcs.h"

int main(int argc, char* argv[])
{


    const int num_threads = 3;
    std::thread t[num_threads];

    auto l = [](std::string file_name)
    {
        save_file(file_name);
        read_file(file_name);
    };

    t[0] = std::thread(l, "file_1");
    t[1] = std::thread(l, "file_2");

    t[0].join();
    t[1].join();

    t[0] = std::thread(l, "file_3");
    t[1] = std::thread(l, "file_4");

    t[0].join();
    t[1].join();
}