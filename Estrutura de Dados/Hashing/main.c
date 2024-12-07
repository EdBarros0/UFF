#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 11;

typedef struct Aluno{
    int matricula;
    char nome [50];
    char email [100];
    int disponibilidade;
}Aluno;

int hash(int key){
    return key%N;
}

void inicializar(char *ArqNome){
    FILE *arq = fopen(ArqNome, "wb");
    Aluno a;
    int i;
    a.disponibilidade=1;
    for(i=0;i<N;i++)
        fwrite(&a, sizeof(Aluno), 1, arq);
    fclose(arq);
}

int AcharPosicao(char *ArqNome, int x){
    int pos = hash(x);
    Aluno a;
    FILE *arq = fopen(ArqNome, "rb");
    fseek(arq,pos*sizeof(Aluno),SEEK_SET);
    fread(&a,sizeof(Aluno), 1, arq);
    while(a.disponibilidade == 0){
        pos=(pos+1)%N;
        fseek(arq,pos*sizeof(Aluno),SEEK_SET);
        fread(&a,sizeof(Aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

void inserir(char *ArqNome, int matricula, char *nome, char *email){
    int pos = AcharPosicao(ArqNome,matricula);
    FILE *arq = fopen(ArqNome, "r+b");
    Aluno a;
    a.matricula = matricula;
    strcpy(a.nome,nome);
    strcpy(a.email,email);
    a.disponibilidade=0;
    fseek(arq,pos*sizeof(Aluno), SEEK_SET);
    fwrite(&a,sizeof(Aluno), 1, arq);
    fclose(arq);
}

int AcharAluno(char *ArqNome, int x){
    int pos = hash(x);
    Aluno a;
    FILE *arq = fopen(ArqNome, "rb");
    if (arq == NULL){
        printf("\nErro na abertura arquivo");
        exit(1);
    }
    fseek(arq,pos*sizeof(Aluno),SEEK_SET);  //erro
    fread(&a,sizeof(Aluno), 1, arq);
    while(a.disponibilidade == 0){
        if(a.matricula == x){
            fclose(arq);
            return pos;
        }
        pos=(pos+1)%N;
        fseek(arq,pos*sizeof(Aluno),SEEK_SET);
        fread(&a,sizeof(Aluno), 1, arq);
    }
    fclose(arq);
    return -1;
}

void ImprimeAluno(char *ArqNome, int x){
    int pos = AcharAluno(ArqNome,x);
    FILE *arq = fopen(ArqNome, "rb");
    Aluno a;
    if(pos>=0){
    fseek(arq,pos*sizeof(Aluno),SEEK_SET);
    fread(&a,sizeof(Aluno), 1, arq);
    printf("Dados Do Aluno\n Matricula: %d\n Nome: %s\n Email:%s",a.matricula,a.nome,a.email);
    }else
        printf("O Aluno não existe ou ainda nao foi inserido!\n");
    fclose(arq);
}

void ImprimeTabela(char *ArqNome){
    
    FILE *arq = fopen(ArqNome, "rb");
    for(int i=0;i<N;i++){
        Aluno a;
       fseek(arq,i*sizeof(Aluno),SEEK_SET); 
       fread(&a,sizeof(Aluno), 1, arq);
       if(a.disponibilidade == 0){
        printf("%d- Dados Do Aluno\n Matricula: %d\n Nome: %s\n Email:%s\n\n",i,a.matricula,a.nome,a.email);
       }else{
        printf("%d- Espaco Livre\n\n",i);
       }
    }
       fclose(arq);
}

int main(){
    char arq1[50];
    printf("\x1B[2J\x1b[H");
    printf("Bem-Vindo ao Simulador da Tabela de Dispercao/Hashing\n\n");
    printf("   Digite o nome do arquivo que deseja efetuar a simulcao: ");
    scanf("%s", arq1);
    inicializar(arq1);
    while(1){
        char arq2[50];
        strcpy(arq2,arq1);
        int op;
        printf("\x1B[2J\x1b[H");
        printf("   Qual operacao deseja realizar?\n    1- Inserir um novo aluno\n    2- Imprimir informacoes de um aluno\n    3- Imprimir tabela de dispercao(tabela hash)\n    4- Sair\n\n");
        printf("   Digite aqui: ");
        scanf("%d", &op);
        if(op == 1){
            int matricula;
            char nome[50], email[100];
            char confirm[1];
            printf("\x1B[2J\x1b[H");
            printf("Digite os dados do aluno\n");
            printf("\nMatricula: ");
            scanf("%d", &matricula);
            printf("\nNome: ");
            getchar();
            fgets(nome,50,stdin);
            nome[strcspn(nome,"\n")] = 0;
            printf("\nEmail: ");
            scanf("%s", email);
            inserir(arq1,matricula,nome,email);
            printf("\x1B[2J\x1b[H");
            printf("Aluno Inserirdo com succeso!!");
            printf("\n\n\nDigite 1 para voltar: ");
            scanf("%s", confirm);
        }
        if(op == 2){
          int matricula;
          char confirm[1];  
          printf("\x1B[2J\x1b[H");
          printf("\nDigite a matricula: ");
          scanf("%d", &matricula);
          ImprimeAluno(arq1,matricula);
          printf("\n\n\nDigite 1 para voltar: ");
          scanf("%s", confirm);
        }
        if(op == 3){
            //char confirm[2];
            system("cls");
            system("clear");
            //printf("\x1B[2J\x1b[H");
            ImprimeTabela(arq1);
            printf("\n\n\nDigite 1 para voltar: ");
            //scanf("%s", confirm);
            system("PAUSE");
        }
        if(op == 4){
            exit(1);
        }
        strcpy(arq1,arq2);
    }
}