
// https://community.topcoder.com/stat?c=problem_statement&pm=1589

class RectangularGrid
{
public:
    long long countRectangles(int width, int height)
    {
    int x = 1;
    int y = 1;

    long long counter = 0;


    for(;x<=width; ++x)
    {
        for(;y<=height; ++y)
        {
            if(x == y)
                continue;
            
            for(int i=0; i<x; ++i)
            {
                for(int j=0; j<y; ++j)
                {
                    counter += count(x,y, width-i, height-j);
                }
            }
        }
        y = 1;
    }

    return counter;
    }

    long long count(int x, int y, int xmax, int ymax)
    {
    return (xmax/x) * (ymax/y);
    }
};