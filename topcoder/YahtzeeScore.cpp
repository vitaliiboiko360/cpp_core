// SRM 146 DIV 2 - 250

#include <vector>
#include <algorithm>
using std::vector;

class YahtzeeScore
{
public:
	int maxPoints(vector <int> toss)
	{

		vector<int> scores;
		scores.reserve(5);
		scores.assign(5,0);
		
		for(int i : toss)
			scores[i-1] += i;

		return *(std::max_element(scores.begin(), scores.end()));
	}
};