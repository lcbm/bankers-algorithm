#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N_THREADS 5
#define N_RES 3

/*
    Estruturas de dados mokadas
*/
int allocation[N_THREADS][N_RES] = {
    {0,1,0},
    {2,0,0},
    {3,0,2},
    {2,1,1},
    {0,0,2}

};

int max[N_THREADS][N_RES] = {
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}

};
int need[N_THREADS][N_RES] = {
    {7,4,3},
    {1,2,2},
    {6,0,0},
    {0,1,1},
    {4,3,1}
};

int available[N_RES]={
    3,
    3,
    2
};





/*
    Checa se os valores de um array sao "menores" que o do outro
 */


int lessEqualThan(int * a, int * b, int size){
  

 
  
  for(int i = 0; i< size;i++){

      
    if (a[i]> b[i]) return 0;

  }
   
  return 1;
}

/*
    Soma dois arrays
 */

void addArray(int * a, int * b, int size){
    for (int i = 0; i < size; i++){
        a[i]+= b[i];
    }
 
}

/*
    Subtrai dois arrays
 */
void subArray(int * a, int * b, int size){
    for (int i = 0; i < size; i++){
        a[i]-= b[i];
    }
 
}

/*
    Checa se todos os itens de um array sao verdadeiros
 */
int isArrayTrue(int a[],int size){

    for (int i = 0; i < size; i++)
    {
        if(a[i] != 1) return 0 ;
    }
    return 1;
}


/*
    Checa se um determinado estado é seguro
 */
int isSafeState(){
    int finish[N_THREADS] ;

    for (int i = 0; i < N_THREADS; i++)
    {
        finish[i] = 0;
    }


    
    int work[N_RES];
    for (int i = 0; i < N_RES; i++)
    {
        work[i] = available[i];
    }
    
    
    while(!isArrayTrue(finish,N_THREADS)){
        int findOne = 0;
        for(int  i  =0;i<N_THREADS;i++){

            int isLessEqualThanNeed = lessEqualThan(need[i],work,N_RES);


            if(!finish[i] && isLessEqualThanNeed){
                addArray(work,allocation[i],N_RES);
                finish[i] = 1;
                findOne = 1;
            } 
        }
        if(!findOne){
            return 0;
        }
    }
    return 1;

}


/*
    Aloca recursos
 */

void allocateResources(int * request, int process){
    subArray(available,request,N_RES);
    subArray(need[process],request,N_RES);
    addArray(allocation[process],request,N_RES);

}

/* void printState(){
    printf("Allocation\n");
    for (int i = 0; i < N_THREADS; i++)
    {
        for (int j = 0; j < N_RES; j++)
        {
            printf("%d ",allocation[i][j]);
        }
        printf("\n");   
    }
    printf("\n");

    printf("Need\n");
    for (int i = 0; i < N_THREADS; i++)
    {
        for (int j = 0; j< N_RES; j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");   
    }
    printf("\n");

    printf("Max\n");
    for (int i = 0; i < N_THREADS; i++)
    {
        for (int j = 0; j< N_RES; j++)
        {
            printf("%d ",max[i][j]);
        }
        printf("\n");   
    }
    printf("\n");

    printf("Available\n");
    for (int i = 0; i < N_RES; i++)
    {
        printf("%d ",available[i]);
           
    }
    printf("\n");   
} */


/*
    Aplica o exemplo do livro para testar se as solicitacoes de 
    recursos deixarão o sistema em estado nao-seguro
*/
int main(int argc, char const *argv[])
{
    
    printf("Is safe? %d\n",isSafeState());
    
    int request[N_RES] = {1,0,2};

    allocateResources(request,1);

    printf("Is safe? %d\n",isSafeState());
   
    int request2[N_RES] = {0,2,0};

    allocateResources(request2,0);

    printf("Is safe? %d\n",isSafeState());
   
    return 0;
}
