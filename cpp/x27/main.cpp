#include <iostream>
#include <thread>
#include <string>
#include <cstdlib>

void fill_string(int limit, std::string& str)
{
    if (limit <= 0)
        return;
    for(int i=0; i<limit; ++i)
    {
        str.push_back(static_cast<char>((std::rand() % 25) + 87));
    }
}

void thread_function(std::string& str)
{
    std::cout<<"thread recieved str:\n"<<str<<"\n";
}

int main(int argc, char* argv[])
{

    int number = 50;
    std::string str;
       
    std::thread thread_1(fill_string, number, std::ref(str));
    std::thread thread_2(thread_function, str); 
    thread_1.join();
    thread_2.join();


    return 0;
}