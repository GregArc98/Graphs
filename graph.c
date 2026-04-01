#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct Graph
{
    int vertices; // numero de vertices
    int **adjMtx; // matriz de adjacencia
};

// helper functions

static int is_valid_vertex(const Graph *G, int v)
{
    return (v >= 1 && v <= G->vertices);
}

//

/**
 * @brief    Aloca dinamicamente um Grafo baseado em um número de vértices.
 *
 * @param    numVertices A quantidade de vértices que serão criados no Grafo.
 * @return   Um ponteiro para o novo Grafo criado.
 */
Graph *create_graph(int numVertices)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));

    if (G == NULL)
        return NULL;

    G->vertices = numVertices;
    G->adjMtx = (int **)calloc(numVertices, sizeof(int *));

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

/**
 * @brief   Libera a memória do Grafo, incluindo sua matriz de adjacência.
 *
 * @param   **G Um ponteiro para o ponteiro de um Grafo.
 * @return  GraphStatus: 0 para sucesso, 1 para falha.
 */
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

/**
 * @brief   Adiciona uma aresta com um peso específico entre dois vértices
 *
 * @param   *G Um ponteiro para o Grafo.
 * @param   v1 O primeiro vértice.
 * @param   v2 O segundo vértice.
 * @param   weight O peso da aresta.
 * @return  GraphStatus: -1 or 1.
 */
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

/**
 * @brief   Verifica se existe uma aresta entre dois vértices.
 *
 * @param   *G Um ponteiro para o Grafo.
 * @param   v1 O primeiro vértice.
 * @param   v2 O segundo vértice.
 * @return  GraphStatus: -1, 0 or 1
 */
GraphStatus exist_edge(const Graph *G, int v1, int v2)
{
    if (G == NULL)
        return GRAPH_ERROR;
    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    if (G->adjMtx[v1 - 1][v2 - 1] == -1)
        return GRAPH_FAILURE;

    return GRAPH_SUCCESS;
}

/**
 * @brief   Remove uma aresta entre dois vértices, não remove se não existir.
 *
 * @param   *G Um ponteiro para o Grafo.
 * @param   v1 O primeiro vértice.
 * @param   v2 O segundo vértice.
 * @return  GraphStatus: -1 or 1
 */
GraphStatus remove_edge(Graph *G, int v1, int v2)
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

/**
 * @brief   Armazena todos os vizinhos de um vértice em um array.
 *
 * @param   *G Um ponteiro para o Grafo.
 * @param   v O vértice do qual será verificado por vizinhos.
 * @param   *size Onde o tamanho do array de vizinhos será armazenado.
 * @return  int*: Um ponteiro para o array que armazena todos os vizinhos, NULL se algum erro ocorrer.
 */
int *neighbors(const Graph *G, int v, int *size)
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

/**
 * @brief   Retorna o primeiro vértice do Grafo que tem o maior número de vizinhos.
 *
 * @param   *G Um ponteiro para o Grafo.
 * @return  int: O vértice.
 */
int max_neighbors(const Graph *G)
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

GraphStatus adjacency_matrix(const Graph *G)
{
    if (G == NULL)
        return GRAPH_ERROR;

    if(G->adjMtx == NULL)
        return GRAPH_ERROR;

    printf("Adjacency Matrix: \n");
    for(int i = 0; i < G->vertices; i++){
        for(int j = 0; j < G->vertices; j++){
            if(j == 0)
                if(G->adjMtx[i][j] == -1)
                    printf("%3d", 0);
                else
                    printf("%3d", G->adjMtx[i][j]);
            else
                if(G->adjMtx[i][j] == -1)
                    printf("%4d", 0);
                else
                    printf("%4d", G->adjMtx[i][j]);
        }
        printf("\n");
    }

    return GRAPH_SUCCESS;
}

/**
 * @brief   Se o array passado for NULL, imprime informação sobre o Grafo, se não, imprime o array.
 *
 * @param   *G A pointer to the Graph.
 * @param   *arr Um ponteiro para array de int
 * @param   size O tamanho do array de int passado
 * @return  GraphStatus: 0 or 1.
 */
GraphStatus print_info(const Graph *G, int *arr, int size)
{
    if (arr && size)
    {
        for (int i = 0; i < size; i++)
            printf("%d ", arr[i]);

        printf("\n");
        return GRAPH_SUCCESS;
    }

    if (G == NULL)
        return GRAPH_ERROR;

    printf("V = [");
    for (int i = 0; i <= G->vertices; i++)
    {
        if (i != G->vertices)
            printf("%d, ", i);
        else
            printf("%d]\n", i);
    }

    printf("E = [");
    int first = 1;
    for (int j = 0; j < G->vertices; j++)
    {
        for (int i = 0; i < G->vertices; i++)
        {
            if (j < i)
                continue;

            if (G->adjMtx[i][j] != -1)
            {
                if (!first)
                {
                    printf(", ");
                }

                printf("(%d, %d)", i + 1, j + 1);
                first = 0;
            }
        }
    }

    printf("]\n");

    return GRAPH_SUCCESS;
}
