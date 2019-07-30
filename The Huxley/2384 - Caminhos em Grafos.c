#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 15

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
    for (i = 0; i < MAX_SIZE; i++)
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

void dfs(GRAPH *graph, int destiny)
{
    graph->visited[destiny] = 1;

    ADJ_LIST *adj_list = graph->vertices[destiny];

    while (adj_list != NULL)
    {
        if (!graph->visited[adj_list->item])
        {
            dfs(graph, adj_list->item);
        }
        adj_list = adj_list->next;
    }
}

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

    int v, p, i, v1, v2, o, d;
    scanf("%d %d", &v, &p);

    for (i = 0; i < p; i++)
    {
        scanf("%d %d", &v1, &v2);
        add_edge(undirected_graph, v1, v2);
    }
    scanf("%d %d", &o, &d);

    dfs(undirected_graph, o);
    // for(i = 0; i < v; i++) {
    //     printf("visited %d\n", undirected_graph->visited[i]);
    // }

    if (undirected_graph->visited[d])
    {
        printf("EXISTE\n");
    }
    else
    {
        printf("NAO EXISTE\n");
    }
    return 0;
}