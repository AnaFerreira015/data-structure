#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100000

typedef struct PAIR {
    int vertex;
    float weight;
} PAIR;

typedef struct ADJ_LIST
{
    PAIR items;
    struct ADJ_LIST *next;
} ADJ_LIST;

typedef struct GRAPH
{
    ADJ_LIST *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
} GRAPH;

GRAPH *create_graph()
{
    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        graph->vertices[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

ADJ_LIST *create_adj_list(float weight, int vertex)
{
    ADJ_LIST *adj_list = (ADJ_LIST *)malloc(sizeof(ADJ_LIST));

    adj_list->items.weight = weight;
    adj_list->items.vertex = vertex;
    adj_list->next = NULL;

    return adj_list;
}

void restarts_visited(GRAPH *undirected_graph) {
    int i;
    for(i = 0; i < MAX_SIZE; i++) {
        undirected_graph->visited[i] = 0;
    }
}

// TODO tirar o ponteiro para ponteiro
void inserts_end(ADJ_LIST **head_list, int vertex, float weight) {
    if((*head_list) == NULL) {
        (*head_list) = create_adj_list(vertex, weight);
    } else {
        ADJ_LIST *temp = (*head_list);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = create_adj_list(vertex, weight);        
    }
}

// TODO tirar a referência para ponteiro
void add_edge(GRAPH *undirected_graph, int vertex1, int vertex2, float weight) {
    inserts_end(&undirected_graph->vertices[vertex1], vertex2, weight);
    inserts_end(&undirected_graph->vertices[vertex2], vertex1, weight);
}

// TODO tirar o ponteiro para ponteiro
PAIR dequeue(ADJ_LIST **head) {
    PAIR values = (*head)->items;
    ADJ_LIST *temp = (*head);
    (*head) = (*head)->next;
    free(temp);

    return values;
}

void printing(GRAPH *undirected_graph, int numVertex) {
    int i;
    for(i = 0; i < numVertex; i++) {
        printf("lista %d: ", i);

        ADJ_LIST *temp = undirected_graph->vertices[i];

        if(temp == NULL) {
            printf("Lista vazia!\n");
            // TODO tirar continue
            continue;
        }

        while(temp != NULL) {
            printf("%d ", temp->items.vertex);
            temp = temp->next;
        }

        printf("\n");
    }
}

void bfs(GRAPH *undirected_graph, int source, float maxWeight){
    ADJ_LIST *head = NULL;
    undirected_graph->visited[source] = 1;

    inserts_end(&head, source, 0);

    while(head != NULL) {
        PAIR value = dequeue(&head);
        ADJ_LIST *adj_list = undirected_graph->vertices[value.vertex];;

        while(adj_list != NULL) {
            if(!(undirected_graph->visited[adj_list->items.vertex]) && value.weight + adj_list->items.weight <= maxWeight + 0.00001) {
                undirected_graph->visited[adj_list->items.vertex] = 1;
                printf("%d ", adj_list->items.vertex);
                inserts_end(&head, adj_list->items.vertex, value.weight + adj_list->items.weight);
            }
            adj_list = adj_list->next;
        }
    }
}

int main () {
    GRAPH *undirected_graph = create_graph();

    int nVertex, vertex1, vertex2, stop, i;
    float dist, weight;

    scanf("%d %f\n", &nVertex, &dist);
    scanf("%d %d %f %d", &vertex1, &vertex2, &weight, &stop);
    add_edge(undirected_graph, vertex1, vertex2, weight);

    while(stop) {
        scanf("%d %d %f %d", &vertex1, &vertex2, &weight, &stop);
        add_edge(undirected_graph, vertex1, vertex2, weight);
    }

    printf("impressao da lista de adjacencias do grafo:\n");
    printing(undirected_graph, nVertex);

    printf("\nimprimindo vertices acessiveis:\n");
    for(i = 0; i < nVertex; i++) {
        restarts_visited(undirected_graph);
        printf("[%d]: %d ", i, i);
        bfs(undirected_graph, i, dist);
        printf("\n");
    }
    return 0;
}