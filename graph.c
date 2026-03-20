#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

struct Graph
{
    int v; //numero de verticies
    int **adj;//matriz de adjacências
};

//Cria o grafo
GRAPH *MyGraph(int v)
{
    GRAPH *G = (GRAPH *)malloc(sizeof(GRAPH));

    if (G == NULL) return NULL;

    G->v = v;
    G->adj = (int **)malloc(v * (sizeof(int *)));
    
    if (G->adj == NULL) return NULL;
    
    for (int i = 0; i < v; i++)
    {
        G->adj[i] = (int *)malloc(v * (sizeof(int)));
        
        if (G->adj[i] == NULL) return NULL;
        
        for (int j = 0; j < v; j++)
        {
            G->adj[i][j] = -1;
        }
    }
    return G;
}

//adiciona uma aresta entre v1 e v2 com um peso
void add_edge(GRAPH *G, int v1, int v2, int peso)
{
    if (G == NULL) return;
    
    if (v1 <= G->v && v2 <= G->v && v1 > 0 && v2 > 0)
    {
        G->adj[v1 - 1][v2 - 1] = peso;
        G->adj[v2 - 1][v1 - 1] = peso;
    }
}

//verifica se existe aresta entre v1 e v2
int exist_edge(GRAPH *G, int v1, int v2)
{
    if (G == NULL) return 0;
    if (v1 < 1 || v1 > G->v) return 0;
    if (v2 < 1 || v2 > G->v) return 0;
    
    if (G->adj[v1 - 1][v2 - 1] != -1 && G->adj[v2 - 1][v1 - 1] != -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//remove aresta entre v1 e v2
void remove_edge(GRAPH *G, int v1, int v2)
{
    if (v1 < 1 || v1 > G->v) return;
    if (v2 < 1 || v2 > G->v) return;

    if (G == NULL){ 
        printf("-1\n");
        return;
    }
    
    if (G->adj[v1 - 1][v2 - 1] != -1 && G->adj[v2 - 1][v1 - 1] != -1)
    {
        G->adj[v1-1][v2-1] = -1;
        G->adj[v2-1][v1-1] = -1;
        return;
    }
}

//imprime as informações do grafo
void print_info(GRAPH *G)
{
    if (G != NULL)
    {
        printf("Vertices: %d\n", G->v);
        printf("Arestas:\n");
        for (int i = 0; i < G->v; i++)
        {
            for (int j = 0; j < G->v; j++)
            {
                if (G->adj[i][j] != -1)
                {
                    printf("(%d, %d) peso: %d\n", i + 1, j + 1, G->adj[i][j]);
                }
            }
        }
    }
}

//libera a memomoria da matriz adjunta
void free_matrix(int **matrix, int v)
{
    if (matrix != NULL)
    {
        for (int i = 0; i < v; i++)
        {
            free(matrix[i]);
        }
        free(matrix);
    }
    return;
}

//libera a memoria do grafo
void remove_graph(GRAPH **G)
{
    if (G == NULL || *G == NULL) return;
    
    free_matrix((*G)->adj, (*G)->v);
    free(*G);
    *G = NULL;
  
}

//retorna o numero de vértices adjacentes a um v
int *neighbors(GRAPH *G, int v)
{
    if (G == NULL || G->adj == NULL) return NULL;
    if (v < 1 || v > G->v) return NULL;

    int idx = v - 1;

    int cont = 0;
    for (int j = 0; j < G->v; j++)
    {
        if (G->adj[idx][j] != -1)
        {
            cont++;
        }
    }

    if (cont == 0) return NULL;

    int *arr = (int *)malloc(cont * sizeof(int));
    if (arr == NULL) return NULL;

    cont = 0;

    for (int j = 0; j < G->v; j++)
    {
        if (G->adj[idx][j] != -1)
        {
            arr[cont] = j+1;
            cont++;
        }
    }
    return arr;
}

//retorn um ponteiro para a matriz de adjacência
int **adjacency_matrix(GRAPH *G)
{
    if (G != NULL)
    {
        if (G->adj != NULL)
        {
            return G->adj;
        }
    }
    return NULL;
}

//retorna o vértice com maior número de vizinhos
int max_neighbors(GRAPH *G)
{
    if (G == NULL || G->adj == NULL) return 0;

    int tmp=0;
    int max=0;
    int max_idx=0;

    for (int i = 0; i < G->v; i++){
        
        for(int j=0; j < G->v; j++){
            if(G->adj[i][j] != -1) tmp++;
        }

        if(tmp > max){
            max = tmp;
            max_idx = i;
        }

        tmp=0;
    }

    return max_idx + 1;
}