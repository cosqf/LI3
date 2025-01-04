#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "output_handling/outputWriter.h"
#include <cmd.h>


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





void writeQ6Geral(Output* output, CMD* cmd, Duration listenTime, Date mostListenedDay, int nMusics, int mostListenedArtist, const char* mostHeardGenreString, int mostListenedAlbum, int mostListenedHour  ){
    char separator = getCMDSeparator(cmd);

    int hour = listenTime.hours;
    int min = listenTime.minutes;
    int seg = listenTime.seconds;

    int ano = mostListenedDay.year;
    int mes = mostListenedDay.month;
    int dia = mostListenedDay.day;

    if (separator == ';')
    fprintf(output->file,"%02d:%02d:%02d;%d;A%07d;%04d/%02d/%02d;%s;AL%06d;%02d\n", hour, min, seg, nMusics, mostListenedArtist, ano, mes, dia, mostHeardGenreString, mostListenedAlbum, mostListenedHour);
    else
    fprintf(output->file,"%02d:%02d:%02d=%d=A%07d=%04d/%02d/%02d=%s=AL%06d=%02d\n", hour, min, seg, nMusics, mostListenedArtist, ano, mes, dia, mostHeardGenreString, mostListenedAlbum, mostListenedHour);

}

void writeQ6Artists(Output* output, CMD* cmd, int mostListenedArtist, int nMusicsArtist, Duration listenedTimeArtist){
    char separator = getCMDSeparator(cmd);

    int hourArtist = listenedTimeArtist.hours;
    int minutesArtist = listenedTimeArtist.minutes;
    int secondsArtist = listenedTimeArtist.seconds;

    if (separator == ';')
    fprintf(output->file,"A%07d;%d;%02d:%02d:%02d\n", mostListenedArtist, nMusicsArtist, hourArtist, minutesArtist, secondsArtist);
    else
    fprintf(output->file,"A%07d=%d=%02d:%02d:%02d\n", mostListenedArtist, nMusicsArtist, hourArtist, minutesArtist, secondsArtist);
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
    else if (type == Musics) fprintf (file, "\"id\";\"title\";\"artist_id\";\"album_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");
    else if (type == Historys) fprintf (file, "\"id\";\"user_id\";\"music_id\";\"timestamp\";\"duration\";\"platform\"\n");
    else if (type == Albums) fprintf (file, "\"id\";\"title\";\"artist_id\";\"year\";\"producers\"\n");
    else perror ("Datatype error in error outputting\n");
}