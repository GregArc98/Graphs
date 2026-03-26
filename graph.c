#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct Graph
{
    int vertices; // number of vertices
    int **adjMtx; // adjacency matrix
};

// helper functions

static int is_valid_vertex(const Graph *G, int v)
{
    return (v >= 1 && v <= G->vertices);
}

//

/**
 * @brief    Dynamically allocates a new Graph struct based on an amount of vertices.
 *
 * @param    numVertices The amount of vertices that'll be created in the Graph.
 * @return   A pointer to the newly created Graph struct.
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
 * @brief   Frees the entire Graph, including its adjacent matrix.
 *
 * @param   **G A pointer to a pointer of the Graph.
 * @return  GraphStatus: 0 for success, 1 for failure.
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
 * @brief   Adds an edge with a specific weight between two vertices of the Graph.
 *
 * @param   *G A pointer to the Graph.
 * @param   v1 The first vertix.
 * @param   v2 The second vertix.
 * @param   weight The "value" (weight) of the edge.
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
 * @brief   Checks if an edge exists between two vertices of the Graph.
 *
 * @param   *G A pointer to the Graph.
 * @param   v1 The first vertix.
 * @param   v2 The second vertix.
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

// all other functions work using GraphStatus, it's required for this one to return -1 so I used GRAPH_ERROR for what was supposed to be GRAPH_FAILURE (third "if")
/**
 * @brief   Removes an edge between two vertices, doesn't do it if it doesn't exist.
 *
 * @param   *G A pointer to the Graph.
 * @param   v1 The first vertix.
 * @param   v2 The second vertix.
 * @return  GraphStatus: -1 or 1
 */
GraphStatus remove_edge(Graph *G, int v1, int v2)
{
    if (G == NULL)
        return GRAPH_ERROR;

    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    if (G->adjMtx[v1 - 1][v2 - 1] == -1)
        return GRAPH_ERROR;

    G->adjMtx[v1 - 1][v2 - 1] = -1;
    G->adjMtx[v2 - 1][v1 - 1] = -1;

    return GRAPH_SUCCESS;
}

/**
 * @brief   Stores all the neighbors of a vertix "v" of the Graph in an array, returns a pointer to it.
 *
 * @param   *G A pointer to the Graph.
 * @param   v The vertix that'll be checked for neighbors.
 * @param   *size Where the neighbors array's size will be stored.
 * @return  int*: A pointer to an array containing all neighbors, NULL if any errors occur.
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
 * @brief   Returns the first vertix from the Graph that has the highest number of neighbors.
 *
 * @param   *G A pointer to the Graph.
 * @return  int: The vertix's number.
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

/**
 * @brief   Returns the Graph's adjacency matrix.
 *
 * @param   *G A pointer to the Graph.
 * @return  int**: The Graph's adjacency matrix, NULL if the Graph is NULL.
 */
int **adjacency_matrix(const Graph *G)
{
    if (G == NULL)
        return NULL;

    return G->adjMtx;
}

// essa funcao ta ruim
/**
 * @brief   Prints info about the graph.
 *
 * @param   *G A pointer to the Graph.
 * @return  GraphStatus: 0 or 1.
 */
GraphStatus print_info(const Graph *G, int *arr, int size)
{
    if (arr && size) {
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
                if (!first) {
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
