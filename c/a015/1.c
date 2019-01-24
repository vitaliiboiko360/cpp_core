#include <stdio.h>

int main()
{
    char * message = "null-terminated string";
    char * escape_chars = "\\this is slack\"this is quote";
    printf("%s\n", message);
    printf("\nantother string test\n");
    printf("%s\n", escape_chars);
    return 0;
}