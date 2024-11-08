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

void writeErrorsUsersContent(FILE* fp, char* username, char* email, char* firstName, char* lastName, char* birthDate, char* country, char* subscriptionType, char* likedMusicsID){
    fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", username, email, firstName, lastName, birthDate, country, subscriptionType, likedMusicsID);
}

void writeErrorsUsersHeader (FILE* fp){
    fprintf (fp, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
}

void writeErrorsArtistsContent( FILE* fp, char* id, char* name, char* description, char* recipePerStream, char* idConstituent, char* country, char* type){
    fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", id, name, description, recipePerStream, idConstituent, country, type);
}

void writeErrorsArtistsHeader (FILE* fp){
    fprintf (fp, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
}

void writeErrorsMusicsContent (FILE* fp, char* id, char* title, char* artistID, char* duration, char* genre, char* year, char* lyrics){
    fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", id, title, artistID, duration, genre, year, lyrics);
}

void writeErrorsMusicsHeader (FILE* fp){
    fprintf (fp, "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");
}

void writeNewLine (FILE* results){
    fprintf(results, "\n");
}