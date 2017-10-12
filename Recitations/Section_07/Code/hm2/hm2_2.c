#include <stdio.h>

int main() {
  // try to exchange the order of a and b
  // see what happens?
  /*
  char b[10] = "0123456789";
  char a[10] = "abcdefghij";
  */

  char a[10] = "abcdefghij";
  char b[10] = "0123456789";

  char *p = b;
  int i;
  for (i = 0; i < 20; i++) {
    printf("%c\n", *(p+i));
    printf("%u\n", p+i);
  }
  return 0;
}
