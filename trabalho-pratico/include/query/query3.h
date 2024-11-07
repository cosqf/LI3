#include <cmd.h>
#include <userManager.h>
#include <musicManager.h>

#ifndef _QUERY3_H_
#define _QUERY3_H_

typedef struct {
    char* genre;
    int likes;
} TupleMusics;


void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr, int);

//void iter_hash (GHashTable* userHashTable, GHashTable* musicHashTable, int AgeMin, int AgeMax);

void addToResults(TupleMusics *array, Genre genre);

void defineGenre (TupleMusics *array);

int compareLikes(const void* a, const void* b);

#endif  
