#include <stdlib.h>
#include <stdio.h>

// TODO: Finalizar função de subconjunto

typedef struct NODE
{
    int num;
    struct NODE *next;
} NODE;

NODE *creating_element(int e)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->num = e;
    new_node->next = NULL;

    return new_node;
}

NODE *add_head(NODE *node, int e)
{
    NODE *new_node = creating_element(e);
    new_node->next = node;

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

    return new_node;
}

void printing_list(NODE *node)
{
    NODE *current = node;
    if (current->next != NULL)
    {
        printf("%d -> ", current->num);
        return printing_list(current->next);
    }
    printf("%d\n", current->num);
}

void search(NODE *node, int e)
{
    if (node->next != NULL)
    {
        if (node->num == e)
        {
            printf("Element %d is on the list\n", node->num);
        }
        else
        {
            return search(node->next, e);
        }
    }
    else
    {
        printf("Sorry, we didn't find element %d in the list\n", e);
    }
}

NODE *search_delete(NODE *node, int e)
{
    if (node->num == e)
    {
        NODE *temp = node->next;
        free(node);
        return temp;
    }
    else
    {
        node->next = search_delete(node->next, e);
    }
}

int main()
{
    int element, i, size_list1, size_list2;

    scanf("%d", &size_list1);
    scanf("%d", &element);

    NODE *head1 = creating_element(element);

    for (i = 0; i < size_list1 - 1; i++)
    {
        scanf("%d", &element);
        add_tail(head1, element);
    }
    printing_list(head1);

    scanf("%d", &size_list2);
    scanf("%d", &element);

    NODE *head2 = creating_element(element);

    for(i = 0; i < size_list2 - 1; i++){
        scanf("%d", &element);
        add_tail(head2, element);
    }
    printing_list(head2);
    return 0;
}