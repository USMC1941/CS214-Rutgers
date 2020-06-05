#include <pthread.h>
#include <stdio.h>

// compile by gcc -o nosyc nosyc.c -pthread
// ./nosyc

int MAX = 10;
int count = 1;

void *printstar_odd(void *param)
{
   int j;
   while (count < MAX)
   {
      if (count % 2 == 1)
      {
         for (j = 1; j <= count; j++)
         {
            printf("*");
         }
         printf("\n");
         count++;
      }
   }

   return NULL;
}

void *printstar_even(void *param)
{
   int j;
   while (count <= MAX)
   {
      if (count % 2 == 0)
      {
         for (j = 1; j <= count; j++)
         {
            printf("*");
         }
         printf("\n");
         count++;
      }
   }

   return NULL;
}

int main()
{
   pthread_t tid1, tid0;
   pthread_create(&tid1, 0, printstar_odd, NULL);
   pthread_create(&tid0, 0, printstar_even, NULL);
   pthread_join(tid1, 0);
   pthread_join(tid0, 0);
   return 0;
}