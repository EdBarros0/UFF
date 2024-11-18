#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct arvore{  //Estrutura da Arvore
    int info;
    struct arvore* esq;
    struct arvore* dir;
}arvore;

arvore* LerArvore(FILE* arq){  //Função De Leitura da Arvore(mesma função explicada na aula)
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

int altura(arvore *a){
    if(a == NULL)
        return 0;
    int tam_esq = altura(a->esq);
    int tam_dir = altura(a->dir);
    if(tam_esq > tam_dir)
        return 1+tam_esq;
    else   
        return 1+tam_dir;
}

void ImpPreArvore(arvore* a){  //Impreção Pre-ordem da Arvore
    if(a != NULL){
        printf("%d ", a->info);  //Print antes de chamar a recursividade
        ImpPreArvore(a->esq);
        ImpPreArvore(a->dir);
    }
}

void ImpEmArvore(arvore* a){  //Impreção Em-ordem da Arvore
    if(a != NULL){
        ImpEmArvore(a->esq);
        printf("%d ", a->info);  //Print entre as chamadas da recursividade
        ImpEmArvore(a->dir);
    }
}

void ImpPosArvore(arvore* a){  //Impreção Pos-ordem da Arvore
    if(a != NULL){
        ImpPosArvore(a->esq);
        ImpPosArvore(a->dir);
        printf("%d ", a->info);  //Print após a chamada da recursividade
    }
}

void ImpNivelArvore(arvore * a, int cont, int n){
    if(a != NULL){
        if(cont == n)
            printf("%d ", a->info);
        ImpNivelArvore(a->esq,cont+1,n);
        ImpNivelArvore(a->dir,cont+1,n);
    }
}

bool ExisteX (arvore *a, int x){
    if(a==NULL)   
        return 0;
    else if(a->info == x)
        return 1;
    else{
        if(a->info > x){
            return ExisteX(a->esq, x);
        }else{
            return ExisteX(a->dir, x);
            
        }
    }

}

void ImpNivelNo(arvore *a, int cont, int no ){
    if(a != NULL){
        if(no == a->info){
            printf("Existe esse noh no Nivel: %d\n", cont);
        }
        if(a->info > no){
            ImpNivelNo(a->esq,cont+1,no);
        }else{
            ImpNivelNo(a->dir,cont+1,no);
        }
    }
}

void ImpFolhasMenor(arvore *a, int x){
    if(a != NULL){
        if(a->info < x){
            if(a->esq == NULL && a->dir == NULL){
                printf("%d  ", a->info);
            }else{
                ImpFolhasMenor(a->esq, x);
                ImpFolhasMenor(a->dir, x);
            }
        }else
            ImpFolhasMenor(a->esq, x);
    }
}

//ROTAÇÂO
arvore *RotacaoEsqSimples(arvore *p)
{
arvore *b = p->dir;
p->dir = b->esq;
b->esq = p;
return b;
}

arvore *RotacaoDirSimples(arvore *p)
{
arvore *b = p->esq;
p->esq = b->dir;
b->dir = p;
return b;
}

arvore *RotacaoEsqDupla(arvore *p)
{
p->dir = RotacaoDirSimples(p->dir);
p = RotacaoEsqSimples(p);
return p;
}

arvore *RotacaoEsq(arvore *p)
{
int he = altura(p->esq);
int hd = altura(p->dir);
if (fabs(hd - he) > 1)
{
arvore *b = p->dir;
he = altura(b->esq);
hd = altura(b->dir);
if (he > hd)
p = RotacaoEsqDupla(p);
else
p = RotacaoEsqSimples(p);
}
return p;
}

arvore *RotacaoDirDupla(arvore *p)
{
p->esq = RotacaoEsqSimples(p->esq);
p = RotacaoDirSimples(p);
return p;
}
arvore *RotacaoDir(arvore *p)
{
int he = altura(p->esq);
int hd = altura(p->dir);
if (fabs(hd - he) > 1)
{
arvore *b = p->esq;
he = altura(b->esq);
hd = altura(b->dir);
if (hd > he)
p = RotacaoDirDupla(p);
else
p = RotacaoDirSimples(p);
}
return p;
}



//INSERIR  ELEMENTO
arvore *Inserir(arvore *a, int x)
{
if(a == NULL) //Momento de inserir
{
a = (arvore*)malloc(sizeof(arvore));
a->info = x;
a->esq = NULL;
a->dir = NULL;
}
else
{
if (x <= a->info)
{
a->esq = Inserir(a->esq,x);
a = RotacaoDir(a);
}
else
{
a->dir = Inserir(a->dir,x);
a = RotacaoEsq(a);
}
}
return a;
}

//REMOVER ELEMENTO
arvore *Remover(arvore *a, int x)
{
if(a != NULL)
{
if(a->info == x)
{
//Verificar se é folha
if(a->esq == NULL && a->dir == NULL)
{
free(a);
return NULL;
}
//Verificar se um dos filhos é nulo
else if (a->esq == NULL || a->dir == NULL)
{
arvore *aux;

if(a->esq == NULL)
aux = a->dir;
else
aux = a->esq;
free(a);
return aux;
}
//Nenhum filho nulo
else
{
arvore *maiorEsq = a->esq;
while (maiorEsq->dir != NULL)
maiorEsq = maiorEsq->dir;
a->info = maiorEsq->info;
a->esq = Remover(a->esq,a->info);
a = RotacaoEsq(a);
}
}
else if (x < a->info)
{
a->esq = Remover(a->esq, x);
a = RotacaoEsq(a);
}
else
{
a->dir = Remover(a->dir, x);
a = RotacaoDir(a);
}
}
return a;
}


int main()  //Main
{
    arvore* a = (arvore*)malloc(sizeof(arvore)); //Cria uma estrutura(arvore) com o nome "a"
    int menu = 0;
    while (menu != 8) //Inicio do loop para manter o programa aberto e ser possivel fazer multiplas operação sem fecha-lo
    {                 //Uso a propria variavel para a escolha de operação, o que vai me permitir controlar mais facil o fechamento da lista ao decorrer do programa
        printf("\x1B[2J\x1b[H");  //Comando que eu aprendi com um professor que tive aula na UFJF para limpar a tela
        printf("Oque Deseja Fazer?\n\n");
        printf("1- Ler uma Arvore\n2- Imprimir Arvore\n3- Verificar Elemento\n4- Imprimir nivel de um noh\n5- Imprimir folhas menores que x\n6- inserir um noh na arvore\n7- remover um noh da arvore\n8- Sair\n\nDigite Aqui: "); //Menu principal de escolha
        scanf("%d", &menu); //A leitura de numero mandara para o if correspondente a operação

        if(menu == 1){  //Leitura da arvore
            printf("\x1B[2J\x1b[H");  //Limpa a tela
            printf("Digite o nome do arquivo que deseja ler: ");
            char string[100]; //Cria uma string de tamanho 100 para colocar o nome do arquivo que contem a arvore
            scanf("%s",string);  //Digita o nome do arquivo contendo seu tipo(".txt", ".docs", etc) 
            FILE* arq = fopen(string, "rt"); // Abre o arquivo no modo leitura
            if(arq == NULL){ //Verifica a integridade do arquivo
                printf("Impossivel Ler o Arquivo!!\n"); //Diz que não foi possivel ler o arquivo caso o arquivo seja NULL
                return -1;  //Fecha o programa
            }  
            a = LerArvore(arq);   //Chama a função para ler o arquivo e armazena na estrutura(arvore) "a"
            fclose(arq); //Fecha o arquivo, pois ja foi usado
            printf("\n\nArquivo Lido com sucesso!\n\n");  //Mostra na tela que foi possivel ler o arquivo com succeso
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 2){  //Impreção da arvore
            int m;
            printf("\x1B[2J\x1b[H"); //Limpa a tela
            printf("Qual forma de impressão voce quer?\n\n"); 
            printf("1- Pre-ordem \n2- Em-ordem \n3- Pos-ordem\n4- Em Largura\n\nDigite Aqui: "); //Escolha de qual impressão voce quer
            scanf("%d", &m);
            printf("\x1B[2J\x1b[H"); //Limpa a tela
            if(m == 1){  //Imprime a arvore em Pre-ordem
                printf("Pre-Ordem:\n");
                ImpPreArvore(a);
            }else if(m == 2){  //Imprime a arvore em Em-ordem
                printf("Em-Ordem:\n");
                ImpEmArvore(a);
            }else if(m == 3){  //Imprime a arvore em Pos-ordem
                printf("Pos-Ordem:\n");
                ImpPosArvore(a);
            }else if(m == 4){
                printf("Em Largura:\n");
                for(int i=0;i<altura(a);i++){
                    ImpNivelArvore(a,0,i);
                    printf("\n");
                }
            }
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 3){  //Verifica se x elemento esta na arvore
            int x;
            printf("\x1B[2J\x1b[H"); //Limpa a tela
            printf("Qual elemento voce deseja que seja verificado a exitencia?\n\nDigite aqui: "); //Pede para digitar o elemento que deseja ser verificado
            scanf("%d", &x);
            printf("\x1B[2J\x1b[H"); //Limpa a tela
            if(ExisteX(a, x)) //Verifica se o elemento esta na arvore
                printf("O elemento %d eh um no da arvore!", x); //Imprime uma mensagem dizendo que esta na arvore
            else
                printf("O elemento %d nao esta presente na arvore!", x); //Se nao, imprime uma mensagem dizendo que nao foi encontrado na arvore
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 4){ 
            int no;
            printf("\x1B[2J\x1b[H");
            printf("Digite o Noh que deseja procurar: ");
            scanf("%d",&no);
            printf("\x1B[2J\x1b[H");
            ImpNivelNo(a,0,no);
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 5){  
            int x;
            printf("\x1B[2J\x1b[H");
            printf("Diga um valor para x: ");
            scanf("%d", &x);
            printf("\x1B[2J\x1b[H");
            printf("As folhas menores que %d são:  ", x);
            ImpFolhasMenor(a, x);
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);  
        }
        if(menu == 6){
            int x;
            printf("\x1B[2J\x1b[H");
            printf("Digite o valor que deseja incluir na arvore: ");
            scanf("%d", &x);
            a = Inserir(a, x);
            printf("\x1B[2J\x1b[H");
            printf("Elemento Incluido!!\n\n");
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 7){
            int x;
            printf("\x1B[2J\x1b[H");
            printf("Digite o valor que deseja excluir da arvore: ");
            scanf("%d", &x);
            a = Remover(a, x);
            printf("\x1B[2J\x1b[H");
            printf("Elemento Excluido\n\n");
            printf("\n\n1- Voltar ao menu\n8- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        
            
    }
    free(a); //Libera a memoria alocada para "a"
    printf("\x1B[2J\x1b[H"); //Limpa a tela
    printf("Programa Fechado!\n"); //Imprime uma mensagem dizendo que o programa fechou
    return 0;
}