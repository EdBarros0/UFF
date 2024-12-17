#include <stdio.h>
#include <stdlib.h>

///////////////////////FUNCAO PARA LIMPAR TELA////////////////////
void clear_screen(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}

typedef struct lista{
    int destino;
    int custo;
    struct lista *prox;
}lista;


void inicializar (lista **g, int n){    
    for(int i=0;i<=n;i++){
        g[i]==NULL;
    }
}

lista *InserirLista(lista *l,int d,int c){
    lista *no = (lista*)malloc(sizeof(lista));
    no->destino = d;
    no->custo = c;
    no->prox = l;
    return no;
}

void InserirAresta(lista **g, int origem, int destino,int custo){
    g[origem] = InserirLista(g[origem],destino,custo);
}

lista* removerLista(lista* l, int d) {
    if (l == NULL) 
        return NULL;
    if (l->destino == d) { 
        lista* prox = l->prox;
        free(l);
        return prox;
    }
    lista* atual = l;
    while (atual->prox != NULL && atual->prox->destino != d) {
        atual = atual->prox;
    }
    if (atual->prox != NULL) { 
        lista* aux = atual->prox;
        atual->prox = aux->prox;
        free(aux);
    }
    return l;
}

void removerAresta(lista** g, int origem, int destino) {
    g[origem] = removerLista(g[origem], destino);
}

void imprimirLista(lista* l){
    if(l!=NULL){
        printf("Destino: %d \n Custo: %d ", l->destino, l->custo);
        imprimirLista(l->prox);
    }
}

void imprimirGrafo(lista** l, int tam){
    printf("Grafo: ");
    for(int i=1;i<tam;i++){
        printf("\n\t[%d] ", i);
        imprimirLista(l[i]);
    }
    printf("\n");
}

int grauDeSaida(lista* l){
    int cont=0;
    lista* aux = l;
    while(aux){
        aux=aux->prox;
        cont++;
    }
    return cont;
}

int saida(lista** l, int v){
    return grauDeSaida(l[v]);
}

