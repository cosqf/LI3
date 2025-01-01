#include <historyManager.h>
#include <query6.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <history.h>
#include <userManager.h>
#include <cmd.h>


void query6(CMD* cmd, HistoryManager* h_mngr,int cmdCounter ) {
    int query = getCMDquery(cmd);
    int nArtists = getCMDnArtists(cmd);
    int id = getCMDId(cmd);
    History* history = lookupHistoryHash(h_mngr, id);
    
    char filename[50];  // buffer for the formatted file name

    Output* output = openOutputFile (filename);
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);


    if (history == NULL) {
        writeNewLine(output);
        printf("Error: No history found for ID %d.\n", id);
        return;
    }
    int idHistory = getHistoryId(history);
    printf("IdHistory: %d, IDUser: %d, Query: %d, Número artistas: %d \n", 
            idHistory, id, query, nArtists);
}



/*
typedef struct cmd {
    int query;          // 1, 2, 3, 4, 5, or 6
    char entity;       // A or U (Q1)
    int id;             // entity ID
    int topN;           // top N places
    char *paises;       // (requires memory allocation)
    int ageMin;         // minimum age
    int ageMax;         // maximum age
    Date dateMin;       // minimum date
    Date dateMax;       // max date
    int noUsers;        // number of users to compare with
    short int year;     // year
    short int nArtists; // number of artists
    char separator;     // separator for output (';' or '=')
} CMD;


typedef struct history {
    int id;                   //– identificador único do registo;
    int user_id;              //– identificador único do utilizador a que o registo se refere;
    int music_id;             //– identificador único da música a que o registo se refere;
    Timestamp timestamp;      //– data e hora em que a música foi ouvida pelo utilizador;
    Duration duration;        //– tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    History* nextByUser;      // points to a History* w the same user_id
    History* nextByMusic;     // points to a History* w the same music_id
} History;

typedef struct historyManager {
    GHashTable *historyByUser;
    GHashTable *historyByMusic;
    GTree* historyInWeeks; // will only have the top 10 artists of each week, key: first day of the week, value: array with artists and duration
} HistoryManager;
*/