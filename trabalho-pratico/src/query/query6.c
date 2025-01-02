#include <historyManager.h>
#include <query6.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <history.h>
#include <userManager.h>
#include <cmd.h>

// Structures and functions used to store music

//Struct that store Listened Music
typedef struct ListenedMusicNode {
    int music_id;                     
    struct ListenedMusicNode* next;   
} ListenedMusicNode;



// Function to add musics to the linked list ListenedMusicNode
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

// Check if the song has already been played
int wasMusicListened(ListenedMusicNode* head, int music_id) {
    ListenedMusicNode* current = head;
    while (current != NULL) {
        if (current->music_id == music_id) {
            return 1;  // returns 1 if the music has found
        }
        current = current->next;
    }
    return 0;  // returns 0 if the music hasn't found
}

// Function to free up memory of the linked list
void freeMusicList(ListenedMusicNode* head) {
    ListenedMusicNode* current = head;
    while (current != NULL) {
        ListenedMusicNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Structures and functions used to store artists and there listened time

//store artists and there listened time
typedef struct {
    int artist_id;      // ID do artista
    Duration totalTime; // Duração total
} ArtistListenData;


// Function to find the artist index in the array
int findArtistIndex(ArtistListenData* array, int size, int artist_id) {
    for (int i = 0; i < size; i++) {
        if (array[i].artist_id == artist_id) {
            return i;
        }
    }
    return -1;
}

//updates the array
ArtistListenData* updateArtistData(ArtistListenData* array, int* size, int artist_id, Duration duration) {
    int index = findArtistIndex(array, *size, artist_id);

    if (index != -1) {
        // updates the totalTime
        array[index].totalTime.hours += duration.hours;
        array[index].totalTime.minutes += duration.minutes;
        array[index].totalTime.seconds += duration.seconds;

        // Corrects seconds and minutes
        if (array[index].totalTime.seconds >= 60) {
            array[index].totalTime.minutes += array[index].totalTime.seconds / 60;
            array[index].totalTime.seconds %= 60;
        }
        if (array[index].totalTime.minutes >= 60) {
            array[index].totalTime.hours += array[index].totalTime.minutes / 60;
            array[index].totalTime.minutes %= 60;
        }
    } else {
        // Add a new artist
        ArtistListenData* new_array = realloc(array, (*size + 1) * sizeof(ArtistListenData));
        if (!new_array) {
            printf("Erro ao alocar memória!\n");
            free(array);
            exit(1);
        }
        array = new_array;
        array[*size].artist_id = artist_id;
        array[*size].totalTime = duration;
        (*size)++;
    }

    return array;
}

// Function to find the most listened artist
int findMostListenedArtist(ArtistListenData* array, int size) {
    if (size == 0) {
        return -1;
    }

    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        Duration current = array[i].totalTime;
        Duration max = array[maxIndex].totalTime;

        if ((current.hours > max.hours) || 
            (current.hours == max.hours && current.minutes > max.minutes) || 
            (current.hours == max.hours && current.minutes == max.minutes && current.seconds > max.seconds)) {
            maxIndex = i;
        }
    }
    return array[maxIndex].artist_id;
}





void query6(CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, int cmdCounter) {
    int userId = getCMDId(cmd);
    int nMusics = 0;

    Duration listenTime = {0, 0, 0, 0}; 
    History* history = lookupHistoryHashByUser(h_mngr, userId);
    ListenedMusicNode* listenedList = NULL; 
    ArtistListenData* artistData = NULL;
    int artistCount = 0;

    char filename[50];
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);
    Output* output = openOutputFile(filename);

    if (history == NULL) {
        writeNewLine(output);
        printf("Error: No history found for ID %d.\n", userId);
        closeOutputFile(output);

        freeMusicList(listenedList);
        free(artistData);
        deleteHistoryByUser(history);

        return;
    }

    History* ptr = history;

    while (ptr != NULL) {
        int currentYear = getHistoryTimestamp(ptr).date.year;
        int intendedYear = getCMDyear(cmd);

        if (currentYear == intendedYear) {
            listenTime = calculateListenTime(ptr, listenTime);

            int music_id = getHistoryMusicId(ptr);
            if (!wasMusicListened(listenedList, music_id)) {
                nMusics++;
                listenedList = addMusic(listenedList, music_id);
            }

            Music* music = lookupMusicHash(m_mngr, music_id);
            if (music == NULL) {
                ptr = getNextHistoryByUser(ptr);
                continue;
            }

            const int* artist_id_ptr = getMusicArtistID(music);
            if (artist_id_ptr == NULL) {
                ptr = getNextHistoryByUser(ptr);
                deleteMusic(music);
                continue;
            }

            int artist_id = *artist_id_ptr;
            Duration duration = getHistoryDuration(ptr);
            artistData = updateArtistData(artistData, &artistCount, artist_id, duration);
            
            deleteMusic(music);
        }

        ptr = getNextHistoryByUser(ptr);
    }
    free(ptr);
    int mostListenedArtist = findMostListenedArtist(artistData, artistCount);


    if (mostListenedArtist == -1) {
        writeNewLine(output);
        printf("Error: No history found for ID %d.\n", userId);
        closeOutputFile(output);

        freeMusicList(listenedList);
        free(artistData);
        deleteHistoryByUser(history);
        return;
    }


    int hour = listenTime.hours;
    int min = listenTime.minutes;
    int seg = listenTime.seconds;

    printf("%d:%d:%d  nMusicas: %d,  Artista: %d,  IdHistory: %d, IDUser: %d\n",
           hour, min, seg, nMusics, mostListenedArtist, userId, userId);

    closeOutputFile(output);
    freeMusicList(listenedList);
    free(artistData);
    deleteHistoryByUser(history);
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