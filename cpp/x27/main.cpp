#include <iostream>
#include <thread>

void busy_work()
{
    int acc;
    for(int i=0; i<__INT16_MAX__; i++)
    {   
        if (acc % 2 ==0)
            acc += i;
    }
}

void thread_function(int arg)
{
    std::cout<<"this thread would count to number \"arg\"= "<<arg<<"\n";
    for(int i=0; i<arg; i++)
    {
        std::cout<<"i= "<<i<<"\n";
        busy_work();
    }
}

int main(int argc, char* argv[])
{

    int number = 50;

    std::thread thread_1(thread_function, number);   
    for(int i=0; i<number; i++)
    {
        std::cout<<"main i="<<i<<"\n";
        busy_work();
    }
    thread_1.detach();
    if(thread_1.joinable())
        thread_1.join();

    return 0;
}