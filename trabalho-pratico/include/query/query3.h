#include <cmd.h>
#include <userManager.h>

#ifndef _QUERY3_H_
#define _QUERY3_H_

typedef struct {
    char* genre;
    int likes;
} TupleMusics;

void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr);

//void iter_hash (GHashTable* userHashTable, GHashTable* musicHashTable, int AgeMin, int AgeMax);
void addToResults(TupleMusics *array, char* genre);

void defineGender (TupleMusics *array);

#endif  
