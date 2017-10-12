#include <stdio.h>

int main() {
	char a[10] = "abcdefghij";
	char b[10] = "0123456789";
	int *p = a;
	printf("%d\n\n", *p);
	
	int c = *p;
	char *np = &c;

	printf("%c\n", *np);
	printf("%c\n", *(np+1));
	printf("%c\n", *(np+2));
	printf("%c\n", *(np+3));
	printf("%c\n", *(np+4));
	printf("%c\n", *(np+5));
	printf("%c\n", *(np+6));
	printf("%c\n", *(np+7));
	
	return 0;
}