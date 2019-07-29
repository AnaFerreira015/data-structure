#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float current;
float decreases;
int count = 0;
int aux = 0;
int compare = 0;

typedef struct NODE
{
    int element;
    struct NODE *next;
} NODE;

typedef struct HASTABLE
{
    struct ELEMENT *table[500001];
} HASHTABLE;

typedef struct ELEMENT
{
    int key;
    struct NODE *value;
} ELEMENT;

int hash_f(int k)
{
    return (k % (int)current);
}

HASHTABLE *creating_hash(int e)
{
    HASHTABLE *new_hash = (HASHTABLE *)malloc(sizeof(HASHTABLE));

    int index;
    for (index = 0; index < e; index++)
    {
        new_hash->table[index] = NULL;
    }

    return new_hash;
}

int has(HASHTABLE *hash_table, int e)
{
    int new_hash = hash_f(e);

    if (hash_table->table[new_hash] == NULL)
    {
        return 0;
    }

    NODE *temp = hash_table->table[new_hash]->value;

    while (temp != NULL)
    {
        compare += 1;
        if (temp->element == e)
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

NODE *deleting_node(NODE *node, int e)
{
    NODE *current = node;
    NODE *previous = NULL;

    while (current != NULL && current->element != e)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return node;
    }

    if (previous == NULL)
    {
        node = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    return node;
}

int del(HASHTABLE *hash_table, int key)
{
    int new_hash = hash_f(key);

    int v = 0;

    if (hash_table->table[new_hash] == NULL)
    {
        return 0;
    }

    NODE *temp = hash_table->table[new_hash]->value;
    v = has(hash_table, key);
    if (v)
    {
        decreases--;
    }
    hash_table->table[new_hash]->value = deleting_node(temp, key);

    return v;
}

HASHTABLE *put(HASHTABLE *hash_table, int key, int e)
{
    int new_hash = hash_f(key);

    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->element = key;

    if (hash_table->table[new_hash] == NULL)
    {
        hash_table->table[new_hash] = (ELEMENT *)malloc(sizeof(ELEMENT));
        hash_table->table[new_hash]->value = NULL;
        aux = 1;
    }
    else
    {
        NODE *temp = hash_table->table[new_hash]->value;
        while (temp != NULL)
        {
            compare++;
            if (temp->element == key)
            {
                aux = 0;
                return hash_table;
            }
            temp = temp->next;
        }
    }

    new_node->next = hash_table->table[new_hash]->value;
    hash_table->table[new_hash]->value = new_node;
    aux = 1;
    decreases++;

    return hash_table;
}

int max(HASHTABLE *hash_table)
{
    int max = 0, index, amount;

    for (index = 0; index < current; index++)
    {
        amount = 0;
        if (hash_table->table[index] != NULL)
        {
            NODE *temp = hash_table->table[index]->value;
            while (temp != NULL)
            {
                amount++;
                temp = temp->next;
            }
        }
        if (max < amount)
        {
            max = amount;
        }
    }
    return max;
}

HASHTABLE *test(HASHTABLE *hash_table)
{
    int index, k, i_aux = 0;
    decreases = 0;
    int array[500001];

    HASHTABLE *new_hash = creating_hash(500001);

    for (index = 0; index < (current / 2) + 1; index++)
    {
        if (hash_table->table[index] != NULL)
        {
            i_aux = 0;
            NODE *aux = hash_table->table[index]->value;
            hash_table->table[index] = NULL;
            while (aux != NULL)
            {
                array[i_aux++] = aux->element;
                aux = aux->next;
            }

            for (k = 0; k < i_aux; k++)
            {
                new_hash = put(new_hash, array[k], array[k]);
            }
        }
    }
    return new_hash;
}

int main()
{
    int index, element_k, result;

    HASHTABLE *new_hash_table = creating_hash(500001);

    char operation[20];
    current = 7.0;
    element_k = 0.0;
    decreases = 0;

    while (scanf("%s %d", operation, &element_k) != EOF)
    {
        if (strcmp(operation, "ADD") == 0)
        {
            new_hash_table = put(new_hash_table, element_k, element_k);
            printf("%d %d %d\n", count, aux, compare);
            if ((float)(decreases / current) >= 0.75)
            {
                current = (2 * current) - 1;
                new_hash_table = test(new_hash_table);
            }
        }
        else if (strcmp(operation, "DEL") == 0)
        {
            result = del(new_hash_table, element_k);
            printf("%d %d %d\n", count, result, compare);
        }
        else if (strcmp(operation, "HAS") == 0)
        {
            result = has(new_hash_table, element_k);
            printf("%d %d %d\n", count, aux, compare);
        }
        else
        {
            printf("%d %.0f %.0f %d\n", count, current, decreases, max(new_hash_table));
        }
        compare = 0;
        aux = 0;
        count++;
    }

    return 0;
}