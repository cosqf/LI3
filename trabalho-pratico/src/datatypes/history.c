#include <history.h>
#include <utils.h>
#include <parsingUtils.h>
#include <output_handling/errorfiles.h>
#include <stdlib.h>

typedef struct history {
    int id;                   //– identificador único do registo;
    int user_id;              //– user_id – identificador único do utilizador a que o registo se refere;
    int music_id;             //– music_id – identificador único da música a que o registo se refere;
    Date timestamp;           //– timestamp – data e hora em que a música foi ouvida pelo utilizador;
    Duration duration;        //– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    bool platform;            //– platform – plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel. -- irrelevante?
} History;

typedef struct historyString {
    char* id;                   //– identificador único do registo;
    char* user_id;              //– user_id – identificador único do utilizador a que o registo se refere;
    char* music_id;             //– music_id – identificador único da música a que o registo se refere;
    char* timestamp;            //– timestamp – data e hora em que a música foi ouvida pelo utilizador;
    char* duration;             //– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    char* platform;             //– platform – plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel.
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

    history->timestamp = parseDate (trimString (tokens[3]));

    history->duration = parseDuration (trimString (tokens[4]));

    char** platform = lower (trimString(tokens[5]));
    if (strcmp (platform, "desktop") == 0) history->platform = 0;
    else history->platform = 1;

    free (platform);
    return history;
}

void deleteHistory (History* history) {
    if (history == NULL) return;
    free (history);
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
Date getHistoryTimestamp (History* history) {
    return history->timestamp;
}

// Getter for the duration field
Duration getHistoryDuration (History* history) {
    return history->duration;
}

// Getter for the platform field
bool getHistoryPlatform (History* history) {
    return history->platform;
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
char* getHistoryPlatformString (History* history) {
    return strdup (history->platform);
}


//– id – identificador único do registo;
//– user_id – identificador único do utilizador a que o registo se refere;
//– music_id – identificador único da música a que o registo se refere;
//– timestamp – data e hora em que a música foi ouvida pelo utilizador;
//– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
//– platform – plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel.