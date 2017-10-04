#include <stdio.h>

int main() {
   
   int i=5;
   int *ip = &i;
   printf("%d\n", *ip);
   printf("%u\n", ip);
   return 0;
}