#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////FUNCAO PARA LIMPAR TELA////////////////////
void clear_screen(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}
///////////////////////COMBINACOES NO VETOR CHAR//////////////////////////////
void ImprimirCombinacaoChar(char *vet, int pos,int n, char *vetAux){
    int i;
    if(pos == n){
        int v=0;
        for(i=0;i<n;i++){
            if(vet[i] == 'a')
                v+=1;
        }
        if(n%2 == 0){
            if(v >= n/2+1){
                for(i=0;i<n;i++)
                    printf("%c ", vet[i]);
                printf("\n");
            }
        }else{
            if(v >= n/2){
                for(i=0;i<n;i++)
                    printf("%c ", vet[i]);
                printf("\n");
            }
        }
    }else{
        for(i=0;i<=2;i++){
            vet[pos]=vetAux[i];
            ImprimirCombinacaoChar(vet, pos+1, n, vetAux);
        }
    }
}
///////////////////////COMBINACOES NO VETOR INT//////////////////////////////
void ImprimirCombinacaoInt(int *vet, int pos,int n, int *vetAux){
    int i;
    if(pos == n){
        int aux=0;
        for(i=0;i<n;i++)
            aux += vet[i];
        if(aux%2 == 0){
            for(i=0;i<n;i++)
                printf("%d ", vet[i]);
            printf("\n");
        }
    }else{
        for(i=0;i<=3;i++){
            vet[pos]=vetAux[i];
            ImprimirCombinacaoInt(vet, pos+1, n, vetAux);
        }
    }
}
///////////////////////QUANTIDADE DE MOEDAS//////////////////////////////
void ImprimirCombinacaoMoeda(int *vet, int pos,int n){
    int i;
    if(pos == 5){
        int aux = 0;
        for(i=0;i<5;i++){
            switch (i)
            {
            case 0:
                aux += vet[i];
                break;
            case 1:
                aux += (5*vet[i]);
                break;
            case 2:
                aux += (10*vet[i]);
                break;
            case 3:
                aux += (25*vet[i]);
                break;
            case 4:
                aux += (50*vet[i]);
                break;

            default:
                break;
            }
        }
        if(aux == n){
            for(i=0;i<5;i++){
                switch (i){
                    case 0:
                        printf("%d moedas de 1, ", vet[i]);
                        break;
                    case 1:
                        printf("%d moedas de 5, ", vet[i]);
                        break;
                    case 2:
                        printf("%d moedas de 10, ", vet[i]);
                        break;
                    case 3:
                        printf("%d moedas de 25, ", vet[i]);
                        break;
                    case 4:
                        printf("%d moedas de 50 ", vet[i]);
                        break;

                    default:
                        break;
                }
            }
            printf("\n");
        }
    }else{
        for(i=0;i<=n;i++){
            vet[pos]= i;
            ImprimirCombinacaoMoeda(vet, pos+1, n);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////
int main(){
    while (1)
    {
       clear_screen();
       int op;
       printf("Diga qual operação deseja fazer: \n\n 1-Combinacoes de {a,e,i}\n 2-Combinacoes de {15,31,55,44}\n 3-Quantidade de Moedas\n 4-sair\n\n");
       printf("Digite aqui: ");
       scanf("%d", &op);
       if(op == 1){
            clear_screen();
            int n;
            printf("Digite o tamanho das combinações: ");
            scanf("%d", &n);
            char a[4] = {'a','e','i'};
            char vet[n+1];
            ImprimirCombinacaoChar(vet,0,n,a);
            getchar();
            getchar();
       }else if(op == 2){
            clear_screen();
            int n;
            printf("Digite o tamanho das combinações: ");
            scanf("%d", &n);
            int b[4] = {15,31,55,44};
            int vet[n];
            ImprimirCombinacaoInt(vet,0,n,b);
            getchar();
            getchar();
       }else if(op == 3){
            clear_screen();
            int n;
            printf("Digite qual valor deseja obter: ");
            scanf("%d", &n);
            int vet[n];
            ImprimirCombinacaoMoeda(vet,0,n);
            getchar();
            getchar();
       }else if(op == 4){
            clear_screen();
            printf("Obrigado por usar o programa!!");
            printf("\n\n\nAperte qualquer tecla para fechar-lo\n");
            getchar();
            getchar();
            break;
       }
    }
    
    
}