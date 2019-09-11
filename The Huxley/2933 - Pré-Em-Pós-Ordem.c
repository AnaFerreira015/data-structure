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

BINARY_TREE *create_node_binary_tree(int item)
{
    BINARY_TREE *new_binary_tree = (BINARY_TREE *)malloc(sizeof(BINARY_TREE));

    new_binary_tree->item = item;
    new_binary_tree->left = NULL;
    new_binary_tree->right = NULL;

    return new_binary_tree;
}

void print_in_order(BINARY_TREE *bt, int height)
{
    if (!isEmpty(bt))
    {
        print_in_order(bt->left, height + 1);
        int i;
        for (i = 0; i < height; i++) printf("\t");
        printf("%4d\n", bt->item);
        print_in_order(bt->right, height + 1);
    }
}

void print_pre_order(BINARY_TREE *bt, int height)
{
    if (!isEmpty(bt))
    {
        int i;
        for (i = 0; i < height; i++) printf("\t");
        printf("%4d\n", bt->item);
        print_pre_order(bt->left, height + 1);
        print_pre_order(bt->right, height + 1);
    }
}

void print_post_order(BINARY_TREE *bt, int height)
{
    if (!isEmpty(bt))
    {
        print_post_order(bt->left, height + 1);
        print_post_order(bt->right, height + 1);
        int i;
        for (i = 0; i < height; i++) printf("\t");
        printf("%4d\n", bt->item);
    }
}

void construct(BINARY_TREE *bt, int u, int left, int right) {
    if(bt == NULL) {
        return;
    } else {
        if(bt->item == u) {
            if(left != -1) {
                bt->left = create_node_binary_tree(left);
            }
            if (right != -1) {
                bt->right = create_node_binary_tree(right);
            }
        }
        construct(bt->left, u, left, right);
        construct(bt->right, u, left, right);
    }
}

int main()
{
    // BINARY_TREE *bt = create_binary_tree(6, create_binary_tree(4, NULL, NULL), create_binary_tree(9, create_binary_tree(1, NULL, NULL), create_binary_tree(2, NULL, NULL)));
    // print_in_order(bt);
    // print_post_order(bt);
    // print_pre_order(bt);
    int n, p, i, u, left, right;

    BINARY_TREE *bt = create_empty_binary_tree();
    
    scanf("%d%d", &n, &p);
    for(i = 0; i < p; i++) {
        scanf("%d%d%d", &u, &left, &right);
        construct(bt, u, left, right);
    }
    
    printf("vazia %d\n", bt == NULL);

    printf("Preorder print:\n");
    print_pre_order(bt, 0);
    
    printf("Inorder print:\n");
    print_in_order(bt, 0);
    
    printf("Postorder print:\n");
    print_post_order(bt, 0);
    return 0;
}