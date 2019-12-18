#include <string>

using std::string;

class PeopleCircle
{
public:
	string order(int numMales, int numFemales, int K)
	{
		string ret;
		ret.reserve(numMales + numFemales);
		ret.assign(numMales + numFemales, 'M');
		
		int i = 0;
		int f = 0;
		while(f++ < numFemales)
		{
			i = get_index(i, K, ret);		
			ret[i] = 'F';
			
			do
			{	
				i = ++i == ret.size() ? 0 : i;
			} while (ret[i] == 'F');		
		}
		
		return ret;
	}
	
	int get_index(int index, int limit, string& str)
	{
		int csteps = 0;
		while(true)
		{			
			if(str[index] == 'M')
			{
				++csteps;
				if(csteps >= limit)
					return index;
			}
			index = ++index == str.size() ? 0 : index; 
		}
	}
};