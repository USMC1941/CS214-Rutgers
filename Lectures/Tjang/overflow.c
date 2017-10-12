#include <stdio.h>
#include <string.h>

int main(void) {

  char buff[10];
  int pass = 0;

  // printf ("%p %p %p %p", (void*)&buff[0], (void*)&buff[9] ,  (void*)&pass, &x);
  printf("\n Enter the password : \n");
  gets(buff);

  if(strcmp(buff, "thegeekstuff")) {
    printf ("\n Wrong Password \n");
  }
  else {
    printf ("\n Correct Password \n");
    pass = 1;
  }

  if(pass == 1) {
    /* Now Give root or admin rights to user*/
    printf ("\n Root privileges given to the user \n");
  }
  //
  return 0;
}
