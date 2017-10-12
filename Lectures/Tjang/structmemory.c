#include <stdio.h>

struct X {
    short s;

    int   i;
    char  c;

};

struct Y {
    int   i;
    char  c;

    short s;
};

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
