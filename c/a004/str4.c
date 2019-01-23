
#include <stdio.h>


int main(int argc, char* argv[])
{

    printf("address of argc is %p\n", &argc);
    printf("address of char* argv[]=%p\n", &argv);

    printf("address of static variables\n");
    int var1;
    printf("address of local variable=%p\n", &var1);
    int var2;
    int * p_to_var2 = &var2;
    printf("address of var2=%p\n", &var2);
    printf("value of pointer=%p\n", p_to_var2);

    int * p_to_var3;
    printf("value of pointer=%p\n", p_to_var3);
    printf("value of unint pointer=%d\n", *p_to_var3);

    return 0;
}
