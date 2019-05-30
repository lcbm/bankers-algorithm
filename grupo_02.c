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
#include <pthread.h>
// #include <semaphore.h>
#include <sys/wait.h> /* required by some linux systems */

// Testar com argv
#define N_THREADS 1 /* number of threads to be created */
#define N_RESOURCE_TYPES 5 /* number of resource types */

/* global variables */
int available[N_RESOURCE_TYPES];             /* Quanto de cada recurso o sistema tem disponivel */
int allocation[N_THREADS][N_RESOURCE_TYPES]; /* Quanto de cada recurso cada processo reservou p/ uso*/
int max[N_THREADS][N_RESOURCE_TYPES];        /* Quanto de cada recurso cada processo pode reservar */
int need[N_THREADS][N_RESOURCE_TYPES];       /* Quanto de cada recurso cada processo precisa */

/* prototype functions */
void createThreads(pthread_t tid, void* runner);
void joinThreads(pthread_t tid, void* runner);
void *runner(void * arg);

int main(int argc, const char * argv[]) {
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
