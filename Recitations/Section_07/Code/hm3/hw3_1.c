/** Include Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Define the max char length */
#define MAX_L 4096

/** Replace function */
void replace(char string[], char from[], char to[])
{
  // a buffer variable to do all replace things
  char buffer[MAX_L];
  // to store the pointer returned from strstr
  char *s;

  // if string doesn't contain from, return
  if (!(s = strstr(string, from)))
  {
    return;
  }

  // copy all the content to buffer before the first occurrence of the search string
  strncpy(buffer, string, s - string);

  // prepare the buffer for appending by adding a null to the end of it
  buffer[s - string] = '\0';

  // append using sprintf function
  sprintf(buffer + (s - string), "%s%s", to, s + strlen(from));

  // empty string for copying
  string[0] = 0;
  strcpy(string, buffer);
  // pass recursively to replace other occurrences
  return replace(string, from, to);
}

int main()
{
  char string1[] = "receive_perceive_conceive_retrieve";
  replace(string1, "ei", "ei");

  char string2[] = "receive_perceive_conceive_retrieve";
  replace(string2, "ve", "1234");

  printf("%s\n", string1);
  printf("%s\n", string2);

  return 0;
}
