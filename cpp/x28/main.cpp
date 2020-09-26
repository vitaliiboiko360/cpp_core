#include <string>
#include <fstream>
#include <cstdlib>

#include "utils.h"

int main(int argc, char* argv[])
{

    cmd_arg_parser options(argc, argv);

    std::string file_name{options.file_name};
    int file_size = options.file_size;

    std::ofstream file{options.file_name};

    int i{0};
    do
    {
        file<<std::rand();
    } while (i++ < options.file_size/4);
}