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
#define FILE_NAME "fileName.txt"
#define N_THREADS 1        /* number of threads to be created */
#define N_RESOURCES 5 /* number of resource types */
#define MAX_TIME_SLEEP 5   /* Max number thread can Sleep */
#define FILE_NAME "./file.txt"

/* global variables */
int available[N_RESOURCES];             /* Quanto de cada recurso o sistema tem disponivel */
int allocated[N_THREADS][N_RESOURCES];  /* Quanto de cada recurso cada processo reservou p/ uso*/
int max[N_THREADS][N_RESOURCES];        /* Quanto de cada recurso cada processo pode reservar */
int need[N_THREADS][N_RESOURCES];       /* Quanto de cada recurso cada processo precisa */
int numTest;                            /* a */

/* prototype functions */
void createThreads(pthread_t tid, void* runner);
void joinThreads(pthread_t tid, void* runner);
void *runner(void * arg);
int randomNum(int max);
int timeSleeping(); // Gera tempo em que a thread vai dormir
void calculateNeed();
void sleepResources(int time, int resource, int index, int thread);

// Function: Reads the file and return the matrix containg the max number of resources for each thread for each resource type
int **getMaxDemandFromFile();

//Function: prints a bidimentional array for testing purposes
void printMatrix();

int main(int argc, const char * argv[]) {
  srand((unsigned int)time(NULL)); /* seed random number generator */
  max = getMaxDemandFromFile();
  pthread_t tid;
  createThreads(tid, runner);
  joinThreads(tid, runner);
  return 0;
}

void *runner(void * arg){
  // Inicializar o struct da thread
  // Gerar os números randômicos

  pthread_exit(NULL);
}

void createThreads(pthread_t tid, void* runner){
  printf("Creating threads...");

  for(int threadsCreated = 0; threadsCreated < N_THREADS; threadsCreated++) {
    pthread_create(&tid, NULL, runner, NULL);
    printf("Threads created: %d\n", threadsCreated + 1);
  }
}

void joinThreads(pthread_t tid, void* runner){
  printf("Joining threads...");

  for(int threadsJoined = 0; threadsJoined < N_THREADS; threadsJoined++) {
    pthread_join(tid, NULL);
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
