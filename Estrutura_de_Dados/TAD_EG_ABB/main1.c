#include "Abb.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Arvore a = inicializar();
    for(int i =0;i <= 5;i++){
        inserir(&a,i,&i,sizeof(int));
    }
    int x = 4;
    inserir(&a,x,&x,sizeof(int));
    //exit(1);
    imprimir(a);
    remover(&a,1,&x,sizeof(int));
    imprimir(a);
    if(buscar(a,7,&x,sizeof(int))==1){
        printf("Achou o numero %d\n", x);
    }else
        printf("O numero buscado nao existe!\n\n");
    if(existe(a,7)==1){
        printf("\n O numero procurado existe\n");
    }else 
        printf("\n O numero procurado nao existe\n");
}
