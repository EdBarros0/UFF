#include <stdio.h>
#include "fila.h"

int main() {
	int x;
	Fila a = inicializar();
	enqueue(a, 10);
	enqueue(a, 24);
	Imprimir(a);
	dequeue(a, &x);
	printf("\n%d", x);
	a = Destruir(a);
	return 0;
}