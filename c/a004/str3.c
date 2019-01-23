
#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
typedef char bool;
#define true 1
#define false 0
#endif // __cplusplus

void convert_to_celsius(double value);
void convert_to_fahrenheit(double value);
void convert(double value, bool to_fahrenheit)
{
    if(to_fahrenheit)
        convert_to_fahrenheit(value);
    else
        convert_to_celsius(value);
}

#define ARG_SIZE 2

int main(int argc, char* argv[])
{

    if (argc < 2)
        exit(1);

    double args[ARG_SIZE];

    for(int i=1; i<ARG_SIZE+1 && i<argc; ++i)
    {
        args[i-1] = atoi(argv[i]);
    }

    for(int i=0; i<ARG_SIZE; ++i)
    {
        if(i / 1 == 0)
            convert(args[i], true);
        else
            convert(args[i], false);
    }

    return 0;
}


void convert_to_celsius(double value)
{
    printf("formula conversion from fahrenheit to celsius\n");
    printf("(f - 32) * 5/9\n");

    printf("value is %f\n", value);

    printf("we use double to store and calculate value:\n");
    printf("result of (f - 32) * 5/9\n");
    printf("where f=%f\n", value);
    printf("(f - 32) * 5/9 = %f\n", (value - 32) * 5/9);
    printf("\n***Fahrenheit to Celcius End***\n\n"); 
}

void convert_to_fahrenheit(double value)
{
    printf("formula conversion from celsius to fahrenheit\n");
    printf("c * 9 / 5 + 32\n");

    printf("value is %f\n", value);

    printf("we use double to store and calculate value:\n");
    printf("result of c * 9/5 + 32\n");
    printf("where c=%f\n", value);
    printf("c * 9/5 + 32 = %f\n", value * 9/5 + 32);
    printf("\n***Celsius to Fahrenheit End***\n\n"); 
}