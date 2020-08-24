#include <set>

#include "application.h"

const int REAZONABLE_SIZE = 256;

bool application::run()
{

    std::set<int> local_set;

    for(int i=0; i<REAZONABLE_SIZE; ++i)
    {
        local_set[std::rand()]
    }
}