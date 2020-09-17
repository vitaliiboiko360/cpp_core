#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <cstdlib>
#include <unistd.h>

struct GuardString
{
    std::mutex mtx;
    std::string str;
};

void fill_string(int limit, GuardString& str)
{
    if (limit <= 0)
        return;

    std::lock_guard<std::mutex> lg(str.mtx);
    int acc = 0;
    for(int i=0; i<limit; ++i)
    {
        str.str.push_back(static_cast<char>((std::rand() % 25) + 97));
        for(int i=0; i<100; ++i)
        {
            if (i % 2 == 0)
            {
                acc += i;
            }
        }
        acc = 0;
    }
    std::cout<<"END OF FILL STRING FUNCTION\n";
}

void thread_function(GuardString& str)
{
    std::lock_guard<std::mutex> lg(str.mtx);
    std::cout<<"thread recieved str:\n"<<str.str<<"\n";
    std::cout<<"END OF THREAD FUNCTION\n";
}

int main(int argc, char* argv[])
{
    int number = 5000;
    std::string str;

    GuardString gd_str;
    
    for (int i=0; i<5; i++)
    {
        std::cout<<"\n\n\n\nITERATION NUMBER "<<i<<"\n\n\n\n";
        sleep(1);
        std::thread thread_1(fill_string, number, std::ref(gd_str));
        std::thread thread_2(thread_function, std::ref(gd_str)); 
        thread_1.join();
        thread_2.join();
    }

    return 0;
}