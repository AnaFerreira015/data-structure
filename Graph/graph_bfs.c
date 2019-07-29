#include <stdio.h>
#include <stdlib.h>

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

typedef struct QUEUE
{
    int current_size;
    int head;
    int tail;
    int items[30];
} QUEUE;

QUEUE *create_queue()
{
    QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));

    queue->current_size = 0;
    queue->head = 0;
    queue->tail = MAX_SIZE - 1;

    return queue;
}

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
    ADJ_LIST *adj_list = (ADJ_LIST *)malloc(sizeof(ADJ_LIST));

    adj_list->item = item;
    adj_list->next = NULL;

    return adj_list;
}

int isEmpty(QUEUE *queue)
{
    return (queue->current_size == 0);
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

void enqueue(QUEUE *queue, int item)
{
    if (!(queue->current_size >= MAX_SIZE))
    {
        queue->tail = (queue->tail + 1) % MAX_SIZE;
        queue->items[queue->tail] = item;
        queue->current_size++;
    }
}

int dequeue(QUEUE *queue)
{
    if (!(queue->head >= MAX_SIZE))
    {
        int dequeue = queue->items[queue->head];
        queue->head = (queue->head + 1) % MAX_SIZE;
        queue->current_size--;
        return dequeue;
    }
}

void bfs(GRAPH *graph, int source)
{
    QUEUE *queue = create_queue();

    int dequeued;
    ADJ_LIST *adj_list = graph->vertices[source];
    graph->visited[source] = 1;
    enqueue(queue, source);

    while (!isEmpty(queue))
    {
        dequeued = dequeue(queue);
        adj_list = graph->vertices[dequeued];
        while (adj_list != NULL)
        {
            if (!graph->vertices[adj_list->item])
            {
                printf("%d", adj_list->item);
                graph->visited[adj_list->item] = 1;
                enqueue(queue, adj_list->item);
            }
            adj_list = adj_list->next;
        }
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

    add_edge(undirected_graph, 1, 2);
    add_edge(undirected_graph, 1, 5);
    add_edge(undirected_graph, 2, 5);
    add_edge(undirected_graph, 2, 3);
    add_edge(undirected_graph, 2, 4);
    add_edge(undirected_graph, 3, 4);
    add_edge(undirected_graph, 4, 5);

    // bfs(undirected_graph, 5);

    printing(undirected_graph);
    return 0;
}