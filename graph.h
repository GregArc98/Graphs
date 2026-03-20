#ifndef GRAPH_H
    #define GRAPH_H
    typedef struct Graph GRAPH;
    GRAPH* MyGraph(int v);
    void add_edge(GRAPH* G,int v1, int v2, int peso); 
    int exist_edge(GRAPH* G, int v1, int v2);
    int* neighbors(GRAPH* G, int v);
    void remove_edge(GRAPH* G,int v1,int v2); 
    void print_info(GRAPH* G);
    void remove_graph(GRAPH** G); 
    int max_neighbors(GRAPH* G);
    int** adjacency_matrix(GRAPH *G);
#endif