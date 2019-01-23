#include <stdio.h>

#include "func.h"

#define SQR(x) multiply(x, x)

int main(int argc, char* argv[])
{

    for(int i=0; i<11; ++i)
    {
        int j=0;
        while(j<11)
        {
            int tmp = j+i;
            printf("%-3d ", SQR(tmp));
            ++j;
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}