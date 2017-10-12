#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) ( ((a) > (b)) ? (a) : (b))

int main() {
  char string0[50] = {'e','n','o','u','g','h'};
  char string1[35] = "receive_perceive_conceive_retrieve";
  char string2[] = "four_similar_words";

  printf("sizeof_string0 %lu\n", sizeof(string0));
  printf("sizeof_string1 %lu\n", sizeof(string1));
  printf("sizeof_string2 %lu\n", sizeof(string2));
  printf("strlen_string0 %lu\n", strlen(string0));
  printf("strlen_string1 %lu\n", strlen(string1));
  printf("strlen_string2 %lu\n\n", strlen(string2));

  if (sizeof(string0) > strlen(string0) + strlen(string1)) {
    strcat(string0, string1);
    printf("string0: %s\n", string0);
  }

  printf("sizeof_string0 %lu\n", sizeof(string0));
  printf("strlen_string0 %lu\n\n", strlen(string0));

  if (sizeof(string1) > strlen(string1) + strlen(string2)) {
    strcat(string1,string2);
    printf("string1:%s\n", string1);
  }

  printf("sizeof_string1 %lu\n", sizeof(string0));
  printf("strlen_string1 %lu\n\n", strlen(string0));

  int L = max(strlen(string1), strlen(string2)) * 2;
  char *double_long_string = (char*)malloc(sizeof(char) * L);

  printf("sizeof_double_long_string %lu\n", sizeof(double_long_string));
  printf("strlen_double_long_string %lu\n\n", strlen(double_long_string));

  strcpy(double_long_string, string1);
  strcat(double_long_string, string2);

  printf("sizeof_double_long_string %lu\n", sizeof(double_long_string));
  printf("strlen_double_long_string %lu\n\n", strlen(double_long_string));

  free(double_long_string);
  return 0;
}
