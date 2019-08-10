#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BTREE_STR_MAX_SIZE 1000
typedef struct btree BTree;

struct btree {
    int item;
    BTree *left;
    BTree *right;
};

BTree* create_empty_btree() {
    return NULL;
}

BTree* create_btree(int item, BTree *left, BTree *right) {
    BTree *new_bt = (BTree*)malloc(sizeof(BTree));
    new_bt->item = item;
    new_bt->left = left;
    new_bt->right = right;
    return new_bt;
}

bool is_empty(BTree *bt) {
    return (bt == NULL) ? true : false;
}

BTree* search(BTree *bt, int item) {
    if((is_empty(bt)) || (bt->item == item)) {
        return bt;
    }
    else if(bt->item > item) {
        return search(bt->left, item);
    }
    else {
        return search(bt->right, item);
    }
}

BTree* bst_add(BTree *bt, int item) {
    if(is_empty(bt)) {
        bt = create_btree(item, NULL, NULL);
    }
    else if(bt->item > item) {
        bt->left = bst_add(bt->left, item);
    }
    else {
        bt->right = bst_add(bt->right, item);
    }

    return bt;
}

char* read_parenthesis_btree() {
    char character;
    char *str = (char*)malloc(BTREE_STR_MAX_SIZE * sizeof(char));
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

void generate_parenthesis_btree(BTree *bt) {
    printf("(");
    if(!is_empty(bt)) {
        printf("%d", bt->item);
        generate_parenthesis_btree(bt->left);
        generate_parenthesis_btree(bt->right);
    }
    printf(")");
}

BTree* construct_btree(char* str, int *i) {

    BTree *bt = create_empty_btree();

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

        bt = create_btree(num, NULL, NULL);
        bt->left = construct_btree(str, i);
        bt->right = construct_btree(str, i);
    }

    (*i)++;
    return bt;
}

void print_pre_order(BTree *bt) {
    if(!is_empty(bt)) {
        printf("%d ", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

void print_in_order(BTree *bt) {
    if(!is_empty(bt)) {
        print_in_order(bt->left);
        printf("%d ", bt->item);
        print_in_order(bt->right);
    }
}

void print_post_order(BTree *bt) {
    if(!is_empty(bt)) {
        print_post_order(bt->left);
        print_post_order(bt->right);
        printf("%d ", bt->item);
    }
}

int main () {

    char *input = read_parenthesis_btree();
    BTree *bt = construct_btree(input, )
    return 0;
}