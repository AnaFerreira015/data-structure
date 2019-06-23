#include <stdlib.h>
#include <stdio.h>

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
        printf("%d\n", current->num);
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
    int element, i, size_list, search_item, delete_item;

    printf("Size and element: \n");
    scanf("%d %d\n", &size_list, &element);

    NODE *head = creating_element(element);

    for (i = 0; i < size_list - 1; i++)
    {
        scanf("%d", &element);
        add_tail(head, element);
        // head = add_head(head, element);
    }
    printf("\n");
    printing_list(head);

    // printf("\nEnter the search item: \n");
    // scanf("%d", &search_item);

    // search(head, search_item);

    // printf("\nEnter the delete item: \n");
    // scanf("%d", &delete_item);

    // head = search_delete(head, delete_item);

    // printf("\n");
    // printing_list(head);
    return 0;
}