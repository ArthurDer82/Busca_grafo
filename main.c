#include <stdio.h>
#include <stdlib.h>

typedef struct grafo Grafo;

Grafo* cria_Grafo(int Vertices, int grau_max);
int AddAresta(Grafo* gr, int orig, int dest);
void menorCaminho_Grafo(Grafo *gr, int ini, int *antecessor, float *distancia);

void imprime_Grafo(Grafo *gr);

struct grafo{
    int Vertices;
    int grau_max;
    int** arestas;
    int* grau;
};

Grafo* cria_Grafo(int Vertices, int grau_max){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->Vertices = Vertices;
        gr->grau_max = grau_max;
        gr->grau = (int*) calloc(Vertices,sizeof(int));

        gr->arestas = (int**) malloc(Vertices * sizeof(int*));
        for(i=0; i<Vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
    }
    return gr;
}

int AddAresta(Grafo* gr, int orig, int dest){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->Vertices)
        return 0;
    if(dest < 0 || dest >= gr->Vertices)
        return 0;
    gr->arestas[orig][gr->grau[orig]] = dest;
    gr->grau[orig]++;
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->Vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            printf("|%d| ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i=0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist){
    int i, cont, NV, ind, *visitado, vert;
    cont = NV = gr->Vertices;
    visitado = (int*) malloc(NV * sizeof(int));
    for(i=0; i < NV; i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while(cont > 0){
        vert = procuraMenorDistancia(dist, visitado, NV);
        if(vert == -1)
            break;

        visitado[vert] = 1;
        cont--;
        for(i=0; i<gr->grau[vert]; i++){
            ind = gr->arestas[vert][i];
            if(dist[ind] < 0){
               dist[ind] = dist[vert] + 1;
               ant[ind] = vert;
            }else{
                if(dist[ind] > dist[vert] + 1){
                    dist[ind] = dist[vert] + 1;
                    ant[ind] = vert;
                }
            }
        }
    }

    free(visitado);
}
int main(){
    int opcao, inicio, destino;
    Grafo* gr = cria_Grafo(7, 2);

    AddAresta(gr, 0, 1);
    AddAresta(gr, 0, 3);
    AddAresta(gr, 1, 0);
    AddAresta(gr, 1, 2);
    AddAresta(gr, 2, 1);
    AddAresta(gr, 2, 6);
    AddAresta(gr, 3, 0);
    AddAresta(gr, 3, 4);
    AddAresta(gr, 4, 3);
    AddAresta(gr, 4, 5);
    AddAresta(gr, 5, 4);
    AddAresta(gr, 6, 2);
do{
		printf("\n\t0 - Sair\n\t1 - imprimir\n\t2 - Busca\n -----DIGITE A OPÇÃO DESEJADA PARA O GRAFO:-----\n\t1 2 3 4 5 6 7\n\t_____________\n 1| 0 1 0 1 0 0 0\n 2| 1 0 1 0 0 0 0\n 3| 0 1 0 0 0 0 1\n 4| 1 0 0 0 1 0 0\n 5| 0 0 0 1 0 1 0\n 6| 0 0 0 0 1 0 0\n 7| 0 0 1 0 0 0 0\n");
	    scanf("%d", &opcao);
	
		switch(opcao){
		case 1:
			imprime_Grafo(gr);
            printf("\nBusca \n");
            int vis[7];
			break;
		case 2:
		    printf("\n\t -----DIGITE O INICIO DA BUSCA-----\n");
		    scanf("%d", &inicio);
		    printf("\n\t -----DIGITE O DESTINO DA BUSCA-----\n");
		    scanf("%d", &destino);
			int i,ant[7];
            float dist[7];
            menorCaminho_Grafo(gr, inicio, ant, dist);
                printf("%d-> %f\n",destino,ant[destino],dist[destino]);
			break;
		default:
			if(opcao != 0)
				printf("Opcao invalida!!!\n");
		}
		}while(opcao !=0);

	return 0;
		}
