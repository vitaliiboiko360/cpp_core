#include <thread>

#include "funcs.h"

int main(int argc, char* argv[])
{


    const int num_threads = 3;
    std::thread t[num_threads];

    t[0] = std::thread(save_file, "file_1");
    t[1] = std::thread(read_file, "file_1");

    t[0].join();
    t[1].join();
}