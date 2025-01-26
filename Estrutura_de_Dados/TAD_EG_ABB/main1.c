#include "Abb.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Arvore a = inicializar();
    int x=0;
    while(1){
        printf("Digite um numero a ser implementado na arvore(-1 para de adicionar):");
        scanf("%d",&x);
        if(x == -1){
            break;
        }else{
            inserir(&a,x,&x,sizeof(int));
        }
    }
    imprimir(a);
    x=0;
    printf("Digite um numero a ser removido:");
    scanf("%d",&x);
    remover(&a,x,&x,sizeof(int));
    imprimir(a);
    exit;
    int y;
    if(buscar(a,6,&y,sizeof(int))==1){  //BUSCANDO O NUMERO 7
        printf("Achou o numero %d\n", y);
    }else
        printf("O numero buscado nao existe!\n\n");
    if(existe(a,5)==1){                 //EXISTE O NUMERO 5?
        printf("\n O numero procurado existe\n");
    }else 
        printf("\n O numero procurado nao existe\n");

    destruir(a);
}
