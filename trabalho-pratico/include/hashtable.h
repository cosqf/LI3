#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef HASH_TABLE_H 
#define HASH_TABLE_H

//GHashTable *hashUser = g_hash_table_new(g_int_hash, g_int_equal);

extern GHashTable *hashUser;// Declara a hashUser globalmente, mas sem inicializá-la
extern GHashTable *hashArtist; // Declara a hashArtist globalmente, mas sem inicializá-la
extern GHashTable *hashMusic; // Declara a hashArtist globalmente, mas sem inicializá-la

void initialize_hash_table();// Função para inicializar a hash table

#endif


/*
typedef struct {
    GHashTable *table;
} HashTable;



HashTable* create_hash_table(); // Função para criar uma hashtable

void free_hash_table(HashTable *ht); // Liberta o espaço da hashtable

void insert_into_hash_table(HashTable *ht, const char *key, const char *value); // Adiciona um elemento à hashtable

const char* lookup_in_hash_table(HashTable *ht, const char *key); // Função de busca na hashtable
*/
