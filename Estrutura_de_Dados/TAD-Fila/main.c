#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#ifdef __linux__
	#include <unistd.h>
#elif _WIN32
	#include <windowns.h>
#else

#endif

void pausef(int x){
	#ifdef __linux__
		usleep(x * 1000);
	#elif _WIN32
		Sleep(x);
	#else

	#endif
}

void clear_screen(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}

int main() {
	Fila a = inicializar();
	while(1){
		int m;
		clear_screen();
		printf("   Criador de Filas   \n Oque deseja fazer?\n 1-Inserir Elemento a Fila\n 2-Remover Elemento da Fila\n 3-Imprimir Fila\n 4-Sair\n\n");
		printf("Digite Aqui: ");
		scanf("%d", &m);
		if(m==1){
			int x;
			clear_screen();
			printf("Digite o Elemento a ser inserido: ");
			scanf("%d", &x);
			clear_screen();
			enqueue(a,x);
			printf("O %d foi adicionado com sucesso!!\n\n", x);
			printf("\nDigite qualquer tecla para voltar para o menu: ");
			getchar();
			getchar();
		}
		if(m==2){
			int x,k;
			clear_screen();
			k = dequeue(a, &x);
			if(k == 1){
				printf("O %d foi removido da fila!\n\n", x);
			}else{
				printf("A fila está vazia!!\n\n");
			}
			printf("\nDigite qualquer tecla para voltar para o menu: ");
			getchar();
			getchar();
		}
		if(m==3){
			clear_screen();
			Imprimir(a);
			printf("\n\n\n\nDigite qualquer tecla para voltar para o menu: ");
			getchar();
			getchar();
		}
		if(m==4){
			clear_screen();
			printf("Sistema fechando em: ");
			fflush(stdout);
			pausef(1000);	
			printf("3...");
			fflush(stdout);
			pausef(1000);
			printf("2...");
			fflush(stdout);
			pausef(1000);
			printf("1...");	
			fflush(stdout);
			pausef(1000);
			printf("bye");
			fflush(stdout);
			pausef(1000);
			clear_screen();
			break;
		}
	}
	a = Destruir(a);
	return 0;
}