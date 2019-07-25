#include <stdio.h>
#include <stdlib.h>

typedef struct BINARY_TREE
{
    int item;
    struct BINARY_TREE *left;
    struct BINARY_TREE *right;
} BINARY_TREE;

int isEmpty(BINARY_TREE *bt)
{
    return (bt == NULL);
}

BINARY_TREE *create_empty_binary_tree()
{
    return NULL;
}

BINARY_TREE *create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right)
{
    BINARY_TREE *new_binary_tree = (BINARY_TREE *)malloc(sizeof(BINARY_TREE));

    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;

    return new_binary_tree;
}

void print_in_order(BINARY_TREE *bt)
{
    if (!isEmpty(bt))
    {
        print_in_order(bt->left);
        printf("%d\n", bt->item);
        print_in_order(bt->right);
    }
}

void print_pre_order(BINARY_TREE *bt)
{
    if (!isEmpty(bt))
    {
        printf("%d\n", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

void print_post_order(BINARY_TREE *bt)
{
    if (!isEmpty(bt))
    {
        print_post_order(bt->left);
        print_post_order(bt->right);
        printf("%d\n", bt->item);
    }
}

int main()
{
    BINARY_TREE *bt = create_binary_tree(6, create_binary_tree(4, NULL, NULL), create_binary_tree(9, create_binary_tree(1, NULL, NULL), create_binary_tree(2, NULL, NULL)));
    print_in_order(bt);
    // print_post_order(bt);
    // print_pre_order(bt);
    // BINARY_TREE *bt = create_empty_binary_tree();
    return 0;
}