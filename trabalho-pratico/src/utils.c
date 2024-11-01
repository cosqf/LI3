#include <utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <users.h>
#include <musics.h>
#include <artists.h>
#include <parsingUtils.h>
#include <string.h>
#include <glib.h>
#include <validation.h>
#include <parsing.h>
#include <validateDatatypes.h>
#include <parsingDatatypes.h>
#include <entityManager.h>
#include <artistManager.h>
#include <userManager.h>
#include <musicManager.h>

FILE* openFile (char * argv) { 
    FILE* fp = fopen (argv, "r");
        if (!fp) {
            perror("Error: File didn't open");
            exit (EXIT_FAILURE);
        }
    return fp;
}

bool mallocErrorCheck (void* address) {
    if (address == NULL) {
        perror ("Malloc error");
        return 1;
    }
    else return 0;
}

char *trimString(char *str) {
    if (!str) return NULL;

    char *start = str;
    char *end = str + strlen(str) - 1;

    while (*start == '"' || *start == ' ' || *start == '\'' || *start == '[' || *start == ']' || *start == '\'') {
        start++;
    }

    while (end > start && (*end == '"' || *end == ' ' || *end == '\'' || *end == '\n' || *end == '[' || *end == ']' || *end == '\'')) {
        *end-- = '\0';
    }

    return start; 
}

char* trimStringWithoutBrackets (char* str) {
    if (!str) return NULL;

    char *start = str;
    char *end = str + strlen(str) - 1;

    while (*start == '"' || *start == ' ' || *start == '\'') {
        start++;
    }

    while (end > start && (*end == '"' || *end == ' ' || *end == '\'' || *end == '\n')) {
        *end-- = '\0';
    }

    return start; 
}

void updateCount(void* IDnum, DataType type, int count) {
    if (type == Users) {
        User *user = (User*)IDnum;
        setUserLikedMusicsCount (user, count);

    } else if (type == Artists) {
        Artist *artist = (Artist*)IDnum;
        setArtistIDConstituentCounter (artist, count);

    } else if (type == Musics) {
        Music *music = (Music*)IDnum;
        setMusicArtistIDCount (music, count);
    }
}

// Checks if the given character is an undercase letter
int isletter(char a){
    if (a >= 'a' && a <= 'z') return 1;
    return 0;
}


// Checks if the given character is a digit
int isDigit(char a){
    if (a >= '0' && a <= '9') return 1;
    return 0;
}


// Checks is the given string is comprised of only undercase letters (if the flag is 0), or comprised of undercase letters and digits (if the flag is 1)
int isstr(char* str, int flag) {
    if (!str) return 0;
    
    int i;

    if (flag == 1) for (i = 0; isletter(str[i]) || isDigit(str[i]); i++);

    else for (i = 0; isletter(str[i]); i++);
    
    if (str[i] == '\0') return 1;
    
    return 0;
}

// Returns a duration in seconds
int durationInSeconds (Duration time) {
    return time.hours*3600 + time.minutes*60 + time.seconds;
}
// Returns the duration when given seconds
Duration secondsInDuration (int seconds) {
    Duration dur;
    dur.hours = seconds / 3600;
    dur.minutes = (seconds % 3600) / 60;
    dur.seconds = seconds % 60;

    return dur;
}

GHashTable* createHash () {
    return g_hash_table_new(g_direct_hash, g_direct_equal);
}

void deleteHash (GHashTable* hash) {
    g_hash_table_destroy (hash);
}

void insertHash (GHashTable* hash, int key, int value) {
    g_hash_table_insert(hash, GINT_TO_POINTER (key), GINT_TO_POINTER (value));
}


char* durationInString(Duration time) {
    char* str = malloc(9 * sizeof(char));
    if (mallocErrorCheck (str)) exit (EXIT_FAILURE);

    sprintf(str, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);

    return str; 
}
// for debugging:

void writeUsersToErrorFile(GHashTable* userTable) {
    FILE *fp = openResultFileUsers();
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, userTable);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User* user = (User*)value;
        insertErrorFileUser(user, fp);
    }
    
    fclose(fp);
}

void writeArtistsToErrorFile(GHashTable* artistTable) {
    FILE *fp = openResultFileArtists();
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, artistTable);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist* artist = (Artist*)value;
        insertErrorFileArtists(artist, fp);
    }

    fclose(fp);
}

void writeMusicsToErrorFile(GHashTable* musicTable) {
    FILE *fp = openResultsFileMusics();
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, musicTable);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Music* music = (Music*)value;
        insertErrorFileMusics(music, fp);
    }

    fclose(fp);
}

void printHash (GHashTable* table) {
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        printf ("id:%d, duration:%d\t", GPOINTER_TO_INT(key), GPOINTER_TO_INT(value));
    }
    printf ("\n");
}