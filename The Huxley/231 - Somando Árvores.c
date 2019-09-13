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

int main () {
    char *arvore;
    arvore = read_parenthesis_btree();
    // gets(arvore);
    // printf("%s\n", arvore);
    int size = strlen(arvore);
    printf("strlen da arvore %d\n", size);

    BINARY_TREE *bt = NULL;
    int i;
    // for(i = 0; i < size; i++) {
        bt = construct_btree(arvore, 0);
    // }

    // BINARY_TREE *bt = construct_btree(arvore, 0);

    return 0;
}