#include "funcs.h"

#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>

namespace 
{
    void print_thread_info()
    {
        std::cout<<"#"<<std::this_thread::get_id()<<"\n";
    }
}

int save_file(const std::string& file_name)
{
    print_thread_info();
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

    int max_value = 0;
    for(auto& i : numbers)
    {
        if (i > max_value)
            max_value = i;
    }
    print_thread_info();
    std::cout<<"max value in file: "<<file_name<<" is "<<max_value<<"\n";
}