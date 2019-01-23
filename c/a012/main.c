#include "func.h"

#define SQUARE(a) multiply(a,a)
#define PRINTEND 1

int main(int argc, char **argv)
{
    /*
    int a,b;
    a = 10;
    b = 14;
    printf("multiply call = %d\n", multiply(a,b));

    printf("multiply2 call = %d\n", multiply2(a,b));

    print_def_size();
    print_file();

    printf("SQUARE macros results = %d\n", SQUARE(9));

    #if defined(PRINTEND)
        printf("The End\n");
    #endif // PRINTEND
    */

    /*
    int a = 5;
    int b;

    printf("initialized var = %d\n", a);
    printf("uninitialized var = %d\n", b);

    for(int i=0; i<5; ++i)
    {
        func2();
        func();
    }
    */

    print_volume();
    up();
    print_volume();
    down();
    print_volume();
    up();
    up();
    print_volume();
    

    return 0;
}