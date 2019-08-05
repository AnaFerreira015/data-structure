#include <stdio.h>
#include <stdlib.h>

typedef struct BINARY_TREE
{
    int item;
    int height;
    struct BINARY_TREE *left;
    struct BINARY_TREE *right;
} BINARY_TREE;

void level(BINARY_TREE *bt, int amount)
{
    if (bt != NULL)
    {
        bt->height = ++amount;
        level(bt->left, bt->height);
        level(bt->right, bt->height);
    }
}

int isEmpty(BINARY_TREE *bt)
{
    return (bt == NULL);
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

void to_compare(BINARY_TREE *bt, int *bigger, int *smaller, int *size_level)
{
    if (bt != NULL)
    {
        //   printf("%d %d\n", bt->item, bigger[bt->height]);
        if (bt->height > *size_level)
            *size_level = bt->height;
        if (bt->item > bigger[bt->height])
        {
            bigger[bt->height] = bt->item;
        }
        if (bt->item < smaller[bt->height])
        {
            smaller[bt->height] = bt->item;
        }
        to_compare(bt->left, bigger, smaller, size_level);
        to_compare(bt->right, bigger, smaller, size_level);
    }
}

void print_in_order(BINARY_TREE *bt)
{
    if (!isEmpty(bt))
    {
        print_in_order(bt->left);
        printf("value: %d level: %d\n\n", bt->item, bt->height + 1);
        print_in_order(bt->right);
    }
}

void print_pre_order(BINARY_TREE *bt)
{
    if (!isEmpty(bt))
    {

        printf("value: %d level: %d\n\n", bt->item, bt->height + 1);
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
        printf("value: %d level: %d\n\n", bt->item, bt->height + 1);
    }
}

BINARY_TREE *create_empty_binary_tree()
{
    return NULL;
}

void main()
{
    int n, i;
    scanf("%d", &n);

    int items[n], child_left[n], child_right[n], size_level = 0, bigger[n], smaller[n];

    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d", &items[i], &child_left[i], &child_right[i]);
        smaller[i] = (1 << 20);
        bigger[i] = -(1 << 20);
    }

    BINARY_TREE *bt = create_empty_binary_tree();
    bt = build_tree(bt, items, child_left, child_right, 0);
    level(bt, -1);
    to_compare(bt, bigger, smaller, &size_level);

    // print_pre_order(bt);
    // print_in_order(bt);
    // print_post_order(bt);

    if (bt != NULL)
    {
        size_level++;
    }
    for (i = 0; i < size_level; i++)
    {
        printf("Nivel %d: Maior = %d, Menor = %d\n", i + 1, bigger[i], smaller[i]);
    }
}