#include <stdio.h>
#include <stdbool.h>

#ifndef _ARTISTS_H_
#define _ARTISTS_H_

typedef struct {
    int id;                       //– identificador único do artista;
    char* name;                     //– nome do artista;
    char* description;              //– detalhes do artista;
    float recipe_per_stream;        //– dinheiro auferido de cada vez que uma das músicas do artista é reproduzida;
    int* id_constituent;            //– lista de identificadores únicos dos seus constituintes, no caso de se tratar de um artista coletivo. Este campo pode ser uma lista vazia.
    unsigned int id_constituent_counter;
    char* country;                  //– nacionalidade do artista.
    bool type;                 //– tipo de artista, i.e., individual(0) ou grupo musical(1)
} Artist;


typedef struct {
    char* id;                       //– identificador único do artista;
    char* name;                     //– nome do artista;
    char* description;              //– detalhes do artista;
    char* recipe_per_stream;        //– dinheiro auferido de cada vez que uma das músicas do artista é reproduzida;
    char* id_constituent;            //– lista de identificadores únicos dos seus constituintes, no caso de se tratar de um artista coletivo. Este campo pode ser uma lista vazia.
    char* country;                  //– nacionalidade do artista.
    char* type;                 //– tipo de artista, i.e., individual(0) ou grupo musical(1)
} ArtistRaw;

#endif  
