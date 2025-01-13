#include <stdio.h>
#include <stdlib.h>
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

#define TAM 1000

typedef struct Professores
{
    int matricula;
    char nome[TAM];
    int salario;

}Professores;


typedef struct Alunos
{
    int matricula;
    char nome[TAM];
    char curso[TAM];
    int anoDeIngresso;

}Alunos;

typedef struct Pessoas
{
    int tipo; //Tipo 1 para Professores e tipo 2 para Alunos
    void* item;
    struct Pessoas *next;

}Pessoas;



Pessoas *inserir(Pessoas* lista, int tipo, void* item){
    if(lista == NULL){
        Pessoas *no = (Pessoas*)malloc(sizeof(Pessoas));
        no->tipo = tipo;
        no->item = item;
        no->next = NULL;
        return no;
    }else{
        lista->next = inserir(lista->next, tipo, item);
        return lista;
    }
}

Pessoas *remover(Pessoas* lista, int mat){
    if(lista != NULL){
        if(lista->tipo == 1){
            Professores* p = lista->item;
            if(p->matricula == mat){
                free(p);
                return lista->next;
            }else{
                lista->next = remover(lista->next, mat);
                return lista;
            }
        }else{
            Alunos* a = lista->item;
            if(a->matricula == mat){
                free(a);
                return lista->next;
            }else{
                lista->next = remover(lista->next, mat);
                return lista;
            }
        }
    }
}

void imprimeMat(Pessoas* lista, int mat){
    if(lista != NULL){
        if(lista->tipo == 1){
            Professores* p = lista->item;
            if(p->matricula == mat){
                printf("-Professor- \nnome: %smatricula: %d\nsalario: %d\n",p->nome,p->matricula,p->salario);
            }else{
                imprimeMat(lista->next, mat);
            }
        }else{
            Alunos* a = lista->item;
            if(a->matricula == mat){
                printf("-Aluno- \nnome: %smatricula: %d\ncurso: %sAno de Ingresso: %d\n",a->nome,a->matricula,a->curso,a->anoDeIngresso);
        
            }else{
                imprimeMat(lista->next, mat);

            }
        }
    }
}

int contAluno(Pessoas* lista){
    if(lista == NULL){
        return 0;
    }else{
        if(lista->tipo == 2){
            return 1 + contAluno(lista->next);
        }else{
            return contAluno(lista->next);
        }
    }
}

int MaiorSalario(Pessoas* lista, int sal){
    if(lista != NULL){
        Professores *p = lista->item;
        if(p->salario > sal){
            sal = p->salario;
        }
        return MaiorSalario(lista->next, sal);
    }else return sal;
}

void imprimeMaior(Pessoas* lista){
    if(lista != NULL){
        Professores *p = lista->item;
        if(p->salario == MaiorSalario(lista, 0)){
            printf("-Professor- \nnome: %smatricula: %d\nsalario: %d\n\n",p->nome,p->matricula,p->salario);
        }
        imprimeMaior(lista->next);
    }
}

Pessoas* limparLista(Pessoas* lista){
    if(lista != NULL){
        lista->next = limparLista(lista->next);
        free(lista->item);
        free(lista);
        return NULL;
    }else{
        return NULL;
    }
}


int main(){
    Pessoas *lista = NULL;
    while (1){
        int menu;
        clear_screen();
        printf("Oque voce deseja fazer?\n 1-Inserir uma pessoa a lista\n 2-Remover alguem da lista\n 3-Buscar alguem\n 4-Contar numero de alunos\n 5-Imprimir professores de maior salario\n 6-sair\n\nDigite aqui: ");
        scanf("%d", &menu);
        if(menu == 1){
            int in;
            clear_screen();
            printf("Oque deseja inserir?\n 1-Professor\n 2-Aluno\n\nDigite aqui: ");
            scanf("%d", &in);
            if(in == 1){
                clear_screen();
                Professores *a = (Professores*)malloc(sizeof(Professores));
                printf("Digite o nome: ");
                getchar();
                fgets(a->nome,TAM,stdin);
                printf("Digite a matricula: ");
                scanf("%d", &a->matricula)/
                printf("Digite o salario: ");
                scanf("%d", &a->salario);
                lista = inserir(lista,in,a);
                printf("Professor foi inserirdo com sucesso!!");
                getchar();
                getchar();
            }else if(in == 2){
                clear_screen();
                Alunos *a = (Alunos*)malloc(sizeof(Alunos));
                printf("Digite o nome: ");
                getchar();
                fgets(a->nome,TAM,stdin);
                printf("Digite a matricula: ");
                scanf("%d", &a->matricula);
                printf("Digite o curso: ");
                getchar();
                fgets(a->curso,TAM,stdin);
                printf("Digite o Ano de Ingresso: ");
                scanf("%d", &a->anoDeIngresso);
                lista = inserir(lista,in,a);
                printf("Aluno foi inserirdo com sucesso!!");
                getchar();
                getchar();
            }else{
                printf("Tipo nao existe!!");
                getchar();
                getchar();
            }
        }else if(menu == 2){
            int mat;
            clear_screen();
            printf("Digite a matricula da pessoa a ser removida: ");
            scanf("%d", &mat);
            lista = remover(lista, mat);
            printf("Pessoa removida com sucesso!!");
            getchar();
            getchar();
        }else if(menu == 3){
            int mat;
            clear_screen();
            printf("Digite a matricula a ser buscada: ");
            scanf("%d", &mat);
            imprimeMat(lista, mat);
            getchar();
            getchar();
        }else if(menu == 4){
            clear_screen();
            int cont = contAluno(lista);
            printf("%d Alunos existem na lista!!\n", cont);
            getchar();
            getchar();
        }else if(menu == 5){
            clear_screen();
            printf("Os professors de maior salario são:\n");
            imprimeMaior(lista);
            getchar();
            getchar();
        }else if( menu == 6){
            clear_screen();
            lista = limparLista(lista);
            free(lista);
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
    
}
