#include <utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <users.h>
#include <musics.h>
#include <artists.h>
#include <processInput.h>
#include <string.h>

FILE* openFile (char * argv) { 
    FILE* fp = fopen (argv, "r");
        if (!fp) {
            perror("Error: File didn't open");
            exit (EXIT_FAILURE);
        }
    return fp;
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
        user->liked_musics_count = count;

    } else if (type == Artists) {
        Artist *artist = (Artist*)IDnum;
        artist->id_constituent_counter = count;

    } else if (type == Musics) {
        Music *music = (Music*)IDnum;
        music->artist_id_counter = count;
    }
}