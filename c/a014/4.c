#include <stdio.h>

int main()
{
    int count = 10;
    while (count < 10)
    {
        printf("count %d\n", ++count);
    }
    printf("this time do the same with for loop\n");

    for(int i=0;;)
    {
        printf("iteration #%d\n", ++i);
        if (i==10) break;
    }
}
/*
#include <stdio.h>

int main()
{
    float res1 = 5.f / 9;
    float res2 = 9.f / 5;
    printf("%.2f %.2f\n", res1, res2);
}
*/
/*
#include <stdio.h>

int main()
{
    float f1 = 0.123;
    float * pf1 = &f1;
    float * pf2;
    float * pf3 = NULL;
    printf("address of %p\n", &f1);
    printf("ptr value %p\n", pf1);
    printf("uninit ptr %p\n", pf2);
    printf("null ptr %p\n", pf3);
}\n
*/