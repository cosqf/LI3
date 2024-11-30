#include <glib.h>

#ifndef _QUERYUTILS_H_
#define _QUERYUTILS_H_


typedef struct {
    int key;
    int value;
} Tuple;

int compareTuple(const void* a, const void* b);

void updateHash(int id, GHashTable* newtable, int newValue);

Tuple* sortHash (GHashTable* hash, int sorterFunc (const void*, const void*)) ;

#endif