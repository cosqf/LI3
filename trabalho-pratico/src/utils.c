#include <utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <users.h>
#include <musics.h>
#include <artists.h>
#include <parsingUtils.h>
#include <string.h>
#include <users.h>

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
    while (len > 0 && (str[len - 1] == '"' || str[len - 1] == ' ' || str[len - 1] == '[' || str[len - 1] == ']' || str[len - 1] == '\'')) {
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