#include <stdlib.h>
#include <string>
#include <cstdlib>
int main(int argc, char* argv[])
{   
    const int FILE_NUMBER = 100;
    std::string path = "../x28/a.out";
    for (int i=0; i<FILE_NUMBER; ++i)
    {   
        std::string command{path};
        command += " ";
        command += "file";
        command += std::to_string(i);
        command += " ";
        int file_size = (std::rand() % 1000)+1000;
        command += std::to_string(file_size);
        system(command.c_str());
    }


    return 0;
}