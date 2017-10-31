#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "helper.h"
#include "sortingkey.h"
#include "record.h"
#include "recordarray.h"
#include "mergesort.h"
#include "sorter.h"
#include "tokenizer.h"


int main(int argc, char* argv[]) {
	// Check for right number of inputs
	if (argc == 3 || argc == 4) {
		// Good
	}
	else {
		printf( "Usage Sorting: sorter -c sorting_key_field\n");
		printf( "Usage Analyzing: sorter -r field1 field2\n");
		printf( "Invalid parameters count %d!\n", argc);
		return 1;
	}
	
	// Parameters
	char* pOption = argv[1];
	
	// Check command line option
	if (strcmp(pOption, "-c") == 0 && argc == 3) {
		char* pSortingKey = argv[2];
		//
		return doSorting(pSortingKey);
	}
	else if (strcmp(pOption, "-r") == 0 && argc == 4) {
		char* pField1 = argv[2];
		char* pField2 = argv[3];
		//
		return getCorrelation(pField1, pField2);
	}
	else {
		printf( "Usage Sorting: sorter -c sorting_key_field\n");
		printf( "Usage Analyzing: sorter -r field1 field2\n");
		printf( "Invalid option or parameter count: %s, %d!\n", pOption, argc);
		return 1;
	}
}


/*
Perform sorting with sortingKey
*/
int doSorting(char* pSortingKey) {
	// Variables
	PFUNC_COMPARE_DATA pFuncCompare = compare;

	// To hold key index
	SKeyIndex sKI;
	sKI.index = -1;
	sKI.idxType = INDEX_TYPE_INTEGER;									// Initially set to integer. Change it later if necessary

	// Buffer for reading from stdin
	BUFFER readBuf;																	// Buffer for reading
	initBuffer(&readBuf, 0);															// Memory to be allocated by getline. Will be freed at the end
	//
	BUFFER headerBuf;																// For holding the header line

	// To hold record array
	RecordArray rcdArray;
	rcdArray.pRecArray	= NULL;
	rcdArray.iCapacity		= 0;
	rcdArray.iSize			= 0;
	
	int outcome = 1;
	if (initializeRecordArray(&rcdArray, SIZE_INITIAL) != 0) {
		printf( "Could not initilize Record array\n");
	}
	else {
		// Read the header and get the index for the sorting key
		if (getline(&(readBuf.data), &(readBuf.length), stdin) > 0 ) {
			stripOffNewline(&readBuf);
			//
			initBuffer(&headerBuf, readBuf.length);																			// Buffer for holding header line
			strcpy(headerBuf.data, readBuf.data);																				// Keep an copy of the header line before tokenize
			//
			if (getSortingKeyIndexFromHeaderLine(readBuf.data, pSortingKey, &sKI)) {
				printf( "Could not parse sorting key\n");
			}
			else {
				// Read data line by line. Creates record and put them into array
				while (getline(&(readBuf.data), &(readBuf.length), stdin) > 0) {
					stripOffNewline(&readBuf);
					
					Record* pRecord = createRecord(readBuf.data, &sKI);
					if (pRecord) {
						insertOneRecord(&rcdArray, pRecord);
					}
					else {
						printf( "Could not create record\n");
					}
				}
				
				// Sort array according to Sorting Key
				mergeSort((void**)rcdArray.pRecArray, 0, rcdArray.iSize - 1, &sKI, pFuncCompare);

				// Output sorted records to file
				writeRecordArrayToStdout(&headerBuf, &rcdArray);
				
				outcome = 0;
			}
		}
		else {
			printf("Could not read header line\n");
		}
	}
	
	// Clean up memory
	if (rcdArray.pRecArray != NULL) {
		cleanRecordArray(&rcdArray);
	}
	
	//Free buffer
	freeBuffer(&readBuf);
	freeBuffer(&headerBuf);
	
	// Return
	return outcome;
}


/*
Writes the data from the RecordArray into stdout
*/
void writeRecordArrayToStdout(BUFFER* pHeader, RecordArray* pRecordArray) {
	FILE *file = stdout;
	
	//print header
	fprintf(file, "%s\n", pHeader->data);																										// Print header line
	
	//print all records
	int i;
	for (i = 0; i < pRecordArray->iSize; i++) {
		*((*(pRecordArray->pRecArray + i))->pSKeyTerm) = (*(pRecordArray->pRecArray + i))->chHold;		// Put back the char set to '\0' for sorting key
		fprintf(file, "%s\n", (*(pRecordArray->pRecArray + i))->recordData);													// Print Records in a loop
	}
}


