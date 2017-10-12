#include <stdio.h>

void starp(int l) {
	if(l == 0) {
		return;
	}
	starp(l - 1);
	
	int i;
	for(i = 0; i < l; i++){
		printf("*");
	}
	printf("\n");
}

int main(int argc, char const *argv[]) {
	starp(10);
	return 0;
}
