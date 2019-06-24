#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int num;
    struct NODE *previous;
    struct NODE *next;
} NODE;

NODE *creating_element(int e)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->num = e;
    new_node->previous = NULL;
    new_node->next = NULL;

    return new_node;
}

NODE *add_head(NODE *node, int e)
{
    NODE *new_node = creating_element(e);
    new_node->next = node;
    node->previous = new_node;
    new_node->previous = NULL;

    return new_node;
}

NODE *add_tail(NODE *node, int e)
{
    if (node->next != NULL)
    {
        return add_tail(node->next, e);
    }
    NODE *new_node = creating_element(e);
    node->next = new_node;
    new_node->previous = node;
    new_node->next = NULL;

    return new_node;
}

void printing_list(NODE *node)
{
    if (node->next != NULL)
    {
        printf("%d -> ", node->num);
        return printing_list(node->next);
    }
    printf("%d\n", node->num);
}

int main()
{
    int element, i, size_list;

    printf("Size and element: \n");
    scanf("%d %d\n", &size_list, &element);

    NODE *head = creating_element(element);
    NODE *end;

    for (i = 0; i < size_list - 1; i++)
    {
        scanf("%d", &element);
        end = add_tail(head, element);
        // head = add_head(head, element);
    }

    printf("\n");
    printing_list(head);
    return 0;
}