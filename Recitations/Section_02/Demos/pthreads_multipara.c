#include <stdio.h>
#include <pthread.h>

struct arg_struct {
    int arg1;
    int arg2;
};

void *print_the_arguments(void *arguments)
{
    struct arg_struct *args = (struct arg_struct *)arguments;
    printf("parameter 1 (%d)\n", args -> arg1);
    printf("parameter 2 (%d)\n", args -> arg2);
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    pthread_t some_thread;
    struct arg_struct args;
    args.arg1 = 214;
    args.arg2 = 314;

    if (pthread_create(&some_thread, NULL, &print_the_arguments, (void *)&args) != 0) {
        printf("fail to create pthread wirh id %d\n",(int)some_thread);
        return -1;
    }

    printf("waiting thread with id %d return\n",(int)some_thread);
    int joinReturn;
    joinReturn = pthread_join(some_thread, NULL); /* Wait until thread is finished */

    printf("pthread_join return value %d with threadid %d\n",joinReturn,(int)some_thread);
    
    printf("main thread finish\n");

}