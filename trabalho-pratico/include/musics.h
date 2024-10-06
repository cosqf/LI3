#include <stdio.h>
#ifndef _MUSICS_H_
#define _MUSICS_H_

typedef struct {
    int hours;     //hh (00-99)
    int minutes;   //mm (00-59)
    int seconds;   //ss (00-59)
    short int error; 
} Duration;

typedef struct {
    int id;              //– identificador único da música;
    char* title;         //– nome da música;
    int* artist_id;     //– lista de identificadores dos autores da música;
    unsigned int artist_id_counter; 
    Duration duration;   //– tempo de duração;
    char* buffer;
    char* genre;         //– género da música;
    int year;            //– ano de lançamento;
    char* lyrics;        //– letra da música.
} Music;

#endif  
