#ifndef SORTINGKEY_H
#define SORTINGKEY_H


#define INDEX_TYPE_STRING			123					// Default. If data type neither float nor integer, it will be String
#define INDEX_TYPE_FLOAT			23					// Numbers. At least one of them is with decimal point
#define INDEX_TYPE_INTEGER		10					// Numbers. None with decimal point


// Index for the sortingkey
typedef struct SKeyIndex {
	int index;															// (index)th field to sort. First field is 0
	int idxType;														// What type of index: STRING, FLOAT or INTEGER
} SKeyIndex;


/*
Gets the index for the sortingkey from the Header Line
*/
int getSortingKeyIndexFromHeaderLine(char* input, char* key, SKeyIndex* pSKI);


#endif