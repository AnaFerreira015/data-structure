#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 11

typedef struct ELEMENT
{
    int key;
    int value;
} ELEMENT;

typedef struct HASH_TABLE
{
    ELEMENT *table[MAX_SIZE];
} HASH_TABLE;

int hash(int key)
{
    return (key % MAX_SIZE);
}

// TODO: corrigir função contains_key
int contains_key(HASH_TABLE *HT, int key)
{
    int h = hash(key);
    return (HT->table[h]->key == key);
}

HASH_TABLE *creating_hash_table()
{
    HASH_TABLE *new_hash_table = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));

    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

void put(HASH_TABLE *HT, int key, int value)
{
    int h = hash(key);

    while (HT->table[h] != NULL)
    {
        if (HT->table[h]->key == key)
        {
            HT->table[h]->value = value;
            break;
        }
        h = hash(h + 1);
    }

    if (HT->table[h] == NULL)
    {
        ELEMENT *new_element = (ELEMENT *)malloc(sizeof(ELEMENT));
        new_element->key = key;
        new_element->value = value;
        HT->table[h] = new_element;
    }
}

int get(HASH_TABLE *HT, int key)
{
    int h = hash(key);

    while (HT->table[h] != NULL)
    {
        if (HT->table[h]->key == key)
        {
            return HT->table[h]->value;
        }
        h = hash(h + 1);
    }
    return -100;
}

void remove_value(HASH_TABLE *HT, int key)
{
    int h = hash(key);

    while (HT->table[h] != NULL)
    {
        if (HT->table[h]->key == key)
        {
            HT->table[h]->key = -1;
        }
        h = hash(h + 1);
    }
}

void print_hash_table(HASH_TABLE *HT)
{
    int i;

    for (i = 0; i < MAX_SIZE; i++)
    {
        if (HT->table[i] != NULL)
        {
            printf("Key: %d Value: %d\n", HT->table[i]->key, HT->table[i]->value);
        }
        else
        {
            printf("===================\n");
        }
    }
    // printf("\n");
}

int main()
{
    HASH_TABLE *new_hash_table = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));

    put(new_hash_table, 3, 1000);
    put(new_hash_table, 14, 2000);
    put(new_hash_table, 15, 3000);
    put(new_hash_table, 92, 4000);

    print_hash_table(new_hash_table);

    int value = get(new_hash_table, 14);
    printf("\nGet value result of key %d: %d\n", 14, value);

    // remove_value(new_hash_table, 14);
    // remove_value(new_hash_table, 15);
    // remove_value(new_hash_table, 92);
    // remove_value(new_hash_table, 3);

    // print_hash_table(new_hash_table);
    return 0;
}