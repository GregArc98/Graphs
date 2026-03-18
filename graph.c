#include "graph.h"
struct Graph
{
    int v;
    int **adj;
};

GRAPH *MyGraph(int v)
{
    GRAPH *G = (GRAPH *)malloc(sizeof(GRAPH));
    if (G != NULL)
    {
        G->v = v;
        G->adj = (int **)malloc(sizeof(int *));
        if (G->adj != NULL)
        {
            for (int i = 0; i < v; i++)
            {
                G->adj[i] = (int *)malloc(sizeof(int));
                if (G->adj[i] != NULL)
                {
                    for (int j; j <= v; j++)
                    {
                        G->adj[i][j] = -1;
                    }
                }
                return NULL;
            }
            return G;
        }
        return NULL;
    }
    return NULL;
}

void add_edge(GRAPH *G, int v1, int v2, int peso)
{
    if (G != NULL)
    {
        if (v1 <= G->v && v2 <= G->v && v1 > 0 && v2 > 0)
        {
            G->adj[v1][v2] = peso;
            G->adj[v2][v1] = peso;
        }
    }
    return;
}

int exist_edge(GRAPH *G, int v1, int v2)
{
    if (G != NULL)
    {
        if (G->adj[v1][v2] != -1 && G->adj[v2][v1] != -1)
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

void remove_edge(GRAPH *G, int v1, int v2)
{
    if (G != NULL)
    {
        if (G->adj[v1][v2] != -1 && G->adj[v2][v1] != -1)
        {
            G->adj[v1][v2] = -1;
            G->adj[v2][v1] = -1;
            return;
        }
        printf("-1\n");
    }
    printf("-1\n");
}

void print_info(GRAPH *G)
{
    if (G != NULL)
    {
        printf("Vertices: %d\n", G->v);
        printf("Arestas:\n");
        for (int i = 1; i <= G->v; i++)
        {
            for (int j = i; j <= G->v; j++)
            {
                if (G->adj[i][j] != -1)
                {
                    printf("(%d, %d) peso: %d\n", i, j, G->adj[i][j]);
                }
            }
        }
    }
}

void free_matrix(int **matrix, int v)
{
    if (matrix != NULL)
    {
        for (int i = 0; i <= v; i++)
        {
            free(matrix[i]);
        }
        free(matrix);
    }
    return;
}

void delete_graph(GRAPH **G)
{
    if (G != NULL && *G != NULL)
    {
        free_matrix((*G)->adj, (*G)->v);
        free(*G);
        *G = NULL;
    }
    return;
}
