#ifndef HELPER_H
#define HELPER_H


/*
Holds a chunk of memory and its length
*/
typedef struct BUFFER {
	size_t	length;
	char*	data;
} BUFFER;


/*
Initialize a BUFFER by allocate initSize byte of memory
*/
char* initBuffer(BUFFER* pBuf, int initSize);


/*
Resize the BUFFER by re-allocate size byte of memory
*/
char* resizeBuffer(BUFFER* pBuf, int size);


/*
Frees buffer memory
*/
void freeBuffer(BUFFER* pBuf);


/*
Strip of Newline char at the end of the string
*/
void stripOffNewline(BUFFER* pBuf);


/*
Compare string regardless cases
*/
int strcicmp(char const *input1, char const *input2);


#endif