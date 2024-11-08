#include <stdio.h>
#include <stdlib.h>

void writeQuery1 (FILE* results, char* email, char* firstname, char* lastname, int age, char* country);

void writeQuery2 (FILE* fp, char* name, char* typeString, char* duration, char* artist_country);

void writeQuery3 (FILE* results, char* genre, char* str);

void writeErrorsUsersContent(FILE* fp, char* username, char* email, char* firstName, char* lastName, char* birthDate, char* country, char* subscriptionType, char* likedMusicsID);

void writeErrorsUsersHeader (FILE* fp);

void writeErrorsArtistsContent(FILE* fp, char* id, char* name, char* description, char* recipePerStream, char* idConstituent, char* country, char* type);

void writeErrorsArtistsHeader (FILE* fp);

void writeNewLine (FILE* results);



