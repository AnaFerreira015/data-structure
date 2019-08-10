#include <stdio.h>
#include <stdlib.h>

typedef struct BINARY_TREE
{
    int item;
    int height;
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
    new_binary_tree->height = 0;

    return new_binary_tree;
}

BINARY_TREE *build_tree(BINARY_TREE *bt, int *items, int *children_left, int *children_right, int pos)
{
    if (pos == -1)
    {
        return NULL;
    }
    else
    {
        return create_binary_tree(items[pos], build_tree(bt, items, children_left, children_right, children_left[pos]), build_tree(bt, items, children_left, children_right, children_right[pos]));
    }
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
        // printf("Node %d: previous = %d next = %d\n", bt->left->item, bt->right->item, bt->item);
        printf("debug\n");
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

void main()
{
    int i, qtd_nodes;

    scanf("%d", &qtd_nodes);
    int child_left[qtd_nodes], child_right[qtd_nodes], root[qtd_nodes];

    for(i = 0; i < qtd_nodes; i++) {
        scanf("%d%d", &child_left[i], &child_right[i]);
    }

    scanf("%d", &root[0]);
    // for(i = 0; i < qtd_nodes; i++) {
    //     printf("left %d right %d\n", child_left[i], child_right[i]);
    // }

    BINARY_TREE *bt = create_empty_binary_tree();
    bt = build_tree(bt, root, child_left, child_right, 0);

    // printf("child_left %d\n", child_left[0]);
    // printf("left %d right %d\n", bt->left, bt->right);
    print_pre_order(bt);
    

}