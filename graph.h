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
GraphStatus exist_edge(Graph *G, int v1, int v2);
int remove_edge(Graph *G, int v1, int v2);

int *neighbors(Graph *G, int v, int *size);
int max_neighbors(Graph *G);

int **adjacency_matrix(Graph *G);

GraphStatus print_info(Graph *G);

#endif