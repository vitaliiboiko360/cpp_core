#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

const int DEFAULT_FILE_SIZE = 1000;

struct cmd_arg_parser
{
    int argc;
    char** argv;
    std::string file_name;
    int file_size;

    cmd_arg_parser(int argc, char* argv[])
    : argc(argc)
    , argv(argv)
    {
        init();
    }

    void init()
    {
        for(int i=0; i<argc; i++)
        {
            params.push_back({ argv[i] });
        }

        int i = 0;
        for(auto p : params)
        {
            std::cout<<"arg"<<i++<<" is "<<p<<"\n";
        }

        if (argc > 1)
            file_name = {argv[1]};
        else
            file_name = "file.dat";
        
        if (argc > 2)
            file_size = std::atoi(argv[2]);

        if (file_size == 0)
            file_size = DEFAULT_FILE_SIZE;

    }

    std::vector<std::string> params;
};