#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// compile by gcc -o nosyc2 nosyc2.c -pthread
// ./nosyc2

int MAX = 10;
int count = 1;

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
            print_star(count++);
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
            print_star(count++);
            // printf(" odd: %d\n", count);
            // count++;
            // printf(" odd: %d\n", count++);
        }
    pthread_exit(0);
}

int main()
{
    pthread_t t1;
    pthread_t t0;

    pthread_create(&t1, 0, &odd, NULL);
    pthread_create(&t0, 0, &even, NULL);

    pthread_join(t1, 0);
    pthread_join(t0, 0);

    return 0;
}