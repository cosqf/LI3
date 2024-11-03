#include <parsing.h>

/* 1. Artists, because it doesn't mess with any other hashtable
   2. Musics, because it needs the artists' hastable for validation
   3. Users, because it needs the musics' hashtable for validation
*/

void getData (char *path, EntityManager *mngr) {
    getDataArtist (path, getArtistManager (mngr));
    getDataMusic (path, getMusicManager (mngr), getArtistManager(mngr));
    getDataUser (path, getUserManager(mngr), getMusicManager(mngr));
}

char* changePath(char *path, DataType type) {
    const char* file;

    if (type == Users) file = "/users.csv";
    else if (type == Musics) file = "/musics.csv";
    else if (type == Artists) file = "/artists.csv";
    else {
        perror ("changePath datatype error");
        exit (EXIT_FAILURE);
    }

    char *pathUpdated = malloc(strlen(path) + strlen(file) + 1); 
    if (pathUpdated) {
        strcpy(pathUpdated, path); 
        strcat(pathUpdated, file); 
    }
    return pathUpdated;
}

int parseLine(char* line, char* tokens[], const char* separator) {
  int tokenCount = 0;
  char* token;
  line[strcspn(line, "\n")] = 0;

  while ((token = strsep(&line, separator)) != NULL) {
    if (*token == '\0') continue;
    tokens[tokenCount] = token;
    tokenCount++;
  }
  return tokenCount;
}

int parseCmdLine(char* line, char* tokens[]) {
    int tokenCount = 0;
    line[strcspn(line, "\n")] = 0;

    while (*line != '\0') {
        while (*line == ' ') line++;

        if (*line == '"') {
            line++; 
            tokens[tokenCount++] = line;

            while (*line != '"' && *line != '\0') line++;

            if (*line == '"') {
                *line = '\0';
                line++;
            }
        } else {
            tokens[tokenCount++] = line;

            while (*line != ' ' && *line != '\0') line++;

            if (*line == ' ') {
                *line = '\0';
                line++;
            }
        }

        if (*line == '\0') break;
    }

    return tokenCount;
}

