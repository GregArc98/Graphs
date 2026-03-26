#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

int main()
{
    int option = 0;
    int numVertices = 0, v1 = 0, v2 = 0, weight = 0;
    int answer = 0;
    bool printStatus = true;
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
            answer = remove_edge(graph, v1, v2);
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
    } while (option != -1);

    if (printStatus)
        print_info(graph, neighborsArr, size);
    else
        printf("%d\n", answer);

    destroy_graph(&graph);

    return 0;
}