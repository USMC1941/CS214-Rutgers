#include <stdio.h>

//min=7,  predict= 12
struct X {
	short s;
	int   i;
	char  c;
};

//min = 7, predict = 8
struct Y {
	int   i;
	char  c;
	short s;
};

//min = 7, predict = 8
struct Z {
	int   i;
	short s;
	char  c;
};

const int sizeX = sizeof(struct X);
const int sizeY = sizeof(struct Y);
const int sizeZ = sizeof(struct Z);

int main(){
	printf("%d  %d  %d", sizeX, sizeY, sizeZ);
}
