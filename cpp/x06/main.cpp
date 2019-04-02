#include <map>
#include <iostream>
#include <cstdio>

class MyClass
{
public:
	MyClass();
	~MyClass();
};

int main(int argc, char** argv)
{

	std::map<int,MyClass*> map_test;
	
	std::cout<<map_test[0]<<"\n";
    std::cout<<map_test[1]<<"\n";
    std::printf("%p\n", map_test[3]);
    std::printf("%p\n", map_test[4]);

	return 0;
}