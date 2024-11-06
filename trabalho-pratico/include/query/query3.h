#include <cmd.h>
#include <userManager.h>

#ifndef _QUERY3_H_
#define _QUERY3_H_

typedef struct {
    char* genre;
    int likes;
} TupleMusics;

typedef enum {
    GENRE_METAL,
    GENRE_REGGAE,
    GENRE_JAZZ,
    GENRE_HIPHOP,
    GENRE_CLASSICAL,
    GENRE_ROCK,
    GENRE_BLUES,
    GENRE_COUNTRY,
    GENRE_POP,
    GENRE_ELECTRONIC
} GenreID;

void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr, int);

//void iter_hash (GHashTable* userHashTable, GHashTable* musicHashTable, int AgeMin, int AgeMax);

void addToResults(TupleMusics *array, const char* genre);

GenreID getGenreID(const char *genre) ;

void defineGenre (TupleMusics *array);

int compareLikes(const void* a, const void* b);

#endif  
