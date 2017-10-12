#include <stdio.h>
#define MAXNUM 10

// test preprocessing
// class 214
int main(int argc, char const *argv[]) {
	int i, j;
	for(i = 0; i < MAXNUM; i++){
		for(j = 0; j < i; j++){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}