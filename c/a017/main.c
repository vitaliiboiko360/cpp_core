
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void* generate_random_stream(void* arg)
{
    while(1)
    {
        printf("%d ", rand());
        sleep(1);
    }

}

int main(int argc, char* argv[])
{

    pthread_t t1;
    pthread_create(&t1, NULL, &generate_random_stream, NULL);

    while(1)
    {
        printf("main\n");
        sleep(2);
    }

    int result = 0;
    pthread_join(t1, (void*)&result);
    printf("thread returned %d\n", result);
}