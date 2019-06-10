/*
 * Institution: CESAR School
 * Course     : Computer Science 2018.1
 * Discipline : Software Insfrastructure (Operating Systems)
 * Professor  : Erico Teixeira
 * Reference  : Operating System Concepts (10th Edition) by Abraham Silberschatz et al.
 *
 * Evaluation : 04.2 @ May 30th/June 06th, 2019
 * Exercise 03: Banker's Algorithm
 * Authors    : [Group 02] Arthur Carlos, João Victor Pessoa, Jonathan Coutinho, Leonardo Melo e Pedro Henrique
 *
 * Compiling  : gcc -o grupo_02 grupo_02.c -lm -lpthread
 * Running    : ./grupo_02
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
// #include <semaphore.h>
#include <sys/wait.h> /* required by some linux systems */

// Testar com argv
#define FILE_NAME "threads.txt"
int  N_THREADS;         /* number of threads to be created */
int  N_RESOURCES = 3;      /* number of resource types */
int  MAX_TIME_SLEEP;   /* Max number thread can Sleep */

/* global variables */
int * available;   /* Quanto de cada recurso o sistema tem disponivel */
int ** allocated;  /* Quanto de cada recurso cada processo reservou p/ uso*/
int ** max;        /* Quanto de cada recurso cada processo pode reservar */
int ** need;       /* Quanto de cada recurso cada processo precisa */

/* Prototype functions */
void createThreads(pthread_t * tid, void* runner){
void joinThreads(pthread_t tid, void* runner);
void *runner(void * arg);
int randomNum(int max);
int timeSleeping();
void calculateNeed();
void sleepResources(int time, int resource, int index, int thread);
int **getMaxDemandFromFile();
int isSafeState(void);
int isArrayTrue(int a[], int size);
int lessEqualThan(int *a, int *b, int size);
void allocateResources(int *request, int process);
void addArray(int *a, int *b, int size);
void subArray(int *a, int *b, int size);
void printState(void);
void printMatrix();



int main(int argc, const char * argv[]) {
  srand((unsigned int)time(NULL)); /* seed random number generator */
  max = getMaxDemandFromFile();


  N_THREADS = sizeof(max)/sizeof(int)*sizeof(N_RESOURCES);


  pthread_t pids[N_THREADS];

  createThreads(pids, runner);

  /* printState();
  printf("\nIs safe? %d\n", isSafeState());

  int request[N_RESOURCES] = {1,0,2};
  allocateResources(request, 1);
  printState();
  printf("\nIs safe? %d\n", isSafeState());

  int request2[N_RESOURCES] = {0,2,0};
  allocateResources(request2, 0);
  printState();
  printf("\nIs safe? %d\n", isSafeState()); */

  joinThreads(tid, runner);
  return 0;
}

void *runner(void * arg){
  // Inicializar o struct da thread
  // Gerar os números randômicos

  pthread_exit(NULL);
}

void createThreads(pthread_t * tid, void* runner){
  printf("Creating threads...");

  for(int threadsCreated = 0; threadsCreated < N_THREADS; threadsCreated++) {
    pthread_create(&tid[threadsCreated], NULL, runner, NULL);
    printf("Threads created: %d\n", threadsCreated + 1);
  }
}

void joinThreads(pthread_t * tid, void* runner){
  printf("Joining threads...");

  for(int threadsJoined = 0; threadsJoined < N_THREADS; threadsJoined++) {
    pthread_join(tid[threadsJoined], NULL);
    printf("Threads joined: %d\n", threadsJoined + 1);
  }
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
    for(i = 0; i < N_RESOURCES; i++){
        matrixMaxDemand[i] = calloc(N_RESOURCES, sizeof(int));
    }

    i = 0;
    while (i < N_THREADS || !feof(fp))
    {
        j = 0;
        while (j < N_RESOURCES || !feof(fp))
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
        for( j = 0; j < N_RESOURCES; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void sleepResources(int time, int resource, int index, int thread){
  // Alocar o index do recurso e o index da thread
  // Pegar o recurso e alocar em uma variavel e liberar a thread
  // Subtrair o recurso de available
  // Adicionar o recurso no allocated
  // Fork -> Criar o filho e liberar o pai
  //  > sleep no time passado pela thread
  //  > Adicionar o recurso no available -> "A thread ja usou um recurso"
  //  > Subtrair de allocated
}

/* not done yet */
void forkThis(){
  printf("Hello from parent process!\n");
  pid_t pid = fork();
  /* child process will execute the code below */

  if (pid < 0){
    printf("ERROR\n");
  } else if (pid == 0){
    printf("Hello from child process!\n");
    /* do some work here */
    printf("Bye from child process!\n");
    return 0;
  } else {
    printf("Parent process is Waiting for child process!\n");
    wait(NULL);
  }
}

/*
 * Checks if the system can allocate resources to each thread
 * (up to its maximum) in some order and still avoid a deadlock
 */
int isSafeState(void)
{
    int work[N_RESOURCES];
    for (int index = 0; index < N_RESOURCES; index++)
        work[index] = available[index];

    int finish[N_THREADS];
    for (int index = 0; index < N_THREADS; index++)
        finish[index] = 0;

    while (!isArrayTrue(finish, N_THREADS)) {
        int findOne = 0;
        for (int index = 0; index < N_THREADS; index++) {
            int isLessEqualThanNeed = lessEqualThan(need[index], work, N_RESOURCES);
            if(!finish[index] && isLessEqualThanNeed) {
                addArray(work, allocated[index], N_RESOURCES);
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
    subArray(available, request, N_RESOURCES);
    subArray(need[process], request, N_RESOURCES);
    addArray(allocated[process], request, N_RESOURCES);
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
    for (int i = 0; i < N_RESOURCES; i++)
        printf("%d ", available[i]);
    printf("\n");

    printf("\nMax\n");
    for (int i = 0; i < N_THREADS; i++) {
        for (int j = 0; j< N_RESOURCES; j++)
            printf("%d ", max[i][j]);

        printf("\n");
    }

    printf("\nallocated\n");
    for (int i = 0; i < N_THREADS; i++) {
        for (int j = 0; j < N_RESOURCES; j++)
            printf("%d ", allocated[i][j]);

        printf("\n");
    }

    printf("\nNeed\n");
    for (int i = 0; i < N_THREADS; i++) {
        for (int j = 0; j< N_RESOURCES; j++)
            printf("%d ", need[i][j]);

    printf("\n");
    }
}