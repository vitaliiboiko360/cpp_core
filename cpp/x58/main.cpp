#include <string>
#include <iostream>
#include <iomanip>

using std::string;

class my_string
{
    std::string _str;
public:
    my_string()
    {
        print_id("my_string()");
    }
    my_string(string str)
    : _str(str)
    {
        print_id("my_string(str)");
    }
    ~my_string()
    {
        print_id("~my_string()");
    }
    my_string(const my_string& r)
    {
        print_id((void*)&r, "const my_string& r=");
        print_id("my_string(const my_string& r)");
    }
    my_string& operator=(const my_string& r)
    {
        print_id((void*)&r, "const my_string& r=");
        print_id("operator=(const my_string&)");
        return *this;
    }
    my_string(my_string&& r)
    {
        print_id((void*)&r, "my_string&& r =");
        print_id("my_string(my_string&& r)");
    }
    my_string& operator=(const my_string&& r)
    {
        print_id((void*)&r, "const my_string&& r=");
        print_id("operator=(const my_string&&)");
        return *this;
    }

private:
    void print_id(string msg = "") {std::cout<<msg<<std::hex<<(int64_t(this) & 0xffff)<<std::endl;}
    void print_id(void* ptr, string msg = "") {std::cout<<msg<<std::hex<<(int64_t(ptr) & 0xffff)<<std::endl;}
};

my_string indet(my_string arg)
{
    return arg;
}

int main()
{

    my_string s1{"Adams"};
    s1 = indet(s1);
}