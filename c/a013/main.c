#include <stdio.h>
typedef unsigned char byte;


int main()
{
    int i = 42;
    float f = 3.14f;
    double d = 0.222121212;

    unsigned ui = 43u;
    short si = 123;
    long li = 12;

    printf("sizeof int %ld\n", sizeof(i));
    printf("sizeof float %ld\n", sizeof(f));
    printf("sizeof double %ld\n", sizeof(d));

    printf("sizeof unsigined int %ld\n", sizeof(ui));
    printf("sizeof short %ld\n", sizeof(si));
    printf("sizeof long %ld\n", sizeof(li));

    return 0;
}