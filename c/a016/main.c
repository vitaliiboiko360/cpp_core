#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void *
thread_func(void* arg)
{
    char *s = (char*)arg;
    printf("%s", s);
    return (void*) strlen(s);
}

int main(int argc, char* argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, thread_func, "Hello there!\n");

    if (s!=0)
    {
        printf("%s", "pthread_create");
        exit(EXIT_FAILURE);
    }

    printf("message from main()\n");
    s = pthread_join(t1, &res);
    if (s!=0)
    {
        printf("%s", "pthread_join");
        exit(EXIT_FAILURE);
    }

    printf("Thread returned %ld\n", (long)res);
    exit(EXIT_SUCCESS);
}