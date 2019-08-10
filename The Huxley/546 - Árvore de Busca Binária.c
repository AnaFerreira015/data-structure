#include <stdlib.h>
#include <stdio.h>
 
typedef struct NODE_TREE
{
    int value;
    struct NODE_TREE *next;
    struct NODE_TREE *previous;
} NODE_TREE;
 
void verify_binary_search(NODE_TREE *node, int *vector, int pos, int *flag)
{ 
    if (node == NULL || flag == 0)
    {
        return;
    }
    else
    {
        if (node->previous != NULL && node->previous->value > node->value)
        {
            *flag = 0;
            return;
        }
        else if (node->next != NULL && node->next->value < node->value)
        {
            *flag = 0;
            return;
        }
        else
        {
            verify_binary_search(node->previous, vector, pos + 1, flag);
            verify_binary_search(node->next, vector, pos + 1, flag);
        }
    }
}
 
void printing_tree(NODE_TREE *node)
{
    if (node != NULL)
    {
        printing_tree(node->previous);
        printf("%d ", node->value);
        printing_tree(node->next);
    }
}

void dfs(NODE_TREE *node, int *pos, int posAux, int value)
{
    if (node == NULL)
    {
        return;
    }
    else if (node->value == value)
    {
        *pos = posAux;
    }
    else
    {
        dfs(node->previous, pos, posAux + 1, value);
        dfs(node->next, pos, posAux + 1, value);
    }
}
 
void read_tree(char *tree_vector)
{
    int i = 0;
    char enter;
    scanf("%c", &enter);
    while (enter != '\n')
    {
        // printf("%c", enter);
        tree_vector[i++] = enter;
        scanf("%c", &enter);
    }
    printf("\n");
    tree_vector[i] = '\0';
}
 
int numberF(char *tree_vector, int *pos)
{
    int i;
    int number = 0;
 
    for (i = *pos; tree_vector[i] >= 48 && tree_vector[i] <= 70; i++)
    {
        number = (number * 10) + (tree_vector[i] - 48);
    }
    *pos = i;
 
    return number;
}
 
void treeAux(char *tree_vector, int *pos, NODE_TREE **node)
{
    int number;
    if (tree_vector[*pos] == '(' && tree_vector[*pos + 1] == ')')
    {
        (*pos) += 2;
        *node = NULL;
    }
    else if (tree_vector[*pos] == ')')
    {
        (*pos)++;
    }
    else
    {
        (*pos)++;
 
        number = numberF(tree_vector, pos);
 
        NODE_TREE *new_node = (NODE_TREE *)malloc(sizeof(NODE_TREE));
        new_node->value = number;
        *node = new_node;
 
        treeAux(tree_vector, pos, &((*node)->previous));
        treeAux(tree_vector, pos, &((*node)->next));
 
        (*pos)++;
    }
}
 
NODE_TREE *tree(char *tree_vector)
{
    NODE_TREE *root = (NODE_TREE *)malloc(sizeof(NODE_TREE));
 
    int pos = 1;
 
    root->value = numberF(tree_vector, &pos);
 
    treeAux(tree_vector, &pos, &(root->previous));
    treeAux(tree_vector, &pos, &(root->next));
 
    return root;
}
 
int main()
{
    int node, flag = 1, vector[100];
    char tree_vector[100];
 
    // read_tree(tree_vector);
    scanf("%[^\n]", tree_vector);
    NODE_TREE *root = tree(tree_vector);
 
    vector[0] = root->value;
   
    verify_binary_search(root, vector, 1, &flag);
 
    if (flag)
    {
        printf("VERDADEIRO\n");
    }
    else
    {
        printf("FALSO\n");
    }
 
    return 0;
}