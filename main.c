#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aluno:  Luís Gustavo Vieira Antoniosi   | NºUSP: 17067476
Aluno:  Luiz Filipe Sá Vioto            | NºUSP: 16886252
Aluno:  Matheus Gregório Muniz Arcanjo  | NºUSP: 16892051
Aluno:  Rafael Said Jannini             | NºUSP: 16898162
*/

typedef enum GraphStatus {
    GRAPH_ERROR = -1,
    GRAPH_SUCCESS = 0,
    GRAPH_FAILURE = 1
} GraphStatus;

typedef struct Graph Graph;

Graph *create_graph(int numVertices);
GraphStatus destroy_graph(Graph **G);

GraphStatus add_edge(Graph *G, int v1, int v2, int weight);
GraphStatus exist_edge(const Graph *G, int v1, int v2);
GraphStatus remove_edge(Graph *G, int v1, int v2);

int *neighbors(const Graph *G, int v, int *size);
int max_neighbors(const Graph *G);

GraphStatus adjacency_matrix(const Graph *G);

GraphStatus print_info(const Graph *G, int *arr, int size);

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

    int linhaValida[G->vertices];
    int colunaValida[G->vertices];
    for (int i = 0; i < G->vertices; i++) {
        linhaValida[i] = 0;
        colunaValida[i] = 0;
    }
    for(int i = 0; i<G->vertices; i++){
        for(int j = 0; j<G->vertices; j++){
            if(G->adjMtx[i][j]!= -1){
                linhaValida[i] = 1;
                colunaValida[j] = 1;
            }
        }
    }

    printf("Adjacency Matrix: \n");
    for(int i = 0; i<G->vertices; i++){
        if(!linhaValida[i])
            continue;
        for(int j = 0; j<G->vertices; j++){
            if(!colunaValida[j]) 
                continue;
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
    for (int i = 0; i < G->vertices; i++)
    {
        if (i != G->vertices-1)
            printf("%d, ", i+1);
        else
            printf("%d]\n", i+1);
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
                if(i<j){
                    printf("(%d, %d)", i + 1, j + 1);
                }
                else
                    printf("(%d, %d)", j + 1, i + 1);
                first = 0;
            }
        }
    }

    printf("]\n");

    return GRAPH_SUCCESS;
}


int main()
{
    int option = 0;
    int numVertices = 0, v1 = 0, v2 = 0, weight = 0;
    int answer = 0;
    bool printStatus = true, mtx = false;
    int *neighborsArr = NULL, size = 0;

    Graph *graph;

    do
    {
        scanf(" %d", &option);

        switch (option)
        {
        case -1:
            break;
        case 0:
            scanf(" %d", &numVertices);
            graph = create_graph(numVertices);
            break;
        case 1:
            scanf(" %d %d %d", &v1, &v2, &weight);
            add_edge(graph, v1, v2, weight);
            break;
        case 2:
            scanf(" %d %d", &v1, &v2);
            answer = (exist_edge(graph, v1, v2) == GRAPH_SUCCESS) ? 1 : 0;
            printStatus = false;
            break;
        case 3:
            scanf(" %d", &v1);
            neighborsArr = neighbors(graph, v1, &size);
            break;
        case 4:
            scanf(" %d %d", &v1, &v2);
    
            if (remove_edge(graph, v1, v2) == GRAPH_ERROR) {
                answer = -1;
                printStatus = false;
            }

            break;
        case 5:
            mtx = true;
            printStatus = false;
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
    } while (option != -1);

    if (printStatus)
        print_info(graph, neighborsArr, size);
    else if(mtx)
        adjacency_matrix(graph);
    else
        printf("%d\n", answer);

    destroy_graph(&graph);

    return 0;
}