#include <string>
#include <iostream>
#include <cstdio>

using std::string;

void function_1(string str1, string str2)
{
    auto itA = str1.begin();
    auto itB = str2.begin();
    while(itA != str1.end())
    {
        std::printf("%c\t%c\n", static_cast<char>(*itA), static_cast<char>(*itB));
        itA++;
        itB++;
    }
}