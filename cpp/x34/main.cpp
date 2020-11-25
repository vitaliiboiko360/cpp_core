#include <iostream>
#include <string>

static int file_counter = 0;

class R 
{
public:
    R(const std::string& msg = "default")
    {
        std::cout<<"ctor "<<msg<<"\n";
    }

    ~R()
    {
        std::cout<<"~dtor\n";
    }

};

int main()
{
    R* r = new R();
    delete r;
}