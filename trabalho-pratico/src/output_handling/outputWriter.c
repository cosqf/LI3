#include <stdio.h>
#include <stdlib.h>
#include "output_handling/outputWriter.h"

#include <parsingUtils.h>

typedef struct output {
    FILE* file;
    char* line [10];
    short int lineCounter; // number of lines to be printed
} Output;


Output* openOutputFile (char* path) {
    Output* output = malloc (sizeof (Output));
    FILE* file = fopen (path, "w");
    if (!file) {
        perror ("Error opening Error file");
        exit (EXIT_FAILURE);
    }
    output->file = file;
    return output;
}

void closeOutputFile (Output* output) {
    fclose (output->file);
    free (output);
}

void setOutput(Output* output, char** lines, int counter) {
    if (counter > 10) {
        perror("Too many lines in output");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < counter; i++) {
        output->line[i] = lines[i];
    }
    output->lineCounter = counter;
}

void writeQuerys (Output* output) {
    FILE* file = output->file;

    int counter = output->lineCounter;
    for (int i = 0; i < counter; i++) {
        fprintf (file, "%s", output->line[i]);
        if (i != counter - 1) fprintf (file, ";");
    }
    fprintf (file, "\n");
}

void writeNewLine(Output* output) {
    fprintf (output->file, "\n");
}

void writeErrorFile (Output* output) {
    FILE* file = output->file;
    int counter = output->lineCounter;

    for (int i = 0; i < counter; i++) {
        fprintf (file, "\"%s\"", output->line[i]);
        if (i != counter - 1) fprintf (file, ";");
        else fprintf (file, "\n");
    }
}

void writeErrorFileHandle (Output* output, DataType type) {
    FILE* file = output->file;
    if (type == Artists) fprintf (file, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
    else if (type == Users) fprintf (file, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
    else if (type == Musics) fprintf (file, "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");

}


// void writeQuery1 (FILE* results, char* email, char* firstname, char* lastname, int age, char* country){
//     fprintf(results, "%s;%s;%s;%d;%s", email, firstname, lastname, age, country); //email;first_name;last_name;age;country
// }

// void writeQuery2 (FILE* fp, char* name, char* typeString, char* duration, char* artist_country){
//     fprintf (fp, "%s;%s;%s;%s\n", name, typeString, duration, artist_country);
// }

// void writeQuery3 (FILE* results, char* genre, char* str){
//     fprintf(results, "%s;%s\n", genre, str);
// }

// void writeErrorsUsersContent(FILE* fp, char* username, char* email, char* firstName, char* lastName, char* birthDate, char* country, char* subscriptionType, char* likedMusicsID){
//     fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", username, email, firstName, lastName, birthDate, country, subscriptionType, likedMusicsID);
// }

// void writeErrorsUsersHeader (FILE* fp){
    
// }

// void writeErrorsArtistsContent( FILE* fp, char* id, char* name, char* description, char* recipePerStream, char* idConstituent, char* country, char* type){
//     fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", id, name, description, recipePerStream, idConstituent, country, type);
// }

// void writeErrorsArtistsHeader (FILE* fp){
    
// }

// void writeErrorsMusicsContent (FILE* fp, char* id, char* title, char* artistID, char* duration, char* genre, char* year, char* lyrics){
//     fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", id, title, artistID, duration, genre, year, lyrics);
// }

// void writeErrorsMusicsHeader (FILE* fp){
   
// }

// void writeNewLine (FILE* results){
//     fprintf(results, "\n");
// }