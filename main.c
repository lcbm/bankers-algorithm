#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "fileName.txt"

#define N_THREADS 2        /* number of threads to be created  n*/
#define N_RESOURCE_TYPES 3 /* number of resource types  m*/

// Function: Reads the file and return the matrix containg the max number of resources for each thread for each resource type
int **getMaxDemandFromFile();

//Function: prints a bidimentional array for testing purposes
void printMatrix();

int main()
{
    int **readFileMatrix = getMaxDemandFromFile();
    printMatrix(readFileMatrix);
}

int **getMaxDemandFromFile()
{
    int **matrixMaxDemand;
    int i;
    int j;
    int currentValue;

    FILE *fp;
    fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("File not found");
        exit(EXIT_FAILURE);
    }

    matrixMaxDemand = calloc(N_THREADS, sizeof(int *));
    for(i = 0; i < N_RESOURCE_TYPES; i++){
        matrixMaxDemand[i] = calloc(N_RESOURCE_TYPES, sizeof(int));
    }

    i = 0;
    while (i < N_THREADS || !feof(fp))
    {
        j = 0; 
        while (j < N_RESOURCE_TYPES || !feof(fp))
        {
            fscanf(fp, "%d", &currentValue);
            matrixMaxDemand[i][j] = currentValue;
            j++;
        }
        i++;
    }
    return matrixMaxDemand;
}

void printMatrix(int** matrix){
    int i;
    int j;
    for(i = 0; i < N_THREADS; i++){
        for( j = 0; j < N_RESOURCE_TYPES; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}