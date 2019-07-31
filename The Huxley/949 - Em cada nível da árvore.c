#include <stdlib.h>
#include <stdio.h>

typedef struct BINARY_TREE
{
    int item;
    int height;
    struct BINARY_TREE *left;
    struct BINARY_TREE *right;
} BINARY_TREE;

int maximum(int node_left, int node_right)
{
    return (node_left > node_right) ? node_left : node_right;
}

int height(BINARY_TREE *binary_tree)
{
    if (binary_tree == NULL)
    {
        return -1;
    }
    else
    {
        return 1 + maximum(height(binary_tree->left), height(binary_tree->right));
    }
}

int is_balanced(BINARY_TREE *binary_tree)
{
    int bf = height(binary_tree->left) - height(binary_tree->right);
    return ((-1 <= bf) && (bf <= 1));
}

int balance_factor(BINARY_TREE *binary_tree)
{
    if (binary_tree == NULL)
    {
        return 0;
    }
    else if ((binary_tree->left != NULL) && (binary_tree->right != NULL))
    {
        return (binary_tree->left->height - binary_tree->right->height);
    }
    else if ((binary_tree->left != NULL) && (binary_tree->right == NULL))
    {
        return (1 + binary_tree->left->height);
    }
    else
    {
        return (-binary_tree->right->height - 1);
    }
}

BINARY_TREE *rotate_left(BINARY_TREE *binary_tree)
{
    BINARY_TREE *subtree_root = NULL;

    if (binary_tree != NULL && binary_tree->right != NULL)
    {
        subtree_root = binary_tree->right;
        binary_tree->right = subtree_root->left;
        subtree_root->left = binary_tree;
    }

    subtree_root->height = height(subtree_root);
    binary_tree->height = height(binary_tree);

    return subtree_root;
}

BINARY_TREE *rotate_right(BINARY_TREE *binary_tree)
{
    BINARY_TREE *subtree_root = NULL;

    if (binary_tree != NULL && binary_tree->left != NULL)
    {
        subtree_root = binary_tree->left;
        binary_tree->left = subtree_root->right;
        subtree_root->right = binary_tree;
    }

    subtree_root->height = height(subtree_root);
    binary_tree->height = height(binary_tree);

    return subtree_root;
}

BINARY_TREE *create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right)
{
    BINARY_TREE *binary_tree = (BINARY_TREE *)malloc(sizeof(BINARY_TREE));

    binary_tree->left = left;
    binary_tree->right = right;
    binary_tree->item = item;
    binary_tree->height = 0;

    return binary_tree;
}

BINARY_TREE *add(BINARY_TREE *binary_tree, int item)
{
    if (binary_tree == NULL)
    {
        return create_binary_tree(item, NULL, NULL);
    }
    else if (binary_tree->item > item)
    {
        binary_tree->left = add(binary_tree->left, item);
    }
    else
    {
        binary_tree->right = add(binary_tree->right, item);
    }

    binary_tree->height = height(binary_tree);
    BINARY_TREE *child;

    if (balance_factor(binary_tree) == 2 || balance_factor(binary_tree) == -2)
    {
        if (balance_factor(binary_tree) == 2)
        {
            child = binary_tree->left;
            if (balance_factor(child) == -1)
            {
                binary_tree->left = rotate_left(child);
            }
            binary_tree = rotate_right(binary_tree);
        }
        else if (balance_factor(binary_tree) == -2)
        {
            child = binary_tree->right;
            if (balance_factor(child) == 1)
            {
                binary_tree->right = rotate_right(child);
            }
            binary_tree = rotate_left(binary_tree);
        }
    }
    return binary_tree;
}

int is_leaf(BINARY_TREE *binary_tree)
{
    return ((binary_tree->left == NULL) && (binary_tree->right == NULL));
}

int isEmpty(BINARY_TREE *binary_tree)
{
    return (binary_tree == NULL);
}

void print_pre_order(BINARY_TREE *binary_tree)
{
    if (!isEmpty(binary_tree))
    {
        printf("%d\n", binary_tree->item);
        print_pre_order(binary_tree->left);
        print_pre_order(binary_tree->right);
    }
}

void print_in_order(BINARY_TREE *binary_tree)
{
    if (!isEmpty(binary_tree))
    {
        print_in_order(binary_tree->left);
        printf("%d\n", binary_tree->item);
        print_in_order(binary_tree->right);
    }
}

void print_post_order(BINARY_TREE *binary_tree)
{
    if (!isEmpty(binary_tree))
    {
        print_post_order(binary_tree->left);
        print_post_order(binary_tree->right);
        printf("%d\n", binary_tree->item);
    }
}

int main () {
    int n, i, value, left, right;
    scanf("%d", &n);

    scanf("%d %d %d", &value, &left, &right);
    if(left == -1) {
        BINARY_TREE *binary_tree_leaf = create_binary_tree(4, NULL, NULL);
    }
    for(i = 0; i < n - 1; i++) {
        scanf("%d %d %d", &value, &left, &right);
    }
    return 0;
}