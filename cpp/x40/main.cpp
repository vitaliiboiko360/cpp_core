#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int start = 100;
    vector<int> numbers;
    numbers.reserve(100);
    cout<<"numbers.size()= "<<numbers.size()<<"\n";
    for(int i=0; i<100; ++i)
        numbers.push_back(0);
    cout<<"numbers.size()= "<<numbers.size()<<"\n";

    for_each(numbers.begin(), numbers.end(), [&start](auto& it){
        it = start++;
    });

    for_each(numbers.begin(), numbers.end(), [](auto& it){
        cout << it << ".";
    });
}