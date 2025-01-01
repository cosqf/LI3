#include <glib.h>

#ifndef _QUERYUTILS_H_
#define _QUERYUTILS_H_


typedef struct {
    int key;
    int value;
} Tuple;

/**
 * @brief Compares two tuples for sorting, in descending order. If values are equal, sorts by key in ascending order.
 *
 * @param a Pointer to the first tuple.
 * @param b Pointer to the second tuple.
 * 
 * @return -1 if a is bigger than b, 1 if b is bigger than a, 0 if equal.
 */
int compareTuple(const void* a, const void* b);

/**
 * @brief Updates or inserts an entry in a hash table.
 * If the ID already exists, increments its value by the new value. Otherwise, inserts a new entry.
 *
 * @param table Pointer to the hash table.
 * @param id The key representing the artist ID.
 * @param newValue The value to insert or add to the existing value.
 */
void updateHash(GHashTable* newtable, int id, int newValue);

/**
 * @brief Converts a hash table into a sorted array of tuples.
 * Transforms the hash table into an array of tuples, then sorts the array using the provided comparison function.
 *
 * @param hash Pointer to the hash table.
 * @param sorterFunc Function used to sort the tuples.
 * 
 * @return Pointer to the sorted tuple array, or NULL if the table is empty.
 */
Tuple* sortHash (GHashTable* hash, int sorterFunc (const void*, const void*)) ;

/**
 * @brief This function traverses a hash table and returns a @ Tuple with the biggest value.
 * 
 * @param table A pointer to the hash table.
 * 
 * @return A tuple with the key and value.
 */
Tuple getBiggestFromHash (GHashTable* table);

/**
 * @brief Formats the user ID from an @c int to a string.
 * 
 * @param id The ID in integer format.
 * 
 * @return The string with the proper ID format.
 */
char* formatUserID (int id);

#endif