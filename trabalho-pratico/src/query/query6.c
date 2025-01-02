#include <historyManager.h>
#include <query6.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <history.h>
#include <userManager.h>
#include <cmd.h>

typedef struct ListenedMusicNode {
    int music_id;                     // Identificador da música
    struct ListenedMusicNode* next;   // Próximo nó
} ListenedMusicNode;

// Função para adicionar uma música à lista ligada
ListenedMusicNode* addMusic(ListenedMusicNode* head, int music_id) {
    ListenedMusicNode* new_node = malloc(sizeof(ListenedMusicNode));
    if (!new_node) {
        printf("Erro ao alocar memória!\n");
        return head;
    }
    new_node->music_id = music_id;
    new_node->next = head;
    return new_node;
}

// Função para verificar se uma música já foi ouvida
int wasMusicListened(ListenedMusicNode* head, int music_id) {
    ListenedMusicNode* current = head;
    while (current != NULL) {
        if (current->music_id == music_id) {
            return 1;  // Música encontrada
        }
        current = current->next;
    }
    return 0;  // Música não encontrada
}

// Função para liberar a memória da lista ligada
void freeMusicList(ListenedMusicNode* head) {
    ListenedMusicNode* current = head;
    while (current != NULL) {
        ListenedMusicNode* temp = current;
        current = current->next;
        free(temp);
    }
}

void query6(CMD* cmd, HistoryManager* h_mngr,int cmdCounter ) {
    int query = getCMDquery(cmd);
    int nArtists = getCMDnArtists(cmd);
    int id = getCMDId(cmd);
    int nMusics = 0;


    Duration listenTime = {0, 0, 0, 0}; //Duration used to output

    History* history = lookupHistoryHash(h_mngr, id);
    ListenedMusicNode* listenedList = NULL; // Cabeça da lista ligada


    
    char filename[50];  // buffer for the formatted file name

    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);

    Output* output = openOutputFile (filename);


    if (history == NULL) { //writes a "\n" in the output file if the user doesn't have an history
        writeNewLine(output);
        printf("Error: No history found for ID %d.\n", id);
        return;
    }

    int idHistory = getHistoryId(history);


    while (history!=NULL){ //calculates the data taking into account the year
        int currentYear = getHistoryTimestamp(history).date.year;
        int intendedYear = getCMDyear (cmd);
        if (currentYear == intendedYear){
            int music_id = getHistoryMusicId(history);

            if (!wasMusicListened(listenedList, music_id)) {
                nMusics++;
                listenedList = addMusic(listenedList, music_id); // Adiciona à lista
            }

            listenTime = calculateListenTime (history, listenTime);


        }
        history = getNextHistoryByUser (history);

    }



    int hour = listenTime.hours;
    int min = listenTime.minutes;
    int seg = listenTime.seconds;

    printf("%d:%d:%d  nMusicas: %d,  IdHistory: %d, IDUser: %d, Query: %d, Número artistas: %d \n", hour, min, seg, nMusics, idHistory, id, query, nArtists);

    closeOutputFile(output);
    freeMusicList(listenedList);
}






Duration calculateListenTime (History* history, Duration listenTime){
        Duration currentDuration = getHistoryDuration(history);

        int hours = currentDuration.hours;
        int min = currentDuration.minutes;
        int sec = currentDuration.seconds;

        listenTime.hours += hours;
        listenTime.minutes += min;
        listenTime.seconds += sec;

        if (listenTime.seconds >= 60){ // checks if the duration is more than 60 seconds and corrects it
            listenTime.minutes += listenTime.seconds / 60;
            listenTime.seconds = listenTime.seconds % 60;
        }

        if (listenTime.minutes >= 60){ // checks if the duration is more than 60 minutes and corrects it
            listenTime.hours += listenTime.minutes / 60;
            listenTime.minutes = listenTime.minutes % 60;
        }

        
    return listenTime;
}


/*

00:04:47;1;A0009964;2019/12/13;Hip Hop;AL006156;07
A0009964;1;00:04:47



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


typedef struct {
    int hours;         
    int minutes;       
    int seconds;       
    short int error;   
} Duration;

*/