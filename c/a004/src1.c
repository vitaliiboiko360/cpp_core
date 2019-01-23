
#include <stdio.h>

int main(int argc, char* argv[])
{

    int a = 5;
    char c = 'c';
    double f_number = 6.78;
    char* str = "Samuel";

    printf("sizeof(int)=%lu\nvalue of a=%d\n", sizeof(a), a);
    printf("sizeof(char)=%lu\nvalue of c=%c\n", sizeof(c), c);
    printf("sizeof(float)=%lu\nvalue of f=%f\n", sizeof(f_number), f_number);
    printf("float into exponent notation %%e\n");
    printf("%%e = %e\n", f_number);
    printf("sizeof(str)=%lu\nvalue of str=%s\n", sizeof(str), str);

    

    return 0;
}