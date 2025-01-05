#ifndef Fila_H
#define Fila_H

typedef struct fila *Fila;
int enqueue(Fila q, int x);
int dequeue(Fila q, int *x);
void Imprimir(Fila q);
Fila inicializar();
Fila Destruir(Fila p);

#endif