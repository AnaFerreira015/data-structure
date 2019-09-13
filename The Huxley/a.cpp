#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct pair PAIR;
typedef struct graph GRAPH;
typedef struct node NODE;
 
struct pair {
    int vertex;
    float weight;
};
 
struct node {
    NODE *next;
    PAIR values;
};
 
struct graph {
    bool visited[100000];
    NODE *adjList[100000];
};
 
GRAPH *createGraph() {
    GRAPH *newGraph = (GRAPH*)malloc(sizeof(GRAPH));
    int i;
    for (i = 0; i < 100000; i++) {
        newGraph->visited[i] = false;
        newGraph->adjList[i] = NULL;
    }
    return newGraph;
}
 
NODE *createNode(int vertex, float weight) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->values.vertex = vertex;
    newNode->values.weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
void insertEnd(NODE **head, int vertex, float connectionWeight) {
    if ((*head) == NULL) {
        (*head) = createNode(vertex, connectionWeight);
    } else {
        NODE *aux = (*head);
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = createNode(vertex, connectionWeight);
    }
}
 
// GRAFO N�O DIRECIONADO (U -> V e V -> U)
void addEdge(GRAPH *graph, int u, int v, float connectionWeight) {
    // Fazendo a aresta de u pra v com o peso de conexao connectionWeight
    insertEnd(&graph->adjList[u], v, connectionWeight);
    // Fazendo a aresta de v pra u com o peso de conexao connectionWeight
    insertEnd(&graph->adjList[v], u, connectionWeight);
}
 
void restartVisited(GRAPH *graph) {
    int i;
    for (i = 0; i < 100000; i++) {
        graph->visited[i] = false;
    }
}
 
PAIR dequeue(NODE **queueHead) {
    PAIR p = (*queueHead)->values;
    NODE *aux = (*queueHead);
    (*queueHead) = (*queueHead)->next;
    free(aux);
    return p;
}
 
void BFS(GRAPH *graph, int source, float maximumDistance) {
    NODE *queueHead = NULL; // FILA
    graph->visited[source] = true;
    insertEnd(&queueHead, source, 0); // INSERINDO O PRIMEIRO NO NA FILA
    while (queueHead != NULL) {
        PAIR p = dequeue(&queueHead);
        NODE *adjListAux = graph->adjList[p.vertex];
        while (adjListAux != NULL) {
            if (!(graph->visited[adjListAux->values.vertex]) && p.weight + adjListAux->values.weight <= maximumDistance + 0.00001) {
                graph->visited[adjListAux->values.vertex] = true;
                printf("%d ", adjListAux->values.vertex);
                insertEnd(&queueHead, adjListAux->values.vertex, p.weight + adjListAux->values.weight);
            }
            adjListAux = adjListAux->next;
        }
    }
}
 
void printAdjList(int numberOfVertex, GRAPH *graph) {
    int i;
    for (i = 0; i < numberOfVertex; i++) {
        printf("lista %d: ", i);
        NODE *aux = graph->adjList[i];
        if (aux == NULL) {
            printf("Lista vazia!\n");
            continue;
        }
        while (aux != NULL) {
            printf("%d ", aux->values.vertex);
            aux = aux->next;
        }
        printf("\n");
    }
}
 
int main() {
    GRAPH *graph = createGraph();
    int numberOfVertex;
    float limiarDistance;
    scanf("%d %f\n", &numberOfVertex, &limiarDistance);
    int u, v, flag;
    float connectionWeight;
    scanf("%d %d %f %d", &u, &v, &connectionWeight, &flag);
    addEdge(graph, u, v, connectionWeight);
    while (flag) {
        scanf("%d %d %f %d", &u, &v, &connectionWeight, &flag);
        addEdge(graph, u, v, connectionWeight);
    }
    printf("impressao da lista de adjacencias do grafo:\n");
    printAdjList(numberOfVertex, graph);
    printf("\nimprimindo vertices acessiveis:\n");
    int i;
    for (i = 0; i < numberOfVertex; i++) {
        restartVisited(graph);
        printf("[%d]: %d ", i, i);
        BFS(graph, i, limiarDistance);
        printf("\n");
    }
    return 0;
}