int existe(lista* l, int v){
    lista* aux = l;
    while(aux){
        if(aux->destino==v){
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}

int existe2(int* vet, int valor, int tam){
    for(int i=0;i<tam;i++){
        if(vet[i]==valor){
            return 1;
        }
    }
    return 0;
}

int entrada(lista** l, int v, int tam){
    int grau=0;
    for(int i=1 ;i<tam;i++){
        if(i==v){
            continue;
        }
        if(existe(l[i], v)==1)
            grau++;
    }
    return grau;
}

int Completo(lista** g, int tam){
    int completude=0;
    for(int i=1;i<=tam;i++){
        if(grauDeSaida(g[i]) == tam-1){
            completude=1;
        }else{
            completude=0;
            break;
        }
    }
    if(completude == 1){
        return 1;
    }else{
        return 0;
    }
}

void caminhos(lista** l, int b, int* vet, int pos){
    if(vet[pos-1]==b){
        printf("\n");
        for(int i=0;i<pos;i++){
            printf("%d ", vet[i]);
        }
    }else{
        lista* p = l[vet[pos-1]];
        while(p!=NULL){
            if(!existe2(vet,p->destino,pos)){
                vet[pos] = p->destino;
                caminhos(l,b,vet,pos+1);
            }
            p=p->prox;
        }
    }
}

void caminhoMaisCurto(lista** l, int origem, int destino, int* vet, int pos, int* melhorCaminho, int* menorTam){
    if(vet[pos - 1] == destino){
        if(pos < *menorTam){
            *menorTam = pos;
            for(int i = 0; i < pos; i++){
                melhorCaminho[i] = vet[i];
            }
        }
    } else {
        lista* p = l[vet[pos - 1]];
        while(p != NULL){
            if(!existe2(vet, p->destino, pos)){
                vet[pos] = p->destino;
                caminhoMaisCurto(l, origem, destino, vet, pos + 1, melhorCaminho, menorTam);
            }
            p = p->prox;
        }
    }
}

void caminhoMenosCustoso(lista** l, int origem, int destino, int* vet, int pos, int* melhorCaminho, int* menorCusto, int custoAtual){
    if(vet[pos - 1] == destino){
        if(custoAtual < *menorCusto){
            *menorCusto = custoAtual;
            for(int i = 0; i < pos; i++){
                melhorCaminho[i] = vet[i];
            }
            melhorCaminho[pos]= -1; //Indica que o caminho terminou
        }
    } else {
        lista* p = l[vet[pos - 1]];
        while(p != NULL){
            if(!existe2(vet, p->destino, pos)){
                vet[pos] = p->destino;
                caminhoMenosCustoso(l, origem, destino, vet, pos + 1, melhorCaminho, menorCusto, custoAtual + p->custo);
            }
            p = p->prox;
        }
    }
}

int main() {

    int tam=5; //tamanho do grafo (considerando a posição 0)
    int vet[tam], melhorCaminho[tam];
    lista* l[tam];
    inicializar(l,tam);
    while (1)
    {
        clear_screen();
        int op;
         printf("Diga qual operação deseja fazer: \n\n1- Inserir aresta\n2- Remover aresta\n3- Imprimir grafo\n4- Graus de entrada e saida\n5- Completude\n6- Todos os caminhos entre X e Y\n7- Caminho mais curto\n8- Caminho menos custoso\n9) Sair\n\n");
         printf("Digite Aqui: ");
         scanf("%d", &op);

         if(op == 1){
            int origem, destino, custo;
            clear_screen();
            printf("Digite a origem a ser inserida: ");
            scanf("%d", &origem);
            printf("Digite o destino: ");
            scanf("%d", &destino);
            printf("Digite o custo: ");
            scanf("%d", &custo);
            InserirAresta(l,origem,destino,custo);
            clear_screen();
            printf("\n\nAresta inserida!");
            getchar();
         }else if(op == 2){
            int origem,destino;
            clear_screen();
            printf("Digite a origem a ser removida: ");
            scanf("%d", &origem);
            printf("Digite o destino: ");
            scanf("%d", &destino);
            removerAresta(l,origem,destino);
            clear_screen();
            printf("\n\nAresta removida!");
            getchar();
         }else if(op == 3){
            imprimirGrafo(l,tam);
            getchar();
         }else if(op == 4){
            int origem;
            clear_screen();
            printf("Digite o vertice: ");
            scanf("%d", &origem);
            clear_screen();
            printf("O Grau de saida eh: %d \n\n O Grau de entrada eh: %d\n", entrada(l,origem,tam),saida(l,origem) );
            getchar();
         }else if(op == 5){
            clear_screen();
            if(Completo(l,tam)==1){
                printf("\n\nO grafo eh completo\n");
            }else{
                printf("\n\nO grafo nao eh completo\n");
            }
         }else if(op == 6){
            int origem,destino;
            clear_screen();
            printf("Digite a origem: ");
            scanf("%d", &origem);
            printf("Digite o destino: ");
            scanf("%d", &destino);
            vet[0] = origem;
            clear_screen();
            caminhos(l,destino,vet,1);
            getchar();
         }else if(op == 7){
            int origem,destino;
            clear_screen();
            printf("Digite a origem: ");
            scanf("%d", &origem);
            printf("Digite o destino: ");
            scanf("%d", &destino);
            vet[0] = origem;
            int TamMin;
            caminhoMaisCurto(l, origem, destino, vet, 1, melhorCaminho, &TamMin);
            clear_screen();
            printf("\nMenor Caminho: \n\n");
            for(int i = 0; i < TamMin; i++){
                printf("%d ", melhorCaminho[i]);
            }
            getchar();
         }else if(op == 8){
            int origem,destino;
            clear_screen();
            printf("Digite a origem: ");
            scanf("%d", &origem);
            printf("Digite o destino: ");
            scanf("%d", &destino);
            vet[0] = origem;
            int CustoMin;
            caminhoMenosCustoso(l, origem, destino, vet, 1, melhorCaminho, &CustoMin, 0);
            clear_screen();
            printf("\nMenor Custo: \n\n");
            for(int i = 0; melhorCaminho[i] != -1; i++){
                printf("%d ", melhorCaminho[i]);
            }
            printf("\nCusto total: %d\n", CustoMin);
            getchar();
         }else if(op == 9){
            clear_screen();
            printf("Obrigado por usar o programa!!");
            printf("\n\n\nAperte qualquer tecla para fechar-lo\n");
            getchar();
            getchar();
            break;
         }
    }
    
    
    return 0;
}