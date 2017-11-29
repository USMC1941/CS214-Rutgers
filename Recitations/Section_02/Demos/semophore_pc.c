//refer to https://docs.oracle.com/cd/E19683-01/806-6867/sync-27385/index.html
//refer to https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-5%3A-Condition-Variables#implementing-counting-semphore

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#define BSIZE 1

typedef struct
{
    int count;
    pthread_mutex_t m;
    pthread_cond_t cv;
} sem_t;

typedef struct
{
    sem_t occupied;
    sem_t freeSpace;
    int vp;
    int vc;
    sem_t pmut;
    sem_t cmut;
    pthread_mutex_t m;
} buffer_t;

sem_post(sem_t *s)
{
    pthread_mutex_lock(&s->m);
    s->count++;
    pthread_cond_signal(&s->cv); /* See note */
    /* A woken thread must acquire the lock, so it will also have to wait until we call unlock*/

    pthread_mutex_unlock(&s->m);
}

sem_wait(sem_t *s)
{
    pthread_mutex_lock(&s->m);
    while (s->count == 0)
    {
        pthread_cond_wait(&s->cv, &s->m); /*unlock mutex, wait, relock mutex*/
    }
    s->count--;
    pthread_mutex_unlock(&s->m);
}

int sem_init(sem_t *s, int pshared, int value)
{
    if (pshared)
    {
        errno = ENOSYS /* 'Not implemented'*/;
        return -1;
    }

    s->count = value;
    pthread_mutex_init(&s->m, NULL);
    pthread_cond_init(&s->cv, NULL);
    return 0;
}

void producer(buffer_t *b)
{
    int i;
    sem_wait(&b->freeSpace);
    sem_wait(&b->pmut);

    pthread_mutex_lock(&b->m);
    printf("p");
    for (i = 0; i < b->vp; i++)
    {
        printf("*");
    }
    printf("\n");
    pthread_mutex_unlock(&b->m);

    b->vp = b->vp + 2;

    sem_post(&b->pmut);
    sem_post(&b->occupied);
}

void consumer(buffer_t *b)
{

    int i;
    int rv = sem_wait(&b->occupied);
    sem_wait(&b->cmut);

    //printf("return value %d occupied %d\n",rv,b->occupied);

    if (rv != 0)
    {
        printf("errno %d\n", errno);
    }

    pthread_mutex_lock(&b->m);
    printf("c");
    for (i = 0; i < b->vc; i++)
    {
        printf("*");
    }
    printf("\n");
    pthread_mutex_unlock(&b->m);

    b->vc = b->vc + 2;

    sem_post(&b->cmut);
    sem_post(&b->freeSpace);
}

int main()
{
    printf("example for producer and consumer problem\n");

    pthread_t tp;
    pthread_t tc;

    buffer_t buffer;

    //init
    sem_init(&buffer.occupied, 0, 0);
    sem_init(&buffer.freeSpace, 0, BSIZE);
    sem_init(&buffer.pmut, 0, 1);
    sem_init(&buffer.cmut, 0, 1);
    pthread_mutex_init(&buffer.m, NULL);

    buffer.vp = 1;
    buffer.vc = 2;

    int j = 20;

    while (j--)
    {
        //create consumer
        pthread_create(&tc, NULL, &consumer, (void *)&buffer);
    }

    j = 20;

    while (j--)
    {
        //create producer
        pthread_create(&tp, NULL, &producer, (void *)&buffer);
    }

    //it's better to use condition variable here
    sleep(2);

    return 0;
}