#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

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

BINARY_TREE *build(int i, BINARY_TREE *bt, int *nodes, int max_size_nodes)
{
    if(bt == NULL) {
        bt = create_binary_tree(nodes[i], NULL, NULL);
    } 
    if(i * 2 > max_size_nodes || i * 2 + 1 > max_size_nodes) {
        return bt;
    }
    // printf("build\n");
    bt->left = build(i * 2, bt->left, nodes, max_size_nodes);
    bt->right = build(i * 2 + 1, bt->right, nodes, max_size_nodes);
    return bt;
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

void check_higher_value(BINARY_TREE *bt, int mult_factor, int *bigger) {
    if(bt == NULL) {
        return;
    }
    else {
        mult_factor *= bt->item;
        if(*bigger < mult_factor) {
        // printf("debug\n");
            *bigger = mult_factor;
        }
        check_higher_value(bt->left, mult_factor, bigger);
        check_higher_value(bt->right, mult_factor, bigger);
    }
}

int main (){
    BINARY_TREE *bt = create_empty_binary_tree();

    int h, i = 1;
    scanf("%d", &h);

    int nodes[(int)(pow(2, h))], pos = 1;

    while(scanf("%d", &nodes[i]) != EOF){
        i++;
    }

    bt = build(pos, bt, nodes, i - 1);

    int lower_value = INT_MIN;

    // print_pre_order(bt);
    check_higher_value(bt, 1, &lower_value);
    printf("%d\n", lower_value);
    return 0;
}