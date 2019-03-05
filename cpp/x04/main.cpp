#include <string>
#include <iostream>

int main()
{
    std::string s1("a2");
    std::string s2("string1");
    std::string s3("string1444");

    std::cout<<"s1.compare(s2) = " << s1.compare(s2) << "\n";
    std::cout<<"s2.compare(s1) = " << s2.compare(s1) << "\n";
    std::cout<<"s2.compare(s3) = " << s2.compare(s3) << "\n";
    std::cout<<"s3.compare(s2) = " << s3.compare(s2) << "\n";

    
    std::cout<<"s1.compare(s2) = " << s1.compare(s2) << "\n";
    std::cout<<"s2.compare(s1) = " << s2.compare(s1) << "\n";
    std::cout<<"s2 > s3 = " << (s2 > s3) << "\n";
    std::cout<<"s3 < s2 = " << (s3.compare(s2)) << "\n";

    return 0;
}