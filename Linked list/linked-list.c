#include <stdlib.h>
#include <stdio.h>

typedef struct NODE
{
    void *num;
    struct NODE *next;
} NODE;

NODE *creating_element(void *e)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->num = e;
    new_node->next = NULL;

    return new_node;
}

NODE *add_head(NODE *node, void *e)
{
    NODE *new_node = creating_element(&e);
    new_node->next = node;

    return new_node;
}

NODE *add_tail(NODE *node, void *e)
{
    if (node->next != NULL)
    {
        return add_tail(node->next, e);
    }
    NODE *new_node = creating_element(&e);
    node->next = new_node;

    return new_node;
}

void printing_list_integers(NODE *node){
    NODE *current = node;
    if(current->next != NULL){
        printf("%d\n", *((int*) node->num));
        return printing_list_integers(current->next);
    }
    printf("%d\n", *((int*) node->num));
}

/*
void printing_list(NODE *node)
{
    NODE *current = node;
    if (current->next != NULL)
    {
        printf("%d\n", current->num);
        return printing_list(current->next);
    }
    printf("%d\n", current->num);
} */

int integers_equals(void *item1, void *item2) {
    return (*((int*) item1) == *((int*) item2));
}

/** Recebe o nó da cabeça da lista, um elemento que será procurado
 * e um ponteiro para a função que vai fazer a busca 
 * search(list_of_integers, &i, integers_equals); */
NODE *search_integers(NODE *node, void *e, int(*equal)(void *item1, void *item2)) {
    if(node->next != NULL){
        if((*equal)(node->num, e)) {
            printf("Element %d is on the list\n", *((int*)node->num));
            return node;
        }
        else {
            return search_integers(node->next, e, equal);
        }
    }
    else {
        printf("Sorry, we didn't find element %d in the list\n", *((int*)e));
        return NULL;
    }
}

/*
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
} */

/** Recebe o nó cabeça da lista, um elemento que vai ser deletado 
 * e um ponteiro para função que realiza a busca */
NODE *search_delete_integers(NODE *node, void *e, int(*equal)(void *item1, void *item2)) {
    if((*equal)(node->num, e)) {
        NODE *temp = node->next;
        free(node);
        return temp;
    }
    else {
        node->next = search_delete_integers(node->next, e, equal);
    }
}

/*
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
} */

int main()
{
    int element, i, size_list, search_item, delete_item;

    printf("Size and element: \n");
    scanf("%d %d\n", &size_list, &element);

    NODE *head = creating_element(&element);

    for(i = 0; i < size_list - 1; i++){
        scanf("%d", &element);
        // TODO: consertar lixo de memória salvo pelo add_tail
        // add_tail(head, &element);
        // TODO: consertar lixo de memória salvo pelo add_head
        head = add_head(head, &element);
    }    
    printf("\n");
    printing_list_integers(head);

    printf("\nEnter the search item: \n");
    scanf("%d", &search_item);

    search_integers(head, &search_item, integers_equals);

    printf("\nEnter the delete item: \n");
    scanf("%d", &delete_item);

    head = search_delete_integers(head, &delete_item, integers_equals);
    printf("\n");
    printing_list_integers(head);

    // printf("Size and element: \n");
    // scanf("%d %d\n", &size_list, &element);

    // NODE *head = creating_element(element);

    // for (i = 0; i < size_list - 1; i++)
    // {
    //     scanf("%d", &element);
    //     add_tail(head, element);
    //     // head = add_head(head, element);
    // }
    // printf("\n");
    // printing_list(head);

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