#include "funcs.h"

#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <sstream>

namespace 
{
    void print_out_string(std::string str)
    {
        std::cout << std::this_thread::get_id() << " " << str << std::endl;
    }
}

int save_file(const std::string& file_name)
{
    std::ofstream file{file_name};

    for(int i=0; i<1000; i++)
    {
        file << std::rand() << " ";
    }
    file.close();

    std::stringstream ss;
    ss << "saved file: "<<file_name;
    print_out_string(ss.str());
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
    
    std::stringstream ss;
    ss << "max value in file: "<<file_name<<" is "<<max_value;
    print_out_string(ss.str());
}