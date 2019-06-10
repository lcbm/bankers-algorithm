#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Constants defined by the exercise */
#define THREAD_NUM 5     /* number of threads to be created */
#define RESOURCE_TYPES 3 /* number of resource types */

/* Banker's Algorithm data structures */
/* indicates the number of available resources of each type */
int available[RESOURCE_TYPES] = {
    3, 3, 2
};

/* defines the maximum demand of each thread */
int max[THREAD_NUM][RESOURCE_TYPES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

/* defines the number of resources of each type currently allocated to each thread */
int allocation[THREAD_NUM][RESOURCE_TYPES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

/* indicates the remaining resource need of each thread */
int need[THREAD_NUM][RESOURCE_TYPES] = {
    {7, 4, 3},
    {1, 2, 2},
    {6, 0, 0},
    {0, 1, 1},
    {4, 3, 1}
};

/* Prototype functions */
int isSafeState(void);
int isArrayTrue(int a[], int size);
int lessEqualThan(int *a, int *b, int size);
void allocateResources(int *request, int process);
void addArray(int *a, int *b, int size);
void subArray(int *a, int *b, int size);
void printState(void);

/* Testa se as solicitacoes de recursos deixarão o sistema em estado nao-seguro */
int main(int argc, char const *argv[])
{
    printState();
    printf("\nIs safe? %d\n", isSafeState());

    int request[RESOURCE_TYPES] = {1,0,2};
    allocateResources(request, 1);
    printState();
    printf("\nIs safe? %d\n", isSafeState());

    int request2[RESOURCE_TYPES] = {0,2,0};
    allocateResources(request2, 0);
    printState();
    printf("\nIs safe? %d\n", isSafeState());

    return 0;
}

/*
 * Checks if the system can allocate resources to each thread
 * (up to its maximum) in some order and still avoid a deadlock
 */
int isSafeState(void)
{
    int work[RESOURCE_TYPES];
    for (int index = 0; index < RESOURCE_TYPES; index++)
        work[index] = available[index];

    int finish[THREAD_NUM];
    for (int index = 0; index < THREAD_NUM; index++)
        finish[index] = 0;

    while (!isArrayTrue(finish, THREAD_NUM)) {
        int findOne = 0;
        for (int index = 0; index < THREAD_NUM; index++) {
            int isLessEqualThanNeed = lessEqualThan(need[index], work, RESOURCE_TYPES);
            if(!finish[index] && isLessEqualThanNeed) {
                addArray(work, allocation[index], RESOURCE_TYPES);
                finish[index] = 1;
                findOne = 1;
            }
        }

        if (!findOne)
            return 0;
    }

    return 1;
}

/* Checks if all items in array are true */
int isArrayTrue(int a[], int size)
{
    for (int index = 0; index < size; index++) {
        if(a[index] != 1)
            return 0;
    }

    return 1;
}

/* Compares values of each index of two arrays */
int lessEqualThan(int *a, int *b, int size)
{
    for (int index = 0; index < size; index++) {
        if (a[index] > b[index])
            return 0;
    }

    return 1;
}

/* Aloca recursos */
void allocateResources(int *request, int process)
{
    subArray(available, request, RESOURCE_TYPES);
    subArray(need[process], request, RESOURCE_TYPES);
    addArray(allocation[process], request, RESOURCE_TYPES);
}

/* Soma dois arrays */
void addArray(int *a, int *b, int size)
{
    for (int index = 0; index < size; index++)
        a[index] += b[index];
}

/* Subtrai dois arrays */
void subArray(int *a, int *b, int size)
{
    for (int index = 0; index < size; index++)
        a[index] -= b[index];
}

/* Printa estado atual das matrizes/vetor globais */
void printState(void)
{
    printf("\nAvailable\n");
    for (int i = 0; i < RESOURCE_TYPES; i++)
        printf("%d ", available[i]);
    printf("\n");

    printf("\nMax\n");
    for (int i = 0; i < THREAD_NUM; i++) {
        for (int j = 0; j< RESOURCE_TYPES; j++)
            printf("%d ", max[i][j]);

        printf("\n");
    }

    printf("\nAllocation\n");
    for (int i = 0; i < THREAD_NUM; i++) {
        for (int j = 0; j < RESOURCE_TYPES; j++)
            printf("%d ", allocation[i][j]);

        printf("\n");
    }

    printf("\nNeed\n");
    for (int i = 0; i < THREAD_NUM; i++) {
        for (int j = 0; j< RESOURCE_TYPES; j++)
            printf("%d ", need[i][j]);

    printf("\n");
    }
}