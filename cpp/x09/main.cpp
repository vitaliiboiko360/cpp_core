#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::string line;
    boost::regex pat("^a.*");

    while(std::cin)
    {
        std::getline(std::cin, line);
        boost::smatch matches;
        if (boost::regex_match(line, matches, pat))
        {
            std::cout<<"0:\t"<<matches[0]<<std::endl;
            std::cout<<"1:\t"<<matches[1]<<std::endl;
            std::cout<<"3:\t"<<matches[2]<<std::endl;
        }
    }

    return 0;
}