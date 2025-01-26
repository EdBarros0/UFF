#include "Abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct aluno{
    int matricula;
    char nome[20];
    //int anoDeIngresso;
}Aluno;


int main()
{
    Arvore a = inicializar();
    Aluno primeiro;
    primeiro.matricula=10;
    strcpy(primeiro.nome, "Oscar");
    Aluno segundo;
    segundo.matricula=5;
    strcpy(segundo.nome, "Armando");
    Aluno terceiro;
    terceiro.matricula=19;
    strcpy(terceiro.nome, "Livia");
    Aluno quarto;
    quarto.matricula=12;
    strcpy(quarto.nome, "Patricia");
    Aluno quinto;
    quinto.matricula=6;
    strcpy(quinto.nome, "Samuel");
    inserir(&a,primeiro.matricula,&primeiro,sizeof(Aluno));
    inserir(&a,segundo.matricula,&segundo,sizeof(Aluno));
    inserir(&a,terceiro.matricula,&terceiro,sizeof(Aluno));
    inserir(&a,quarto.matricula,&quarto,sizeof(Aluno));
    inserir(&a,quinto.matricula,&quinto,sizeof(Aluno));

    imprimir(a);

    Aluno x;
    remover(&a,terceiro.matricula,&x,sizeof(Aluno));

    imprimir(a);

    Aluno y;
    if(buscar(a,10,&y,sizeof(Aluno)) == 1){
        printf("O Aluno buscado eh:\nMatricula:%d\nNome:%s",y.matricula,y.nome);
    }else
        printf("O Aluno buscado nao foi encontrado!!\n");
    if(existe(a,20) == 1){
        printf("\n\nO Aluno existe!\n");
    }else 
        printf("\n\nO Aluno nao existe!\n");

    destruir(a);

    return 0;
}



