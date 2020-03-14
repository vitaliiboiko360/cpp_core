#include <string>
#include <iostream>

using std::string;

class CCipher
{
public:
	string decode(string cipherText, int shift)
	{
		string ret;
		int norm{ 0 };
		for(char c : cipherText)
		{
			// any (c-shift) must give only 65...90
			if ( (c - shift) <= 64 )
			{
				norm = 90 - (64-(c - shift));
				ret.push_back(char(norm));
			}
			else
				ret.push_back(c-shift);
		}
		
		/*
		char c = 'A';
		int i = 0;
		while(c != '[')
		{
			std::cout<<i<<" "<<c<<std::endl;
			c++; i++;
		}*/
		
		return ret;
	}
};
// SRM 147 DIV 2 250
