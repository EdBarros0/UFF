#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAXSIZE 4

struct fila{
   int data[MAXSIZE];  // Vetor para armazenar os elementos da fila
   int n;               // Número de elementos inseridos
   int first;           // Primeiro elemento da fila
   int end;             // Final da fila (próxima posição disponível)
};

Fila inicializar(){
    Fila q = (Fila)malloc(sizeof(struct fila));
    q->n = 0;
    q->first = 0;
    q->end = 0;
    return q;
}

Fila Destruir(Fila q){
    free(q);
    return NULL;
}

bool vazia(Fila q){
   if (q->n == 0)
		return 1;
	else
		return 0;
   //return q->n == 0 ? 1 : 0;
}

int enqueue(Fila q, int x){
   // Certifica-se de que há espaço disponível.
   if(q->n >= MAXSIZE)
    return 0;

   // Coloca o elemento no final da fila.
   q->data[q->end] = x;
   // Incrementa a quantidade de elementos inseridos na fila.
   q->n++;

   // Atualiza o fim da fila.
   q->end = (q->end+1)%MAXSIZE;
   return 1;
}

int dequeue(Fila q, int *x){
   // Certifica-se de que a fila não está vazia.
   if(vazia(q) == 1)
    return 0;

   // Obtém o valor no início da fila.
   *x = q->data[q->first];

   // Decrementa a quantidade de elementos inseridos na fila.
   q->n--;

   // Atualiza a posição do primeiro elemento da fila.
   q->first = (q->first+1)%MAXSIZE;

   // Retorna o valor.
   return 1;
}

void Imprimir(Fila q){
    int x;
    Fila j = (Fila)malloc(sizeof(struct fila));
    for(int i =0; i < MAXSIZE;i++){
      j->data[i]= q->data[i];
    }
    j->n = q->n;
    j->first = q->first;
    j->end = q->end;
    printf("\nElementos: ");
	while(!vazia(j)){
        dequeue(j, &x);
    	printf("%d ", x);
   }
   free(j);
}