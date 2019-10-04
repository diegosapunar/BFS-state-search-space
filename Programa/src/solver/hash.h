#pragma once
#include "state.h"
#include "queue.h"
#include <stdbool.h>

struct hashnode
{
    bool free;           
    Queue* colisiones;      
};

typedef struct hashnode HashNode;

struct hashtable
{
    unsigned long long size;
    HashNode** array;
    int count;
};

typedef struct hashtable HashTable;


/* Inizializo mi HashTable del tamano de n. Parte bacia, es decir todos free */
HashTable *hashtable_init(int n);

bool hashtable_insert(HashTable* hashtable, State* state, int n);

HashTable *hashtable_rehash(HashTable *hashtable_antigua, int n);

void hashtable_destroy(HashTable* hashtable);