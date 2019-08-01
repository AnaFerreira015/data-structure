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

BINARY_TREE *create_binary_tree(int item, BINARY_TREE *left, BINARY_TREE *right)
{
    BINARY_TREE *new_binary_tree = (BINARY_TREE *)malloc(sizeof(BINARY_TREE));

    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;
    new_binary_tree->height = 0;

    return new_binary_tree;
}

BINARY_TREE *tree(BINARY_TREE *bt, int *items, int *children_left, int *children_right, int pos)
{
    if(pos == -1) {
        return NULL;
    }else {
        return create_binary_tree(items[pos], tree(bt, items, children_left, children_right, children_left[pos]), tree(bt, items, children_left, children_right, children_right[pos]));
    }
}

void print_in_order(BINARY_TREE *bt)
{
    if (!isEmpty(bt))
    {
        print_in_order(bt->left);
        printf("value: %d level: %d\n\n", bt->item, bt->height+1);
        print_in_order(bt->right);
    }
}

void print_pre_order(BINARY_TREE *bt)
{
  if(!isEmpty(bt))
  {
 
    printf("value: %d level: %d\n\n", bt->item, bt->height+1);
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
        printf("value: %d level: %d\n\n", bt->item, bt->height+1);
    }
}

void level(BINARY_TREE *bt, int amount)
{
  if(bt != NULL)
  {
    bt->height = ++amount;
    level(bt->left, bt->height);
    level(bt->right, bt->height);
  }
}

int main () {
    int n, i;
    scanf("%d", &n);

    int items[n], child_left[n], child_right[n];

    for(i = 0; i < n; i++) {
        scanf("%d%d%d", &items[i], &child_left[i], &child_right[i]);
    }

    BINARY_TREE *bt = NULL;
    bt = tree(bt, items, child_left, child_right, 0);
    level(bt, -1);

    // print_pre_order(bt);
    // print_in_order(bt);
    // print_post_order(bt);


    return 0;
}