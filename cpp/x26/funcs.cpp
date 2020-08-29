#include "funcs.h"

#include <cstdlib>
#include <fstream>
#include <vector>

int save_file(const std::string& file_name)
{
    std::ofstream file{file_name};

    for(int i=0; i<1000; i++)
    {
        file << std::rand() << " ";
    }
    file.close();
}

int read_file(const std::string& file_name)
{
    std::ifstream file;
    file.open(file_name);
    if (!file.is_open())
        return -1;
    
    std::vector<int> numbers;
    int number;
    while(file >> number)
    {
        numbers.push_back(number);
    }
}