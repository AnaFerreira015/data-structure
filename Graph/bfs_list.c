#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

typedef struct NODE
{
    int item;
    struct NODE *next;
} NODE;

typedef struct QUEUE
{
    NODE *head;
    NODE *tail;
    int size;
} QUEUE;

typedef struct ADJ_LIST
{
    NODE *front;
} ADJ_LIST;

typedef struct GRAPH
{
    ADJ_LIST *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
} GRAPH;

ADJ_LIST *create_adj_list(int item)
{
    ADJ_LIST *adj_list = (ADJ_LIST *)malloc(sizeof(ADJ_LIST));

    adj_list->front = (NODE *)malloc(sizeof(NODE));
    adj_list->front->item = item;
    adj_list->front->next = NULL;

    return adj_list;
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

NODE *creating_node(int item)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));

    node->item = item;
    node->next = NULL;

    return node;
}

QUEUE *create_queue()
{
    QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));

    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void printing_queue(QUEUE *queue)
{
    NODE *temp = queue->head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->item);
        temp = temp->next;
    }
}

int isEmpty(QUEUE *queue)
{
    return (queue->head == 0);
}

void enqueue(QUEUE *queue, int item)
{
    NODE *node = creating_node(item);
    if (queue->size == 0)
    {
        queue->head = node;
        queue->tail = node;
        queue->size++;
        return;
    }
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return;
}

int dequeue(QUEUE *queue)
{
    if (!queue->size)
    {
        printf("0 elementos\n");
        return 0;
    }
    if (queue->size == 1)
    {
        queue->size--;
        NODE *aux = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
        int value = aux->item;
        free(aux);
        return value;
    }
    NODE *aux = queue->head;

    int value = aux->item;

    queue->head = aux->next;
    queue->size--;
    free(aux);
    return value;
}

void add_edge(GRAPH *graph, int vertex1, int vertex2)
{
    if (graph->vertices[vertex1] == NULL)
    {
        graph->vertices[vertex1] = create_adj_list(vertex2);
    }
    else
    {
        NODE *node = creating_node(vertex2);
        NODE *new_node = graph->vertices[vertex1]->front;
        node->next = graph->vertices[vertex1]->front;
        graph->vertices[vertex1]->front = node;
    }
}

void bfs(GRAPH *graph, int source)
{
    QUEUE *queue = create_queue();

    int dequeued;
    NODE *node = graph->vertices[source]->front;
    graph->visited[source] = 1;
    enqueue(queue, source);

    while (!isEmpty(queue))
    {
        dequeued = dequeue(queue);
        printf("bfs %d\n", dequeued);
        if (graph->vertices[dequeued] == NULL)
        {
            continue;
        }
        node = graph->vertices[dequeued]->front;
        while (node != NULL)
        {
            if (graph->visited[node->item] == 0)
            {
                enqueue(queue, node->item);
                graph->visited[node->item] = 1;
            }
            node = node->next;
        }
    }
}

void printing(GRAPH *graph)
{
    int i;
    NODE *temp;
    for (i = 1; i <= MAX_SIZE - 1; i++)
    {
        if (graph->vertices[i] == NULL)
        {
            continue;
        }
        temp = graph->vertices[i]->front;
        printf("Vertex %2d: ", i);
        while (temp != NULL)
        {
            printf("%d  ==> ", temp->item);
            temp = temp->next;
        }
        printf("\n");
    }
}

void add_double_edge(GRAPH *graph, int vertex1, int vertex2)
{
    add_edge(graph, vertex1, vertex2);
    add_edge(graph, vertex2, vertex1);
}

int main()
{
    GRAPH *undirected_graph = create_graph();
    // add_edge(undirected_graph, 1, 2);
    add_double_edge(undirected_graph, 1, 2);
    add_double_edge(undirected_graph, 1, 5);
    add_double_edge(undirected_graph, 2, 5);
    add_double_edge(undirected_graph, 2, 3);
    add_double_edge(undirected_graph, 2, 4);
    add_double_edge(undirected_graph, 3, 4);
    add_double_edge(undirected_graph, 4, 5);

    // bfs(undirected_graph, 3);

    printing(undirected_graph);
    return 0;
}