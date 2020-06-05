#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char str[10];
	char str2[20];
	//get str from input (last character is '\n')
	scanf("%s", str);
	//get only one character from input
	getchar();
	//get whole line from input file
	gets(str2);
	printf("out put sth: %s\n", str);
	printf("out put sth: %s\n", str2);
	return 0;
}