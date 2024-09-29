#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    int info;
    struct Lista *prox;
}Lista;

Lista* inserirFinal(Lista *l, int x){
    if(l==NULL){
        Lista *no=(Lista*)malloc(sizeof(Lista));
        no->info=x;
        no->prox=NULL;
        return no;
    }else{
        l->prox = inserirFinal(l->prox, x);
        return l;
    }
}

int somaElementos(Lista *l){
    if(l==NULL){
        return 0;
    }else{
        return somaElementos(l->prox) + l->info;
    }
}


int contElemento(Lista *l, int x){
    if(l==NULL){
        return 0;
    }else{
        if(l->info == x){
            return contElemento(l->prox, x) + 1;;
        }else{
            return contElemento(l->prox, x);
        }
    }
}

int main()
{
    Lista *l= (Lista*)malloc(sizeof(Lista));
    l = inserirFinal(l, 9);
    l = inserirFinal(l, 10);
    l = inserirFinal(l, 52);
    l = inserirFinal(l, 9);
    l = inserirFinal(l, 80);
    l = inserirFinal(l, 9);
    printf("\n %d", somaElementos(l));
    printf("\n %d", contElemento(l, 9));

    return 0;
}
