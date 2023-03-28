#include <stdio.h>
#include <stdlib.h>

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest);
void menorCaminho_Grafo(Grafo *gr, int ini, int *antecessor, float *distancia);

void imprime_Grafo(Grafo *gr);

struct grafo{
    int nro_vertices;
    int grau_max;
    int** arestas;
    int* grau;
};

Grafo* cria_Grafo(int nro_vertices, int grau_max){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
    }
    return gr;
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;
    gr->arestas[orig][gr->grau[orig]] = dest;
    gr->grau[orig]++;
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->nro_vertices; i++){
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
    cont = NV = gr->nro_vertices;
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

    insereAresta(gr, 0, 1);
    insereAresta(gr, 0, 3);
    insereAresta(gr, 1, 0);
    insereAresta(gr, 1, 2);
    insereAresta(gr, 2, 1);
    insereAresta(gr, 2, 6);
    insereAresta(gr, 3, 0);
    insereAresta(gr, 3, 4);
    insereAresta(gr, 4, 3);
    insereAresta(gr, 4, 5);
    insereAresta(gr, 5, 4);
    insereAresta(gr, 6, 2);
do{
		printf("\n\t0 - Sair\n\t1 - imprimir\n\t2 - Busca\n -----DIGITE A OPÇÃO DESEJADA-----\n");
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
            libera_Grafo(gr);
            system("pause");
            return 0;
			break;
		default:
			if(opcao != 0)
				printf("Opcao invalida!!!\n");
		}
		}while(opcao !=0);

	return 0;
		}