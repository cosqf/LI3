#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef HASH_TABLE_H 
#define HASH_TABLE_H

typedef struct {
    GHashTable *table;
} HashTable;

HashTable* create_hash_table(); // Função para criar uma hashtable

void free_hash_table(HashTable *ht); // Liberta o espaço da hashtable

void insert_into_hash_table(HashTable *ht, const char *key, const char *value); // Adiciona um elemento à hashtable

const char* lookup_in_hash_table(HashTable *ht, const char *key); // Função de busca na hashtable

#endif
