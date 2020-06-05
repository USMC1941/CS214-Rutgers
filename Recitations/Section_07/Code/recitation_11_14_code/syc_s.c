#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// compile by gcc -o syc_s syc_s.c -pthread
// ./syc_s

int MAX = 10;
int count = 1;
sem_t s;

void print_star(int i)
{
    int j;
    for (j = 1; j <= i; j++)
    {
        printf("*");
    }
    // printf(" %d", i);
    printf("\n");
    //printf(" %d\n", i);
}
void *even(void *arg)
{
    //printf("This is even thread()\n");
    while (count <= MAX)
        if (count % 2 == 0)
        {
            sem_wait(&s);
            print_star(count++);
            sem_post(&s);
            // printf(" even: %d\n", count);
            // count++;
            //printf(" even: %d\n", count++);
        }
    pthread_exit(0);
}

void *odd(void *arg)
{
    //printf("This is odd thread()\n");
    while (count < MAX)
        if (count % 2 == 1)
        {
            sem_wait(&s);
            print_star(count++);
            sem_post(&s);
            // printf(" odd: %d\n", count);
            // count++;
            // printf(" odd: %d\n", count++);
        }
    pthread_exit(0);
}

int main()
{
    sem_init(&s, 0, 1);

    pthread_t t1;
    pthread_t t0;

    pthread_create(&t1, 0, &odd, NULL);
    pthread_create(&t0, 0, &even, NULL);

    pthread_join(t1, 0);
    pthread_join(t0, 0);

    sem_destroy(&s);

    return 0;
}