#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    uint64_t n1 = 0;
    uint64_t n2 = UINT64_MAX;

    
	uint64_t m1{ 0x123456789abcdef0 };
	uint64_t m2{ 0x23456789abcdef01 };

    std::cout<<std::hex<<n1<<"\n";
    std::cout/*<<std::hex*/<<n2<<"\n";
    std::cout<<RAND_MAX<<"\n";

    std::stringstream ss;
    ss << std::hex << n1 << n2;
    std::cout << ss.str() << "\n";

    std::stringstream s2;
    s2 << std::hex << m1 << m2;
    std::cout<<s2.str()<<"\n";
    
    std::stringstream s3;
    s3 << std::hex << m2 << m1;
    std::cout<<s3.str()<<"\n";
}