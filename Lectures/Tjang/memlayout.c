#include <stdio.h>

int main(){

	char buff[] = {1,2,3,4,5,6,7,8,9,10};
	char x = 255;
	buff[10] = 16;
	printf("%p  %p  %p", &buff[0],  &buff[9], &x);
}
