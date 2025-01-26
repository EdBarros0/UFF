#include "Abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct items{
    int chave;
    void *obj;
}Items;


struct arvore{
    Items* item;
    struct arvore* esq;
    struct arvore* dir;
};



Arvore inicializar(){
    Arvore a = (Arvore)malloc(sizeof(Arvore));
    a->item = (Items*)malloc(sizeof(Items));
    a->dir = NULL;
    a->esq = NULL;
    return a;
}

Arvore destruir(Arvore a){
    if(a == NULL){
        return a;
    }else{
        a->esq = destruir(a->esq);
        a->dir = destruir(a->dir);
        free(a->item->obj);
        free(a);
        return NULL;
    }
}

int existe (Arvore a, int chav){
    if(a==NULL)   
        return 0;
    else if(a->item->chave == chav)
        return 1;
    else{
        if(a->item->chave > chav){
            return existe(a->esq, chav);
        }else{
            return existe(a->dir, chav);
            
        }
    }

}

Items* insereItem(int chave, void *objeto, int sizeObj){
    Items* it = (Items*)malloc(sizeof(Items));
    it->obj= (void*)malloc(sizeof(sizeObj));
    memcpy(it->obj, objeto, sizeObj);
    it->chave = chave;
    return it;
}

void inserir(Arvore* a, int chave, void* objeto, int sizeObj) {
    if (*a == NULL) {
        *a = inicializar();
    }
    if((*a)->item->obj == NULL){
        (*a)->item = insereItem(chave, objeto, sizeObj);
        return;
    }else{
        if (chave <= (*a)->item->chave) {
             return inserir(&((*a)->esq), chave, objeto, sizeObj);
        } else {
             return inserir(&((*a)->dir), chave, objeto, sizeObj);
        }
    }
}



int remover(Arvore* a, int chave,  void *objeto, int sizeObj){
    if(a != NULL)
        if((*a)->item->chave == chave){
            if((*a)->esq == NULL && (*a)->dir == NULL){
                free((*a)->item->obj);
                free(*a);
                return 1;
            }else if((*a)->esq == NULL){
                Arvore aux = (*a)->dir;
                free((*a)->item->obj);
                free(*a);
                *a = aux;
                return 1;
                }else if((*a)->dir == NULL){
                Arvore aux = (*a)->esq;
                free((*a)->item->obj);
                free(*a);
                *a = aux;
                return 1;
            }
            else{
                Arvore aux = (*a)->esq;
                while (aux->dir!= NULL)
                    aux = aux->dir;
                    (*a)->item->chave = aux->item->chave;
                    memcpy((*a)->item->obj,objeto,sizeObj);
                    return remover(&(*a)->esq, aux->item->chave,objeto,sizeObj);
                    return 1;
            }
            }else if(chave < (*a)->item->chave)
                return remover(&(*a)->esq, chave, objeto, sizeObj);
            else
                return remover(&(*a)->dir, chave, objeto, sizeObj);
            return 0;
        
}

int buscar(Arvore a, int chave, void *objeto, int sizeObj){
    if(a == NULL){
        return 0;
    }else{
        if(existe(a,chave)==0){
            return 0;
        }else{
            if(chave == a->item->chave){
                memcpy(objeto,a->item->obj, sizeObj);
                return 1;
            }else{
                if(a->item->chave > chave){
                    return buscar(a->esq,chave,objeto,sizeObj);
                }else{
                    return buscar(a->dir,chave,objeto,sizeObj);
                }
            }
        }
    }
}


int altura(Arvore a){
    if(a == NULL)
        return 0;
    int tam_esq = altura(a->esq);
    int tam_dir = altura(a->dir);
    if(tam_esq > tam_dir)
        return 1+tam_esq;
    else   
        return 1+tam_dir;
}


void ImpNivelArvore(Arvore a, int cont, int n){
    if(a != NULL){
        if(cont == n)
            printf("%d ", a->item->chave);
        ImpNivelArvore(a->esq,cont+1,n);
        ImpNivelArvore(a->dir,cont+1,n);
    }
}


void imprimir(Arvore a){
    printf("Em Largura:%d\n", altura(a));
        for(int i=0;i<altura(a);i++){
            ImpNivelArvore(a,0,i);
            printf("\n");
        }
}

