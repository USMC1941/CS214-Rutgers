#include "stdio.h"
#include "string.h"

/*
void replace(char*original, char*sub, char*new){
    char *offset =strstr(original,sub);
    if (offset==NULL){
        return;
    }

    strcpy(offset,sub);

}
*/
int main(){

    //the string literal is not on the heap and stack
    //Many C compilers allocate string literals in read-only memory, hence the bus error!
    char * original_literal = "replaceoriginal"; 
    printf("address of string literal %p\n",original_literal);
         

    char* original=(char*)malloc(sizeof(char)*50);

    strncpy(original,original_literal,(strlen(original_literal)+1)*sizeof(char*));

    printf("original: \n(%s)\n",original);
    
     
    char substr[]="orig";
    char newstr[]="abcd";

    char* offset=strstr(original,substr);

    printf("offset: (%s)\n",offset);
    
    int size=strlen(newstr)*sizeof(char);

    strncpy(offset,newstr,size);
    //memcpy(offset,substr,size);

    printf("final string: \n(%s)\n",original);

    return 0;

}