#ifndef SORTER_H
#define SORTER_H


/*
Define structures and function prototypes for your sorter
*/


/*
Writes the data from the RecordArray into stdout
*/
void writeRecordArrayToStdout(BUFFER* pHeader, RecordArray* pRecordArray);


/*
Get correlation between two fields
*/
int getCorrelation(char* pField1, char* pField2);


/*
Performs Correlation Algorithm
*/
int doCorrelation(Record* arr1[], SKeyIndex* pSKI1, Record* arr2[], SKeyIndex* pSKI2, int length, double* pOutput);


/*
Perform sorting with sortingKey
*/
int doSorting(char* pSortingKey);



//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function


#endif