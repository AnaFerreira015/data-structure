#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int dist[MAX_SIZE];
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
        graph->dist[i] = 0;
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

int bfs(GRAPH *graph, int source, int destiny)
{
    QUEUE *queue = create_queue();

    int dequeued;
    NODE *node = graph->vertices[source]->front;
    graph->visited[source] = 1;
    enqueue(queue, source);

    while (!isEmpty(queue))
    {
        dequeued = dequeue(queue);
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
                graph->dist[node->item] = graph->dist[dequeued] + 1;
            }
            node = node->next;
        }
    }
    return graph->dist[destiny];
}

int main()
{

    int test_cases, num_ilhas, num_pontes, u, v, i, j;

    scanf("%d", &test_cases);

    for (i = 0; i < test_cases; i++)
    {
        GRAPH *undirected_graph = create_graph();
        scanf("%d%d", &num_ilhas, &num_pontes);
        for (j = 0; j < num_pontes; j++)
        {
            scanf("%d%d", &u, &v);
            add_double_edge(undirected_graph, u, v);
        }
        int qtd_min = bfs(undirected_graph, 1, num_ilhas);
        if (qtd_min >= 1)
        {

            printf("%d\n", qtd_min);
        }
        else
        {
            printf("-1\n");
        }
    }
    return 0;
}