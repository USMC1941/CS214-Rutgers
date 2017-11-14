#include <stdio.h>
#include <pthread.h>
// remember to set compilation option -pthread

 void *busy(void *ptr) {
// // ptr will point to "Hi"
     puts("Hello World");
         return NULL;
      }


	int main() {

            pthread_t id;
            pthread_create(&id, NULL, busy, "Hi");
            while (1) {} // Loop forever
        }
