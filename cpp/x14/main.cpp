#include <iostream>

int main()
{
    std::cout<<"LONG_MAX= "<<LONG_MAX<<"\n";
    long count;
    for(long i=0; i<LONG_MAX; ++i)
    {
        count = i;
    }

    std::cout<<count<<"\n";

    return 0;
}