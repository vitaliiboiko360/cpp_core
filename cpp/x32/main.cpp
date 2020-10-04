#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>

void print(const std::vector<int>& vec)
{
    for(const auto& i : vec)
        std::cout<<i<<" ";
    std::cout<<"\n";
}

void square(int& elem)
{
    elem = elem * elem;
}

int mask_16_bits(int a)
{
    return a & 0xf0;
}

int remainder_16(int a)
{
    return a % 16;
}

void fill_vect_rand(std::vector<int>& v, int count = 0)
{
    for(int i=0; i<count; ++i)
        v.push_back(std::rand());
}

int main(int argc, char* argv[])
{

    std::vector<int> v;
    fill_vect_rand(v, 50);
    print(v);
    std::for_each(v.begin(), v.end(), square);
    print(v);
    std::vector<int> v2;
    v2.reserve(v.size());
    std::transform(v.begin(), v.end(), v2.begin(), mask_16_bits);
    print(v2);
    std::transform(v.begin(), v.end(), v2.begin(), remainder_16);
    print(v2);
    return 0;
}