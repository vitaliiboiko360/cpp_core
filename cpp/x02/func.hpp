#include <cstdio>
#include <string>
#include <algorithm>

const int8_t nbits = 64;

std::string to_binary(int number)
{
    std::string ret;
    char c;
    do
    {
        std::sprintf(&c, "%d", number % 2);
        ret.push_back(c);
        number /= 2;
    } while (number);
    std::reverse(ret.begin(), ret.end());
    return ret;
}
