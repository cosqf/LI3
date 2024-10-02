#include <stdio.h>
#ifndef _MUSICS_H_
#define _MUSICS_H_

typedef struct {
    int hours;     //hh (00-99)
    int minutes;   //mm (00-59)
    int seconds;   //ss (00-59)
} Duration;

typedef struct {
    int id;              //– identificador único da música;
    char* title;         //– nome da música;
    char* artist_id;     //– lista de identificadores dos autores da música;
    Duration duration;   //– tempo de duração;
    char* genre;         //– género da música;
    int year;            //– ano de lançamento;
    char* lyrics;        //– letra da música.
} Music;

#endif  
