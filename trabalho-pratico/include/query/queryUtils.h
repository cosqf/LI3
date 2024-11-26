#include <hashtableManager.h>
#include <glib.h>

#ifndef _QUERYUTILS_H_
#define _QUERYUTILS_H_


typedef struct {
    int key;
    int duration;
} Tuple;


int compareTuple(const void* a, const void* b);

Tuple* sortHash (GHashTable* hash);

#endif