#include<stdio.h>
#include<stdlib.h>

int main() {
	char *s1 = "abcdefghij";
	char *s2 = "0123456789";
	int *a = (int*) s1;
	printf("int value: %d\n", *(a + 1));
	/*int b = 1751606885;
	char *s3 = (char*) &b; 
	for (int i = 0 ; i < 8 ; i++) {
		printf("%c ", s3[i]);
	}
	printf("\n");*/
	for (int i = 0 ; i < 20 ; i++) {
		printf("%c", s1[i]);
	}
	printf("\n");
	return 0;
}