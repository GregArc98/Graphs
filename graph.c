#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct Graph
{
    int vertices; // numero de verticies
    int **adjMtx; // matriz de adjacências
};

// helper functions

static int is_valid_vertex(const Graph *G, int v)
{
    return (v <= 0 || v > G->vertices);
}

//

// Cria o grafo
Graph *create_graph(int numVertices)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));

    if (G == NULL)
        return NULL;

    G->vertices = numVertices;
    G->adjMtx = (int **)malloc(numVertices * (sizeof(int *)));

    if (G->adjMtx == NULL)
        return NULL;

    for (int i = 0; i < numVertices; i++)
    {
        G->adjMtx[i] = (int *)malloc(numVertices * (sizeof(int)));

        if (G->adjMtx[i] == NULL)
            return NULL;

        for (int j = 0; j < numVertices; j++)
            G->adjMtx[i][j] = -1;
    }

    return G;
}

// libera a memoria do grafo
GraphStatus destroy_graph(Graph **G)
{
    if (!G || !(*G))
        return GRAPH_FAILURE;

    for (int i = 0; i < (*G)->vertices; i++)
    {
        free((*G)->adjMtx[i]);
    }

    free((*G)->adjMtx);
    free(*G);
    *G = NULL;

    return GRAPH_SUCCESS;
}

// adiciona uma aresta entre v1 e v2 com um peso
GraphStatus add_edge(Graph *G, int v1, int v2, int weight)
{
    if (G == NULL)
        return GRAPH_ERROR;

    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    G->adjMtx[v1 - 1][v2 - 1] = weight;
    G->adjMtx[v2 - 1][v1 - 1] = weight;

    return GRAPH_SUCCESS;
}

// verifica se existe aresta entre v1 e v2
GraphStatus exist_edge(Graph *G, int v1, int v2)
{
    if (G == NULL)
        return GRAPH_ERROR;
    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    if (G->adjMtx[v1 - 1][v2 - 1] == -1)
        return GRAPH_FAILURE;

    return GRAPH_SUCCESS;
}

// remove aresta entre v1 e v2
int remove_edge(Graph *G, int v1, int v2)
{
    if (G == NULL)
        return GRAPH_ERROR;

    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    if (G->adjMtx[v1 - 1][v2 - 1] == -1)
        return GRAPH_FAILURE;

    G->adjMtx[v1 - 1][v2 - 1] = -1;
    G->adjMtx[v2 - 1][v1 - 1] = -1;

    return GRAPH_SUCCESS;
}

// retorna o numero de vértices adjacentes a um v
int *neighbors(Graph *G, int v, int *size)
{
    if (!G)
        return NULL;
    if (!is_valid_vertex(G, v))
        return NULL;

    int *adjacentVertices = (int *)calloc(G->vertices, sizeof(int));
    if (!adjacentVertices)
        return NULL;

    int tmpCount = 0;

    for (int j = 0; j < G->vertices; j++)
    {
        if (G->adjMtx[v - 1][j] != -1)
        {
            adjacentVertices[tmpCount++] = j + 1;
        }
    }

    *size = tmpCount;

    return adjacentVertices;
}

// retorna o vértice com maior número de vizinhos
int max_neighbors(Graph *G)
{
    if (G == NULL || G->adjMtx == NULL)
        return 0;

    int tmp = 0;
    int max = 0;
    int max_idx = 0;

    for (int i = 0; i < G->vertices; i++)
    {

        for (int j = 0; j < G->vertices; j++)
        {
            if (G->adjMtx[i][j] != -1)
                tmp++;
        }

        if (tmp > max)
        {
            max = tmp;
            max_idx = i;
        }

        tmp = 0;
    }

    return max_idx + 1;
}

// retorn um ponteiro para a matriz de adjacência
int **adjacency_matrix(Graph *G)
{
    if (G == NULL)
        return NULL;

    return G->adjMtx;
}

// imprime as informações do grafo ; still need to fix this
GraphStatus print_info(Graph *G)
{
    if (G == NULL)
        return GRAPH_FAILURE;

    printf("Vertices: %d\n", G->vertices);
    printf("Arestas:\n");
    for (int i = 0; i < G->vertices; i++)
    {
        for (int j = 0; j < G->vertices; j++)
        {
            if (G->adjMtx[i][j] != -1)
            {
                printf("(%d, %d) peso: %d\n", i + 1, j + 1, G->adjMtx[i][j]);
            }
        }
    }

    return GRAPH_SUCCESS;
}
