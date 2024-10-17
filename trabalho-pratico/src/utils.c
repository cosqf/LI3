#include <utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <users.h>
#include <musics.h>
#include <artists.h>
#include <parsingUtils.h>
#include <string.h>
#include <users.h>
#include <glib.h>

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

char *trimString(char *str) { // Trims a string, removing symbols from each end
    if (!str) return NULL;

    while (*str == '"' || *str == ' ' || *str == '[' || *str == ']' || *str == '\'') {
        str++;
    }

    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '"' || str[len - 1] == ' ' || str[len - 1] == '[' || str[len - 1] == ']' || str[len - 1] == '\'' || str[len - 1] == '\n')) {
        str[--len] = '\0';
    }

    return str;
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