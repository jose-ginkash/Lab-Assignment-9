// Jose Mathew
// 4/12/2024
// Lab Assignment 9


#include <stdio.h>
#include <stdlib.h>


struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next; 
};


struct RecordType** hashTable;
int hashTableSize = 23; // Size of the hash table


// Compute the hash function
int hash(int x)
{
    return x % hashTableSize;
}


// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL; // Initialize next pointer to NULL
        }

        fclose(inFile);
    }

    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}



// Display records in hash structure
void displayRecordsInHash()
{
    int i;
    struct RecordType *p;
    for (i = 0; i < hashTableSize; ++i)
    {
        p = hashTable[i];
        if (p != NULL)
        {
            printf("index %d -> ", i);
            while (p != NULL)
            {
                printf("%d, %c, %d -> ", p->id, p->name, p->order);
                p = p->next;
            }
            printf("NULL\n");
        }
    }
}


int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    hashTable = (struct RecordType**) malloc(sizeof(struct RecordType*) * hashTableSize);
    for (int i = 0; i < hashTableSize; ++i)
        hashTable[i] = NULL; // Initialize all elements to NULL

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Insert records directly in the main function
    for (int i = 0; i < recordSz; ++i) {
        int index = hash(pRecords[i].id);
        pRecords[i].next = hashTable[index];
        hashTable[index] = &pRecords[i];
    }

    displayRecordsInHash();

    free(pRecords);
    free(hashTable);
}