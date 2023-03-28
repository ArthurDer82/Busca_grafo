#include <stdio.h>
#include <stdlib.h>

typedef struct grafo Grafo;

Grafo* cria_Grafo(int Vertices, int grau_max);
int AddAresta(Grafo* Ponteiro, int orig, int dest);
void Caminho_Grafo(Grafo *Ponteiro, int ini, int *Antecessor, float *Distancia);

void imprime_Grafo(Grafo *Ponteiro);

struct grafo{
    int Vertices;
    int grau_max;
    int** arestas;
    int* grau;
};

Grafo* cria_Grafo(int Vertices, int grau_max){
    Grafo *Ponteiro;
    Ponteiro = (Grafo*) malloc(sizeof(struct grafo));
    if(Ponteiro != NULL){
        int i;
        Ponteiro->Vertices = Vertices;
        Ponteiro->grau_max = grau_max;
        Ponteiro->grau = (int*) calloc(Vertices,sizeof(int));

        Ponteiro->arestas = (int**) malloc(Vertices * sizeof(int*));
        for(i=0; i<Vertices; i++)
            Ponteiro->arestas[i] = (int*) malloc(grau_max * sizeof(int));
    }
    return Ponteiro;
}

int AddAresta(Grafo* Ponteiro, int orig, int dest){
    if(Ponteiro == NULL)
        return 0;
    if(orig < 0 || orig >= Ponteiro->Vertices)
        return 0;
    if(dest < 0 || dest >= Ponteiro->Vertices)
        return 0;
    Ponteiro->arestas[orig][Ponteiro->grau[orig]] = dest;
    Ponteiro->grau[orig]++;
    return 1;
}

void imprime_Grafo(Grafo *Ponteiro){
    if(Ponteiro == NULL)
        return;

    int i, j;
    for(i=0; i < Ponteiro->Vertices; i++){
        printf("%d: ", i);
        for(j=0; j < Ponteiro->grau[i]; j++){
            printf("|%d| ", Ponteiro->arestas[i][j]);
        }
        printf("\n");
    }
}

int MenorDeslocamento(float *Espaco, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i=0; i < NV; i++){
        if(Espaco[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(Espaco[menor] > Espaco[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void Caminho_Grafo(Grafo *Ponteiro, int ini, int *Anterior, float *Espaco){
    int i, cont, NV, ind, *visitado, vert;
    cont = NV = Ponteiro->Vertices;
    visitado = (int*) malloc(NV * sizeof(int));
    for(i=0; i < NV; i++){
        Anterior[i] = -1;
        Espaco[i] = -1;
        visitado[i] = 0;
    }
    Espaco[ini] = 0;
    while(cont > 0){
        vert = MenorDeslocamento(Espaco, visitado, NV);
        if(vert == -1)
            break;

        visitado[vert] = 1;
        cont--;
        for(i=0; i<Ponteiro->grau[vert]; i++){
            ind = Ponteiro->arestas[vert][i];
            if(Espaco[ind] < 0){
               Espaco[ind] = Espaco[vert] + 1;
               Anterior[ind] = vert;
            }else{
                if(Espaco[ind] > Espaco[vert] + 1){
                    Espaco[ind] = Espaco[vert] + 1;
                    Anterior[ind] = vert;
                }
            }
        }
    }

    free(visitado);
}
int main(){
    int opcao, inicio, destino;
    Grafo* Ponteiro = cria_Grafo(7, 2);

    AddAresta(Ponteiro, 0, 1);
    AddAresta(Ponteiro, 0, 3);
    AddAresta(Ponteiro, 1, 0);
    AddAresta(Ponteiro, 1, 2);
    AddAresta(Ponteiro, 2, 1);
    AddAresta(Ponteiro, 2, 6);
    AddAresta(Ponteiro, 3, 0);
    AddAresta(Ponteiro, 3, 4);
    AddAresta(Ponteiro, 4, 3);
    AddAresta(Ponteiro, 4, 5);
    AddAresta(Ponteiro, 5, 4);
    AddAresta(Ponteiro, 6, 2);
do{
		printf("\n\t0 - Sair\n\t1 - imprimir\n\t2 - Busca\n -----DIGITE A OPÇÃO DESEJADA PARA O GRAFO:-----\n    1 2 3 4 5 6 7\n    _____________\n 1| 0 1 0 1 0 0 0\n 2| 1 0 1 0 0 0 0\n 3| 0 1 0 0 0 0 1\n 4| 1 0 0 0 1 0 0\n 5| 0 0 0 1 0 1 0\n 6| 0 0 0 0 1 0 0\n 7| 0 0 1 0 0 0 0\n");
	    scanf("%d", &opcao);
	
		switch(opcao){
		case 1:
			imprime_Grafo(Ponteiro);
            printf("\nBusca \n");
            int vis[7];
			break;
		case 2:
		    printf("\n\t -----DIGITE O INICIO DA BUSCA-----\n");
		    scanf("%d", &inicio);
		    printf("\n\t -----DIGITE O DESTINO DA BUSCA-----\n");
		    scanf("%d", &destino);
			int i,Anterior[7];
            float Espaco[7];
            Caminho_Grafo(Ponteiro, inicio, Anterior, Espaco);
                printf("O VALOR DA DISTANCIA PERCORRIDA FOI => %f\n",destino,Anterior[destino],Espaco[destino]);
			break;
		default:
			if(opcao != 0)
				printf("Opcao invalida!!!\n");
		}
		}while(opcao !=0);

	return 0;
		}
