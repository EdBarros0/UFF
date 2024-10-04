#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore{
    int info;
    struct arvore* esq;
    struct arvore* dir;
}arvore;

arvore* LerArvore(FILE* arq){
    char c;
    int n;

    fscanf(arq,"%c", &c);
    fscanf(arq,"%d", &n);

    if(n == -1){
        fscanf(arq,"%c", &c);
        return NULL;
    }else{
        arvore* a = (arvore*)malloc(sizeof(arvore));
        a->info = n;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq,"%c", &c);
        return a;
    }
}

void ImpPreArvore(arvore* a){
    if(a != NULL){
        printf("%d ", a->info);
        ImpPreArvore(a->esq);
        ImpPreArvore(a->dir);
    }
}

void ImpEmArvore(arvore* a){
    if(a != NULL){
        ImpEmArvore(a->esq);
        printf("%d ", a->info);
        ImpEmArvore(a->dir);
    }
}

void ImpPosArvore(arvore* a){
    if(a != NULL){
        ImpPosArvore(a->esq);
        ImpPosArvore(a->dir);
        printf("%d ", a->info);
    }
}

bool ExisteX (arvore* a, int x){
    if(a==NULL)
        return 0;
    else if(a->info == x)
        return 1;
    else{
        return ExisteX(a->esq,x) || ExisteX(a->dir,x) ;
    }
}

int ContElementos(arvore* a){
    if(a == NULL)
        return 0;
    else{
        return ContElementos(a->esq) + ContElementos(a->dir) + 1;
    }
}

void ImpFolhas(arvore* a){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL){
            printf("%d ", a->info);
        }
        ImpFolhas(a->esq);
        ImpFolhas(a->dir);
    }
}
int main()
{
    arvore* a = (arvore*)malloc(sizeof(arvore));
    int menu = 0;
    while (menu != 6)
    {
        printf("\x1B[2J\x1b[H");  //Comando que eu aprendi com um professor que tive aula na UFJF para limpar a tela
        printf("Oque Deseja Fazer?\n\n");
        printf("1- Ler uma Arvore\n2- Imprimir Arvore\n3- Verificar Elemento\n4- Tamanho Da Arvore\n5- Imprimir Folhas\n6- Sair\n\nDigite Aqui: ");
        scanf("%d", &menu);

        if(menu == 1){
            printf("\x1B[2J\x1b[H");
            FILE* arq = fopen("Arvore.txt", "rt");
            a = LerArvore(arq);
            fclose(arq);
            printf("Arquivo Lido com sucesso!\n\n");
            printf("\n\n1- Voltar ao menu\n6- Sair\n\nDigite Aqui: ");
            scanf("%d", &menu);
        }
        if(menu == 2){
            int m;
            printf("\x1B[2J\x1b[H");
            printf("Qual forma de impressão voce quer?\n\n");
            printf("1- Pre-ordem \n2- Em-ordem \n3- Pos-ordem\n\nDigite Aqui: ");
            scanf("%d", &m);
            printf("\x1B[2J\x1b[H");
            if(m == 1){
                printf("Pre-Ordem:\n");
                ImpPreArvore(a);
            }else if(m == 2){
                printf("Em-Ordem:\n");
                ImpEmArvore(a);
            }else if(m == 3){
                printf("Pos-Ordem:\n");
                ImpPosArvore(a);
            }
            printf("\n\n1- Voltar ao menu\n6- Sair\n\nDigite Aqui: ");
            scanf("%d", &menu);
        }
        if(menu == 3){
            int x;
            printf("\x1B[2J\x1b[H");
            printf("Qual elemento voce deseja que seja verificado a exitencia?\n\nDigite aqui: ");
            scanf("%d", &x);
            printf("\x1B[2J\x1b[H");
            if(ExisteX(a, x))
                printf("O elemento %d eh um no da arvore!", x);
            else
                printf("O elemento %d nao esta presente na arvore!", x);
            printf("\n\n1- Voltar ao menu\n6- Sair\n\nDigite Aqui: ");
            scanf("%d", &menu);
        }
        if(menu == 4){
            printf("\x1B[2J\x1b[H");
            printf("A arvore tem %d elementos!", ContElementos(a));
            printf("\n\n1- Voltar ao menu\n6- Sair\n\nDigite Aqui: ");
            scanf("%d", &menu);
        }
        if(menu == 5){
            printf("\x1B[2J\x1b[H");
            printf("Folhas da arvore\n");
            ImpFolhas(a);
            printf("\n\n1- Voltar ao menu\n6- Sair\n\nDigite Aqui: ");
            scanf("%d", &menu);
        }
    }
    free(a);
    printf("\x1B[2J\x1b[H");
    printf("Programa Fechado!\n");
    return 0;
}