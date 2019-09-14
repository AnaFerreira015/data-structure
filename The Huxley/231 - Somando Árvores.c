#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BINARY_TREE
{
    int item;
    struct BINARY_TREE *left;
    struct BINARY_TREE *right;
} BINARY_TREE;

int is_empty(BINARY_TREE *bt)
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

char* read_parenthesis_btree() {
    char character;
    char *str = (char*)malloc(256 * sizeof(char));
    int open_par = 0;
    int close_par = 0;
    int i = 0;

    scanf("%c", &character);
    while(1) {
        if(character != ' ' && character != '\n') {
            str[i++] = character;
        }

        if(character == '(') {
            open_par++;
        }
        else if(character == ')') {
            close_par++;
        }

        if(open_par == close_par) break;
        scanf("%c", &character);
    }

    str[i] = '\0';
    return str;
}

BINARY_TREE* construct_btree(char* str, int *i) {

    BINARY_TREE *bt = create_empty_binary_tree();

    if(str[(*i)++] == '(') {
        if(str[*i] == ')') {
            (*i)++;
            return NULL;
        }

        char str_num[10];
        int j = 0;
        int num;

        while(str[*i] != '(') {
            str_num[j++] = str[(*i)++];
        }

        str_num[j] = '\0';
        num = atoi(str_num);

        bt = create_binary_tree(num, NULL, NULL);
        bt->left = construct_btree(str, i);
        bt->right = construct_btree(str, i);
    }

    (*i)++;
    return bt;
}

void generate_parenthesis_btree(BINARY_TREE *bt) {
    printf("(");
    if(!is_empty(bt)) {
        printf("%d", bt->item);
        generate_parenthesis_btree(bt->left);
        generate_parenthesis_btree(bt->right);
    }
    printf(")");
}

void print_pre_order(BINARY_TREE *bt)
{
    if (!is_empty(bt))
    {
        printf("%d ", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

int is_leaf(BINARY_TREE *bt) {
    return ((bt->left == NULL) && (bt->right == NULL));
}

// void count_sum(BINARY_TREE *bt, int sum) {
//     int amount = 0;
//     if(!is_empty(bt)) {
//         if(!is_leaf(bt)) {
//             amount += bt->item;
//             count_sum(bt->left, sum);
//             count_sum(bt->right, sum);
//         }
//         else {
//             if(amount == sum) {
//                 printf("sim\n");
//             } else {
//                 printf("nao\n");
//             }
//             amount -= bt->item;
//         }
//     }
// }

void count_sum(BINARY_TREE *bt, int amount, int sum)
{
    if (!is_empty(bt))
    {
        if(is_leaf(bt)) {
            if(amount + bt->item == sum) {
                // printf("sim soma: %d amount: %d\n", sum, amount);
                printf("sim\n");
                return;
            }
            else{
                printf("nao\n");
                // printf("nao soma: %d amount: %d\n", sum, amount);
            }
        }
        // printf("bt->item %d\n", bt->item);
        count_sum(bt->left, amount + bt->item, sum);
        count_sum(bt->right, amount + bt->item, sum);
    } 
    // else{
    //     printf("nao\n");
    // }
}

int main () {
    char *arvore;
    int size, i, aux = 0, sum;
    BINARY_TREE *bt = NULL;

    // while(scanf("%d", &sum) != -1000) {
    //     arvore = read_parenthesis_btree();
        
    //     printf("%s\n", arvore);
        
    //     size = strlen(arvore);

    //     bt = construct_btree(arvore, &aux);

    //     count_sum(bt, sum);
        
    //     printf("pre_order\n");
    //     print_pre_order(bt);
    //     printf("\n");
    // }

    scanf("%d", &sum);
    // printf("sum: %d\n", sum);
    // printf("sum %d\n", sum);

    while(sum != -1000){
        arvore = read_parenthesis_btree();
        // printf("%s\n", arvore);
        
        size = strlen(arvore);

        bt = construct_btree(arvore, &aux);

        count_sum(bt, 0, sum);
        
        // printf("pre_order\n");
        // print_pre_order(bt);
        // printf("\n");  

        scanf("%d", &sum);
        // printf("sum: %d\n", sum);
    }
    return 0;
}