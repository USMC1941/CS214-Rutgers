
/*
1. Write some code that declares two arrays of size 10 that are string literals.
        
Make a pointer to one of the arrays, cast it to be an int pointer, and print out its value.

Make a new integer, set it equal to the value of your int pointer, then make a pointer to that integer, cast it to be a char pointer, and print out 8 chars.

                                   What happened? Why?



97
down vote
accepted
A common technique is for string literals to be put in "read-only-data" section which gets mapped into the process space as read-only (which is why you can't change it).

It does vary by platform. For example, simpler chip architectures may not support read-only memory segments so the data segment will be writable.

Rather then try to figure out a trick to make string literals changeable (it will be highly dependent on your platform and could change over time), just use arrays:

*/

#include "stdio.h"
#include "stdlib.h"


void main(){

    //char stra[20] ="abcdefghvvv";

    //*stra++='f';
    /*
    printf("%s\n",stra);

    char *p = NULL;

    p=stra;
    
    int* p2=(int*)p;

    printf("ascii code of a %08X b %08d c %08d d %08d\n",'a','b','c','d');

    //out put by hexadecimal
    //In big endian, you store the most significant byte in the smallest address
    //In little endian, you store the least significant byte in the smallest address
    // 0x 64 -> 16*6+4=100
    // 0x 63 -> 16*6+3=99

    printf("value of p2 (%d)\n",*p2);

    printf("in 0X mode (%08X)\n",*p2);    


    int * temp=p2;

    printf("in 0X mode (%08X)\n",*(temp+1));
    

    
    //'int a' store in the stack area
    //string "abcdefgh" store in the data segment area
    //the address of integer a and the string is not continuous
    
    int a = *p2;
    
    char *p3= &a;

    char *p33= stra;

    int i=0;

    for(i=0;i<20;i++){
        printf("the char index (%d) p3 value (%c), p33 value (%c)\n",i,*p3,*p33);
        p3++;
        p33++;
    }

*/
     int i;
     char stra[20] ="abcdefghvvv";
     char strb[15]="abcdefghijklm";
     char strc[10]="123456789";
     char *p4=strb;
     printf("---------------------------\n");
     for (i=0;i<30;i++){
        printf("the char index (%d) value (%c)\n",i,*p4);
        p4++;
     }
     char *strd="abcd";

     char stre[]="Global";
     char strf[10]="abcdef";

     printf("addr of strd %p\n",strd);

     printf("addr of stra %p\n", stra);
     printf("addr of strb %p\n", strb);
     printf("addr of strc %p\n", strc);
     printf("addr of strf %p\n",strf);
     printf("addr of stre %p\n",stre);
     
}