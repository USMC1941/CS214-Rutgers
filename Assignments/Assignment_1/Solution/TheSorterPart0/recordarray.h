#ifndef RECORDARRAY_H
#define RECORDARRAY_H


// Array of records
typedef struct RecordArray {
	Record** 	pRecArray;				// Array of Record pointer
	int 		 	iCapacity;					// Total capacity
	int		 	iSize;						// Current size
} RecordArray;


/*
Initializes the record array
*/
int initializeRecordArray(RecordArray* pRecordArray, int initialCapacity);


/*
Inserts one record into the RecordArray
Expend capacity if need to
*/
int insertOneRecord(RecordArray* pRecordArray, Record* pRecord);


/*
Frees all memory allocated for the RecordArray
*/
void cleanRecordArray(RecordArray* pRecordArray);


#endif