/*
Get correlation between two fields
*/
int getCorrelation(char* pField1, char* pField2) {
	// To hold key index
	SKeyIndex sKI1;
	sKI1.index = -1;
	sKI1.idxType = INDEX_TYPE_INTEGER;									// Initially set to integer. Change it later if necessary
	//
	SKeyIndex sKI2;
	sKI2.index = -1;
	sKI2.idxType = INDEX_TYPE_INTEGER;									// Initially set to integer. Change it later if necessary

	// Buffer for reading from stdin
	BUFFER readBuf;																	// Buffer for reading
	initBuffer(&readBuf, 0);															// Memory to be allocated by getline. Will be freed at the end
	//
	BUFFER tempBuf;

	// To hold record array
	RecordArray rcdArray1;
	rcdArray1.pRecArray	= NULL;
	rcdArray1.iCapacity	= 0;
	rcdArray1.iSize			= 0;
	//
	RecordArray rcdArray2;
	rcdArray2.pRecArray	= NULL;
	rcdArray2.iCapacity	= 0;
	rcdArray2.iSize			= 0;
	
	int outcome = 1;
	if (initializeRecordArray(&rcdArray1, SIZE_INITIAL) != 0 || initializeRecordArray(&rcdArray2, SIZE_INITIAL) != 0) {
		printf( "Could not initilize Record array\n");
	}
	else {
		// Read the header and get the index for the sorting key
		if (getline(&(readBuf.data), &(readBuf.length), stdin) > 0 ) {
			stripOffNewline(&readBuf);
			//
			initBuffer(&tempBuf, 	readBuf.length);																			// Buffer for holding header line
			strcpy(tempBuf.data, readBuf.data);																				// Keep an copy of the header line before tokenize
			//
			if (getSortingKeyIndexFromHeaderLine(readBuf.data, pField1, &sKI1) || getSortingKeyIndexFromHeaderLine(tempBuf.data, pField2, &sKI2)) {
				printf( "Could not parse sorting key\n");
			}
			else {
				// Read data line by line. Creates record and put them into array
				while (getline(&(readBuf.data), &(readBuf.length), stdin) > 0) {
					stripOffNewline(&readBuf);
					//
					resizeBuffer(&tempBuf, 	readBuf.length);
					strcpy(tempBuf.data, readBuf.data);
					//
					Record* pRecord1 = createRecord(readBuf.data, &sKI1);
					if (pRecord1) {
						insertOneRecord(&rcdArray1, pRecord1);
					}
					else {
						printf( "Could not create record1\n");
					}
					//
					Record* pRecord2 = createRecord(tempBuf.data, &sKI2);
					if (pRecord2) {
						insertOneRecord(&rcdArray2, pRecord2);
					}
					else {
						printf( "Could not create record2\n");
					}
				}
				
				if (sKI1.idxType == INDEX_TYPE_STRING )  {
					printf( "Field1 is not of number type.\n");
				}
				else if (sKI2.idxType == INDEX_TYPE_STRING) {
					printf( "Field2 is not of number type.\n");
				}
				else if (rcdArray1.iSize != rcdArray2.iSize) {
					printf( "Size of array 1 and array 2 are not the same.\n");
				}
				else {
					// Sort array according to Sorting Key
					double output;
					doCorrelation(rcdArray1.pRecArray, &sKI1, rcdArray2.pRecArray, &sKI2, rcdArray1.iSize, &output);

					// Output sorted records to file
					fprintf(stdout, "Correlation between %s %s: %f\n", pField1, pField2, output);
					
					outcome = 0;
				}
			}
		}
		else {
			printf("Could not read header line\n");
		}
	}
	
	// Clean up memory
	if (rcdArray1.pRecArray != NULL) {
		cleanRecordArray(&rcdArray1);
	}
	//
	if (rcdArray2.pRecArray != NULL) {
		cleanRecordArray(&rcdArray2);
	}
	
	//Free buffer
	freeBuffer(&readBuf);
	freeBuffer(&tempBuf);
	
	// Return
	return outcome;
}


/*
Performs Correlation Algorithm
*/
int doCorrelation(Record* arr1[], SKeyIndex* pSKI1, Record* arr2[], SKeyIndex* pSKI2, int length, double* pOutput) {
	int count = 0;
	double x, y, sum_x, sum_y, sum_xx, sum_yy, sum_xy;
	int len1, len2;
	//
	int i;
	for (i=0; i < length; i++) {
		Record* pRecord1 = *(arr1 + i);
		Record* pRecord2 = *(arr2 + i);
		//
		len1 = strlen(pRecord1->pSKey);
		len2 = strlen(pRecord2->pSKey);
		//
		if (len1 == 0 || len2 == 0) {
			// Skip. At least one of the Records are NULL 
		}
		else {
			x = (double)pRecord1->fKey;
			y = (double)pRecord2->fKey;
			//
			count++;
			sum_x += x;
			sum_y += y;
			sum_xx += x*x;
			sum_yy += y*y;
			sum_xy += x*y;     
		}
	}
	//
	double r, nr=0.0D, dr_1=0.0D, dr_2=0.0D, dr_3=0.0D, dr=0.0D;
	//
    nr = (count * sum_xy) - (sum_x * sum_y);
	//
    double sum_x2 = sum_x * sum_x;
    double sum_y2 = sum_y * sum_y;
	//
    dr_1 = (count * sum_xx) - sum_x2;
    dr_2 = (count * sum_yy) - sum_y2;
    dr_3 = dr_1 * dr_2;
	//
    dr = sqrt(dr_3);
    r = (nr/dr);
	
	*pOutput = r;
	
	return 0;
}