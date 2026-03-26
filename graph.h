#ifndef GRAPH_H
#define GRAPH_H

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

int **adjacency_matrix(const Graph *G);

GraphStatus print_info(const Graph *G, int *arr, int size);

#endif