#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "output_handling/outputWriter.h"
#include <cmd.h>

#include <parsingUtils.h>

typedef struct output {
    FILE* file;
    char* line [10]; // number of tokens never surpasses 10
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

// adds the lines to the output
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

// generic function to write in the querys format
void writeQuerys (Output* output, CMD* cmd) {
    if (output == NULL || output->file == NULL || output->line == NULL) return;

    FILE* file = output->file;

    const char separator = getCMDSeparator(cmd);

    int counter = output->lineCounter;
    for (int i = 0; i < counter; i++) {
        fprintf (file, "%s", output->line[i]);
        if (i != counter - 1) fprintf(file, "%c", separator);
    }
    fprintf (file, "\n");
}

void writeNewLine(Output* output) {
    fprintf (output->file, "\n");
}

// generic function to write error files
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
    else if (type == Historys) fprintf (file, "\"id\";\"user_id\";\"music_id\";\"timestamp\";\"duration\";\"platform\"\n");
    else if (type == Albums) fprintf (file, "\"id\";\"title\";\"artist_id\";\"year\";\"producers\"\n");
    else perror ("Datatype error in error outputting\n");
}