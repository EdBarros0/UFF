#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int totalElementos=0;

int indiceFilhoEsq(int x){
    int indice=(2*x)+1;
    if(x>=totalElementos||indice>=totalElementos)
        return -1;
    else
        return indice;
}

int indiceFilhoDir(int x){
    int indice=(2*x)+2;
    if(x>=totalElementos||indice>=totalElementos)
        return -1;
    else
        return indice;
}

int IndicePai(int x){
    int indice=(int)floor((x-1)/2);
    if(x<=0||x>=totalElementos)
        return -1;
    else
        return indice;
}

void AjustarSubindo(int *heap, int pos){
    if(pos!=-1){
        int pai = IndicePai(pos);
        if(pai!=-1){
            if(heap[pos] < heap[pai]){
                int aux = heap[pos];
                heap[pos]= heap[pai];
                heap[pai]=aux;
                AjustarSubindo(heap,pai);
            }
        }
    }
}

void Inserir(int *heap, int x){
    heap[totalElementos] = x;
    totalElementos++;

    AjustarSubindo(heap, totalElementos-1);
}

void AjustarDescendo(int *heap, int pos){
    if (pos != -1 && indiceFilhoEsq(pos) != -1){
//Descobridoo maior filho
        int indiceMaiorFilho = indiceFilhoEsq(pos);
        if (indiceFilhoDir(pos) != -1 && heap[indiceFilhoDir(pos)] < heap[indiceMaiorFilho])
            indiceMaiorFilho = indiceFilhoDir(pos);

//Verificando se existe flho maior que o nó atual
        if (heap[indiceMaiorFilho] < heap[pos]){
            int aux =heap[pos];
            heap[pos] = heap[indiceMaiorFilho];
            heap[indiceMaiorFilho] = aux;
            AjustarDescendo(heap, indiceMaiorFilho);
        }
    }
}

int Remover(int *heap){
    if(totalElementos == 0)
        return -1;
    else{
        int retorno = heap[0];
        heap[0] = heap[totalElementos-1];
        totalElementos--;
        AjustarDescendo(heap, 0);
        return retorno;
    }
}

void ImprimeHeap(int *heap){
    for(int i=0;i<totalElementos;i++){
        printf("%d ", heap[i]);
    }
}
int main()
{
    int heap[100];
    while(1){
        printf("\x1B[2J\x1b[H");
        printf("              BEM-VINDO A MANIPULAÇÂO DO MINHEAP!\n\nEscolha a operação a ser feita:\n 1)Inserir Elemento na Heap\n 2)Remover um elemento\n 3)Imprimir a Heap\n 4)Sair\n\nDigite Aqui: ");
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 1){
            printf("\x1B[2J\x1b[H");
            int n;
            printf("Digite o numero a ser inserido: ");
            scanf("%d",&n);
            Inserir(heap, n);
            printf("\n  O numero foi inserido com sucesso!!\n\nDigite 1 para voltar ao menu: ");
            scanf("%d",&n);
        }
        if(escolha == 2){
            printf("\x1B[2J\x1b[H");
            printf(" O Elemento %d foi removido!!\n\nDigite 1 para voltar ao menu: ",Remover(heap));
            int n;
            scanf("%d", &n);
        }
        if(escolha == 3){
            printf("\x1B[2J\x1b[H");
            printf("O heap atual é:\n ");
            ImprimeHeap(heap);
            printf("\n\nDigite 1 para voltar ao menu: ");
            int n;
            scanf("%d", &n);
        }
        if(escolha == 4)
            break;
    }
    printf("\x1B[2J\x1b[H");
    printf("O Programa foi fechado!!\n\n");
    return 0;
}
