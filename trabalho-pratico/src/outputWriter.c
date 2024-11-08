#include <stdio.h>
#include <stdlib.h>


void writeQuery1 (FILE* results, char* email, char* firstname, char* lastname, int age, char* country){
    fprintf(results, "%s;%s;%s;%d;%s", email, firstname, lastname, age, country); //email;first_name;last_name;age;country
}

void writeQuery2 (FILE* fp, char* name, char* typeString, char* duration, char* artist_country){
    fprintf (fp, "%s;%s;%s;%s\n", name, typeString, duration, artist_country);
}

void writeQuery3 (FILE* results, char* genre, char* str){
    fprintf(results, "%s;%s\n", genre, str);
}

void writeErrorsArtistsContent(FILE* fp, char* id, char* name, char* description, char* recipePerStream, char* idConstituent, char* country, char* type){
        fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", id, name, description, recipePerStream, idConstituent, country, type);
}

void writeErrorsArtistsHeader (FILE* fp){
    fprintf (fp, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
}

void writeNewLine (FILE* results){
        fprintf(results, "\n");
}