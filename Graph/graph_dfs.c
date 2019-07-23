#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 11

typedef struct ADJ_LIST
{
    int item;
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
    for (i = 1; i < MAX_SIZE - 1; i++)
    {
        graph->vertices[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

ADJ_LIST *create_adj_list(int item)
{
    ADJ_LIST *new_adj_list = (ADJ_LIST *)malloc(sizeof(ADJ_LIST));
    new_adj_list->item = item;
    new_adj_list->next = NULL;

    return new_adj_list;
}

void add_edge(GRAPH *graph, int vertex1, int vertex2)
{
    ADJ_LIST *vertex = create_adj_list(vertex2);
    vertex->next = graph->vertices[vertex1];
    graph->vertices[vertex1] = vertex;

    //Undirected graph. Edge to the other direction as well.
    vertex = create_adj_list(vertex1);
    vertex->next = graph->vertices[vertex2];
    graph->vertices[vertex2] = vertex;
}

void dfs(GRAPH *graph, int source)
{
    graph->visited[source] = 1;
    printf("%d\n", source);

    ADJ_LIST *adj_list = graph->vertices[source];

    while (adj_list != NULL)
    {
        if (!graph->visited[adj_list->item])
        {
            dfs(graph, adj_list->item);
        }
        adj_list = adj_list->next;
    }
}

// TODO: consertar função (falha de segmentação)
void printing(GRAPH *graph)
{
    int i;
    ADJ_LIST *temp;
    for (i = 1; i <= MAX_SIZE - 1; i++)
    {
        temp = graph->vertices[i];
        printf("Vertex %2d: ", i);
        while (temp != NULL)
        {
            printf("%d  ==> ", temp->item);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
    GRAPH *undirected_graph = create_graph();

    add_edge(undirected_graph, 1, 2);
    add_edge(undirected_graph, 1, 5);
    add_edge(undirected_graph, 2, 5);
    add_edge(undirected_graph, 2, 3);
    add_edge(undirected_graph, 2, 4);
    add_edge(undirected_graph, 3, 4);
    add_edge(undirected_graph, 4, 5);

    // dfs(undirected_graph, 5);
    printing(undirected_graph);
    return 0;
}