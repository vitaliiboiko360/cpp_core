
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

    printf("formula conversion from celsius to fahrenheit\n");
    printf("c * 9 / 5 + 32\n");

    if (argc < 2)
        exit(1);

    int c = atoi(argv[1]);
    printf("first argument is %d\n", c);

    printf("we use int to store and calculate value:\n");
    printf("result of c * 9/5 +32\n");
    printf("where c=%d\n", c);
    printf("c * 9/5 + 32 = %d\n", c * 9/5 + 32);
    printf("\nppart1 end\n\n"); 


    printf("formula conversion from celsius to fahrenheit\n");
    printf("c * 9 / 5 + 32\n");

    double fc = atoi(argv[1]);
    printf("first argument is %f\n", fc);

    printf("we use double to store and calculate value:\n");
    printf("result of c * 9/5 +32\n");
    printf("where c=%f\n", fc);
    printf("c * 9/5 + 32 = %f\n", fc * 9/5 + 32);
    printf("\npart2 end\n\n"); 

    return 0;
}