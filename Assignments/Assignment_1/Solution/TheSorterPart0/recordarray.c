#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "sortingkey.h"
#include "record.h"
#include "recordarray.h"


/*
Initializes the record array
Return:
	1 means failed
	0 means OK
*/
int initializeRecordArray(RecordArray* pRecordArray, int initialCapacity) {
	int outcome = 1;			// 1 means failed
	
	if (pRecordArray != NULL) {
		pRecordArray->pRecArray = (Record**)malloc(sizeof(Record*) * initialCapacity);
		
		// Allocate success
		if (pRecordArray->pRecArray != NULL) {
			pRecordArray->iCapacity = initialCapacity;
			pRecordArray->iSize = 0;
			//
			outcome = 0;
		}
		else {
			//
		}
	}
	//
	return outcome;
}


/*
Inserts one record into the RecordArray
Return:
	1 means failed
	0 means OK
*/
int insertOneRecord(RecordArray* pRecordArray, Record* pRecord) {
	int outcome;
	
	// Check inputs
	if (pRecordArray == NULL || (pRecordArray->pRecArray) == NULL || pRecord==NULL) {
		outcome = 1;
	}
	else {
		// Has enough space to insert
		if (pRecordArray->iCapacity > pRecordArray->iSize) {
			// Insert at the end of the array
			*(pRecordArray->pRecArray + pRecordArray->iSize) = pRecord;
			pRecordArray->iSize++;
			//
			outcome = 0;
		}
		else {
			pRecordArray->pRecArray = (Record**)realloc(pRecordArray->pRecArray, sizeof(Record) * (pRecordArray->iCapacity + SIZE_DELTA));
			pRecordArray->iCapacity += SIZE_DELTA;
			//
			*(pRecordArray->pRecArray + pRecordArray->iSize) = pRecord;
			pRecordArray->iSize++;
			//
			outcome = 0;
		}
	}
	//
	return outcome;
}


/*
Frees the RecordArray
*/
void cleanRecordArray(RecordArray* pRecordArray) {
	if (pRecordArray != NULL) {
		int i;
		for (i = 0; i < pRecordArray->iSize; i++) {
			free( (*(pRecordArray->pRecArray + i)) );
		}
		//
		free(pRecordArray->pRecArray);
	}
}