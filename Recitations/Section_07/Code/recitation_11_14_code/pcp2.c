// gcc -o pcp2 pcp2.c -pthread
// ./pcp2

#include <stdio.h>
#include <pthread.h>

#define MAX 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;  //if queue is full
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER; //if queue is empty

int top = 0;
int bottom = 0;

void *produce(void *arg)
{
    int i;
    for (i = 0; i < MAX * 2; i++)
    {
        pthread_mutex_lock(&mutex);
        while ((top + 1) % MAX == bottom)
        {
            printf("full! producer is waiting\n");
            pthread_cond_wait(&notfull, &mutex); //waiting for queue is not full
        }

        top = (top + 1) % MAX;
        printf("now top is %d\n", top);
        pthread_cond_signal(&notempty); //send information that queue is not empty

        pthread_mutex_unlock(&mutex);
    }
    return (void *)1;
}

void *consume(void *arg)
{
    int i;
    for (i = 0; i < MAX * 2; i++)
    {
        pthread_mutex_lock(&mutex);
        while (top % MAX == bottom)
        {
            printf("empty! consumer is waiting\n");
            pthread_cond_wait(&notempty, &mutex); //waiting for queue is not empty
        }
        bottom = (bottom + 1) % MAX;
        printf("now bottom is %d\n", bottom);
        pthread_cond_signal(&notfull); //waiting for queue is not full

        pthread_mutex_unlock(&mutex);
    }

    return (void *)2;
}

int main(int argc, char *argv[])
{
    pthread_t thid1;
    pthread_t thid2;
    pthread_t thid3;
    pthread_t thid4;

    int ret1;
    int ret2;
    int ret3;
    int ret4;

    pthread_create(&thid1, NULL, produce, NULL);
    pthread_create(&thid2, NULL, consume, NULL);
    pthread_create(&thid3, NULL, produce, NULL);
    pthread_create(&thid4, NULL, consume, NULL);

    pthread_join(thid1, (void **)&ret1);
    pthread_join(thid2, (void **)&ret2);
    pthread_join(thid3, (void **)&ret3);
    pthread_join(thid4, (void **)&ret4);

    return 0;
}
