#include <history.h>
#include <utils.h>
#include <parsingUtils.h>
#include <output_handling/errorfiles.h>
#include <stdlib.h>

typedef struct history {
    int id;                   //– identificador único do registo;
    int user_id;              //– identificador único do utilizador a que o registo se refere;
    int music_id;             //– identificador único da música a que o registo se refere;
    Timestamp timestamp;      //– data e hora em que a música foi ouvida pelo utilizador;
    Duration duration;        //– tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    History* nextByUser;      // points to a History* w the same user_id
    History* nextByMusic;     // points to a History* w the same music_id
} History;

typedef struct historyString {
    char* id;                   //– identificador único do registo;
    char* user_id;              //– identificador único do utilizador a que o registo se refere;
    char* music_id;             //– identificador único da música a que o registo se refere;
    char* timestamp;            //– data e hora em que a música foi ouvida pelo utilizador;
    char* duration;             //– tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    char* platform;             //– plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel.
} HistoryString;

History* createHistory (char** tokens) {
    History* history = malloc (sizeof(History));
    if (mallocErrorCheck (history)) exit (EXIT_FAILURE);

    int id, user_id, music_id;
    if (convertToInt (trimString((tokens[0])) + 1, &id)) history->id = id;
    else exit (EXIT_FAILURE);

    if (convertToInt (trimString((tokens[1])) + 1, &user_id)) history->user_id = user_id;
    else exit (EXIT_FAILURE);

    if (convertToInt (trimString((tokens[2])) + 1, &music_id)) history->music_id = music_id;
    else exit (EXIT_FAILURE);

    history->timestamp = parseTimestamp (trimString (tokens[3]));

    history->duration = parseDuration (trimString (tokens[4]));

    history->nextByUser = NULL;

    history->nextByMusic = NULL;

    return history;
}

void deleteHistory(History* history) {
    History* temp;

    while (history != NULL) {
        temp = history->nextByUser;
        free(history);
        history = temp;
    }
}


// GETTERs

// Getter for the id field
int getHistoryId (History* history) {
    return history->id;
}

// Getter for the user_id field
int getHistoryUserId (History* history) {
    return history->user_id;
}

// Getter for the music_id field
int getHistoryMusicId (History* history) {
    return history->music_id;
}

// Getter for the timestamp field
Timestamp getHistoryTimestamp (History* history) {
    return history->timestamp;
}

// Getter for the duration field
Duration getHistoryDuration (History* history) {
    return history->duration;
}

// Getter for the next field
History* getNextHistoryByUser (History* history) {
    return history->nextByUser;
}

History* getNextHistoryByMusic (History* history) {
    return history->nextByMusic;
}

// Getter to determine how many nodes are in a linked list
int getHistoryListLengthByUser(History* history) {
    int length = 0;
    while (history) {
        length++;
        history = getNextHistoryByUser(history);
    }
    return length;
}

int getHistoryListLengthByMusic(History* history) {
    int length = 0;
    while (history) {
        length++;
        history = getNextHistoryByMusic(history);
    }
    return length;
}






History* copyHistory( History* historyOg) {
    if (historyOg == NULL) {
        return NULL;
    }

    History* historyCopy = malloc(sizeof(History));
    if (!historyCopy) {
        perror("Error allocating memory for User");
        return NULL;
    }

    // Copia os campos simples (inteiros)
    historyCopy->id = historyOg->id;
    historyCopy->user_id = historyOg->user_id;
    historyCopy->music_id = historyOg->music_id;

    // Copia o campo Timestamp (composto por Date e Duration)
    historyCopy->timestamp.date = historyOg->timestamp.date;  // Copia Date
    historyCopy->timestamp.hour.hours = historyOg->timestamp.hour.hours;
    historyCopy->timestamp.hour.minutes = historyOg->timestamp.hour.minutes;
    historyCopy->timestamp.hour.seconds = historyOg->timestamp.hour.seconds;
    historyCopy->timestamp.hour.error = historyOg->timestamp.hour.error;

    // Copia o campo Duration (relacionado à duração da música)
    historyCopy->duration.hours = historyOg->duration.hours;
    historyCopy->duration.minutes = historyOg->duration.minutes;
    historyCopy->duration.seconds = historyOg->duration.seconds;
    historyCopy->duration.error = historyOg->duration.error;

    // Copia os ponteiros para as listas encadeadas, se existirem
    if (historyOg->nextByUser != NULL) {
        historyCopy->nextByUser = copyHistory(historyOg->nextByUser);  // Cópia recursiva para a lista encadeada por user_id
    } else {
        historyCopy->nextByUser = NULL;  // Se o próximo for NULL, também definimos o próximo como NULL
    }

    if (historyOg->nextByMusic != NULL) {
        historyCopy->nextByMusic = copyHistory(historyOg->nextByMusic);  // Cópia recursiva para a lista encadeada por music_id
    } else {
        historyCopy->nextByMusic = NULL;  // Se o próximo for NULL, também definimos o próximo como NULL
    }


    return historyCopy;
}
















// SETTERs

//Setter for the next field
History* setNextHistoryByUser (History* newNext, History* history) {
    History* tail = history;
    while (tail->nextByUser != NULL) tail = tail->nextByUser;
    tail->nextByUser = newNext;
    return history;
}

History* setNextHistoryByMusic (History* newNext, History* history) {
    History* tail = history;
    while (tail->nextByMusic != NULL) tail = tail->nextByMusic;
    tail->nextByMusic = newNext;
    return history;
}

// String format 
HistoryString* createHistoryString (char** tokens) {
    HistoryString* history = malloc (sizeof (HistoryString));
    if (mallocErrorCheck (history)) exit (EXIT_FAILURE);

    history->id = strdup (trimString(tokens[0]));
    history->user_id = strdup (trimString(tokens[1]));
    history->music_id = strdup (trimString(tokens[2]));
    history->timestamp = strdup (trimString(tokens[3]));
    history->duration = strdup (trimString(tokens[4]));
    history->platform = strdup (trimString(tokens[5]));

    return history;
}


void deleteHistoryString (HistoryString* history) {
    if (history == NULL) return;
    free (history->id);
    free (history->user_id);
    free (history->music_id);
    free (history->timestamp);
    free (history->duration);
    free (history->platform);
    free (history);
}

// GETTERs in string format

// Getter for the id field
char* getHistoryIdString (HistoryString* history) {
    return strdup (history->id);
}

// Getter for the user_id field
char* getHistoryUserIdString (HistoryString* history) {
    return strdup (history->user_id);
}

// Getter for the music_id field
char* getHistoryMusicIdString (HistoryString* history) {
    return strdup (history->music_id);
}

// Getter for the timestamp field
char* getHistoryTimestampString (HistoryString* history) {
    return strdup (history->timestamp);
}

// Getter for the duration field
char* getHistoryDurationString (HistoryString* history) {
    return strdup (history->duration);
}

// Getter for the platform field
char* getHistoryPlatformString (HistoryString* history) {
    return strdup (history->platform);
}

