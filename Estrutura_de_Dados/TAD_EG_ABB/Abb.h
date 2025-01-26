#ifndef ABB_H
#define ABB_H

typedef struct arvore *Arvore;

Arvore inicializar(void);
Arvore destruir(Arvore a);
void inserir (Arvore* a, int chave, void *objeto, int sizeObj);
int remover (Arvore* a, int chave, void *objeto, int sizeObj);
int existe (Arvore a, int chave);
int buscar (Arvore a, int chave, void *objeto, int sizeObj);
void imprimir (Arvore a);


#endif