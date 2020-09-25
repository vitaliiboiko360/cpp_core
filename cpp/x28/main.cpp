#include <string>

#include "utils.h"

int main(int argc, char* argv[])
{

    cmd_arg_parser options(argc, argv);

    std::string file_name{options.file_name};
    int file_size = options.file_size;

    std::cout<<"file_name= "<<file_name<<"\n";
    std::cout<<"file_size= "<<file_size<<"\n";
}