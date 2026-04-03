#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aluno:  Luís Gustavo Vieira Antoniosi   | NºUSP: 17067476
Aluno:  Luiz Filipe Sá Vioto            | NºUSP: 16886252
Aluno:  Matheus Gregório Muniz Arcanjo  | NºUSP: 16892051
Aluno:  Rafael Said Jannini             | NºUSP: 16898162
*/


//Diferentes status de saída
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
GraphStatus remove_edge(Graph *G, int v1, int v2);

int *neighbors(Graph *G, int v, int *size);
int max_neighbors(Graph *G);

GraphStatus adjacency_matrix(Graph *G);

GraphStatus print_info(Graph *G, int *arr, int size);

struct Graph
{
    int vertices;   //Número de vértices
    int **adjMtx;   //Matriz de adjacência
};

//Função auxiliar para verificar se o vérice é válido

int is_valid_vertex(const Graph *G, int v)
{
    return (v >= 1 && v <= G->vertices); //Precisa estar entre 1 e o número de vértices do grafo
}

//Funções do Grafo

//Função que cria um grafo
Graph *create_graph(int numVertices)
{
    Graph *G = (Graph *)malloc(sizeof(Graph)); //Aloca memória para o grafo

    if (G == NULL)
        return NULL; // Verificação do malloc

    G->vertices = numVertices;
    G->adjMtx = (int **)calloc(numVertices, sizeof(int *)); //Aloca memória para a matriz

    if (G->adjMtx == NULL)
        return NULL; //Verificação do malloc

    //Instanciando a matriz de adjacência 
    for (int i = 0; i < numVertices; i++)
    {
        G->adjMtx[i] = (int *)malloc(numVertices * (sizeof(int))); //Aloca memória para a linha da matriz

        if (G->adjMtx[i] == NULL)
            return NULL;    //Verificação do malloc

        for (int j = 0; j < numVertices; j++)
            G->adjMtx[i][j] = -1;   //Inicializa tudo com -1
    }

    return G;
}

//Função que destrói o grafo
GraphStatus destroy_graph(Graph **G)
{
    if (!G || !(*G))
        return GRAPH_FAILURE;

    for (int i = 0; i < (*G)->vertices; i++)
    {
        free((*G)->adjMtx[i]); //Libera memória das linhas da matriz de adjacência
    }

    free((*G)->adjMtx); //Libera a matriz de adjacência
    free(*G);   //Libera o grafo
    *G = NULL;  //Seta como nulo o ponteiro por segurança

    return GRAPH_SUCCESS;
}

//Função que adiciona aresta
GraphStatus add_edge(Graph *G, int v1, int v2, int weight)
{
    if (G == NULL)
        return GRAPH_ERROR;

    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    //Adiciona o peso das arestas na matriz
    G->adjMtx[v1 - 1][v2 - 1] = weight;
    G->adjMtx[v2 - 1][v1 - 1] = weight; //Como é não direcionado, é necessário adicionar aresta (a,b) e (b,a)

    return GRAPH_SUCCESS;
}

//Função que verifica se a aresta existe
GraphStatus exist_edge(Graph *G, int v1, int v2)
{
    if (G == NULL)
        return GRAPH_ERROR;
    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    //Caso o peso da aresta for -1 na matriz, significa que não existe
    if (G->adjMtx[v1 - 1][v2 - 1] == -1)
        return GRAPH_FAILURE;

    return GRAPH_SUCCESS;
}

//Função que remove aresta do grafo
GraphStatus remove_edge(Graph *G, int v1, int v2)
{
    if (G == NULL)
        return GRAPH_ERROR;

    if (!is_valid_vertex(G, v1) || !is_valid_vertex(G, v2))
        return GRAPH_ERROR;

    //Verificação extra, para ver se já está removido
    if (G->adjMtx[v1 - 1][v2 - 1] == -1)
        return GRAPH_ERROR;

    //Coloca o peso como -1, significando que está removido
    G->adjMtx[v1 - 1][v2 - 1] = -1;
    G->adjMtx[v2 - 1][v1 - 1] = -1;

    return GRAPH_SUCCESS;
}

//Função que retorna vetor de vizinhos de um vértice
int *neighbors(Graph *G, int v, int *size)
{
    if (!G)
        return NULL;
    if (!is_valid_vertex(G, v))
        return NULL;

    //Aloca o vetor de vértices
    int *adjacentVertices = (int *)malloc(G->vertices*sizeof(int));
    if (!adjacentVertices)
        return NULL;

    int tmpCount = 0;

    //Coloca valores na matriz de acordo com o vértice especificado
    for (int j = 0; j < G->vertices; j++)
    {
        if (G->adjMtx[v - 1][j] != -1)
        {
            adjacentVertices[tmpCount++] = j + 1;
        }
    }

    //Passando o tamanho do vetor por referência
    *size = tmpCount;

    return adjacentVertices;
}

//Retorna o vértice com a maior quantidade de vizinhos
int max_neighbors(Graph *G)
{
    if (G == NULL || G->adjMtx == NULL)
        return 0;

    int tmp = 0;
    int max = 0;
    int max_idx = 0;

    //Percorre a matriz inteira
    for (int i = 0; i < G->vertices; i++)
    {

        for (int j = 0; j < G->vertices; j++)
        {
            //Se houver um vizinho, aumenta o contador
            if (G->adjMtx[i][j] != -1)
                tmp++;
        }

        //Troca do contador temporário com o maior número de vizinhos até o momento
        if (tmp > max)
        {
            max = tmp; //Salva o novo maior número de vizinhos
            max_idx = i; //Salva o vérice com maior vizinhos
        }

        tmp = 0;
    }

    return max_idx + 1;
}

//Função que printa a matriz de adjacência
GraphStatus adjacency_matrix(Graph *G)
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

//Função que printa a informação necessária 
GraphStatus print_info(Graph *G, int *arr, int size)
{
    //Caso o vetor de vizinhos seja não nulo, imprime ele
    if (arr && size) {
        for (int i = 0; i < size; i++)
            printf("%d ", arr[i]);

        printf("\n");
        return GRAPH_SUCCESS;
    }
    if (G == NULL)
        return GRAPH_ERROR;

    //Caso o vetor de vizinhos seja nulo, imprime todos os vértices e as arestas
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
    bool printStatus = true, mtx = false, max = false;
    int *neighborsArr = NULL, size = 0;

    Graph *graph = NULL;

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
        case 6:
            answer = max_neighbors(graph);
            max = true;
            printStatus = false;
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
    } while (option != -1);

    if (printStatus)
        print_info(graph, neighborsArr, size);
    else if (mtx)
        adjacency_matrix(graph);
    else if (max)
        printf("max vertex: %d\n", answer);
    else
        printf("%d\n", answer);

    destroy_graph(&graph);

    return 0;
}