#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>

#ifndef ENTITY_MANAGER_H 
#define ENTITY_MANAGER_H

//GHashTable *hashUser = g_hash_table_new(g_int_hash, g_int_equal);

typedef struct entityManager EntityManager;

EntityManager* initializeHash ();

void freeHash (EntityManager *mngr);

UserManager* getUserManager (EntityManager *mngr);
MusicManager* getMusicManager (EntityManager *mngr);
ArtistManager* getArtistManager (EntityManager *mngr);
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
