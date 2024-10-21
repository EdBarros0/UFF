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

int AlturaArvore(arvore *a){
    if(a == NULL)
        return 0;
    int tam_esq = AlturaArvore(a->esq);
    int tam_dir = AlturaArvore(a->dir);
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

bool ExisteX (arvore* a, int x){  //Função bool(biblioteca stdboo.h) para verificar se existe "x" na arvore
    if(a==NULL)   
        return 0;
    else if(a->info == x)
        return 1;
    else{
        return ExisteX(a->esq,x) || ExisteX(a->dir,x) ;  //Retorna verdadeiro se encontrar um no valido pela direita, ou pela esquerda, ou se haver mais de um no verdadeiro
    }
}

int ContElementos(arvore* a){  //Função para contar quantos elementos tem na arvore
    if(a == NULL)
        return 0;
    else{
        return ContElementos(a->esq) + ContElementos(a->dir) + 1;  //A função passa por toda arvore e em cada no ela soma +1
    }
}

void ImpFolhas(arvore* a){    //Função que imprime as folhas da arvore
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL){  //Faz uma comparação para ver se a "esq" e a "dir" da arvore são nulas, a comparação vem da definição de folha
            printf("%d ", a->info);   //Imprime o no que foi verificado corretamente a cima
        }
        ImpFolhas(a->esq);  //Percorre toda a arvore verificando qual no é uma folha
        ImpFolhas(a->dir);
    }
}

int ArvBalanceada(arvore *a){
    if(a == NULL){
        return 0;
    }
    int esq = ArvBalanceada(a->esq);
        if(esq == -1)
            return -1;
    int dir = ArvBalanceada(a->dir);
        if(dir == -1)
            return -1;
    if(abs(esq - dir) > 1)
        return -1;
    else if(esq > dir)
        return 1+esq;
    else
        return 1+dir;

}
int ArvoreCheia(arvore *a, int cont, int n){
    if(a == NULL)
        return 0;
    int quant = ArvoreCheia(a->esq,cont+1,n) + ArvoreCheia(a->dir,cont+1,n);
    if(cont == n)
        return 1 + quant;
    else
        return quant;
}
void ImpNivelNo(arvore *a,int cont, int no){
    if(a != NULL){
        if(no == a->info){
            printf("Existe esse noh no Nivel: %d\n", cont);
        }
        ImpNivelNo(a->esq,cont+1,no);
        ImpNivelNo(a->dir,cont+1,no);
    }
}
int main()  //Main
{
    arvore* a = (arvore*)malloc(sizeof(arvore)); //Cria uma estrutura(arvore) com o nome "a"
    int menu = 0;
    while (menu != 9) //Inicio do loop para manter o programa aberto e ser possivel fazer multiplas operação sem fecha-lo
    {                 //Uso a propria variavel para a escolha de operação, o que vai me permitir controlar mais facil o fechamento da lista ao decorrer do programa
        printf("\x1B[2J\x1b[H");  //Comando que eu aprendi com um professor que tive aula na UFJF para limpar a tela
        printf("Oque Deseja Fazer?\n\n");
        printf("1- Ler uma Arvore\n2- Imprimir Arvore\n3- Verificar Elemento\n4- Tamanho Da Arvore\n5- Imprimir Folhas\n6- Verificar se a Arvore esta balanceada\n7- Verificar se a Arvore esta cheia\n8- Imprimir nivel de um noh\n9- Sair\n\nDigite Aqui: "); //Menu principal de escolha
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
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
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
                for(int i=0;i<AlturaArvore(a);i++){
                    ImpNivelArvore(a,0,i);
                    printf("\n");
                }
            }
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
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
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 4){  //Conta quantos elementos tem na arvore.
            printf("\x1B[2J\x1b[H");  //Limpa a tela
            printf("A arvore tem %d elementos!", ContElementos(a));  //Usa a funcao para contar quantos elementos existem na arvore e imprime na tela
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 5){  //Imprime as folhas
            printf("\x1B[2J\x1b[H");
            printf("Folhas da arvore\n"); 
            ImpFolhas(a);  //Usa a funcao vista anteriormente para imprimir todos os nos folha da arvore
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 6){
            printf("\x1B[2J\x1b[H");
            if(ArvBalanceada(a)>=0){
                printf("A Arvore está Balanceada!");
            }else
                printf("A Arvore não está Balanceada!");
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
        if(menu == 7){

        }
        if(menu == 8){
            int no;
            printf("\x1B[2J\x1b[H");
            printf("Digite o Noh que deseja procurar: ");
            scanf("%d",&no);
            printf("\x1B[2J\x1b[H");
            ImpNivelNo(a,0,no);
            printf("\n\n1- Voltar ao menu\n9- Sair\n\nDigite Aqui: ");  //Escolhas para voltar ao menu principal de escolha ou fechar o programa
            scanf("%d", &menu);
        }
            
    }
    free(a); //Libera a memoria alocada para "a"
    printf("\x1B[2J\x1b[H"); //Limpa a tela
    printf("Programa Fechado!\n"); //Imprime uma mensagem dizendo que o programa fechou
    return 0;
}