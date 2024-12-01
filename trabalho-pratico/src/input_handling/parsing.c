#include <parsing.h>
#include <utils.h>
#include <output_handling/errorfiles.h>
#include <cmdManager.h>

/* 1. Artists, because it doesn't mess with any other entity
   2. Albums, because it needs the artists for validation
   3. Musics, because it needs the albums for validation
   4. Users, because it needs the musics for validation
   5. History,
*/

int getData (char *path, hashtableManager *mngr) {
    bool error = 0;
    char *artistPath = changePath(path, Artists);
    char *albumPath = changePath(path, Albums);
    char *musicPath = changePath(path, Musics);
    char *userPath = changePath(path, Users);
    char *historyPath = changePath(path, Historys);

    if      (getDataArtist (artistPath, getArtistManager (mngr))) error = 1;
    else if (getDataAlbum (albumPath, mngr)) error = 1;
    else if (getDataMusic (musicPath, mngr)) error = 1;
    else if (getDataUser (userPath, mngr)) error = 1;
    else if (getDataHistory (historyPath, getHistoryManager(mngr))) error = 1;

    if (error) freeHash (mngr);

    free(artistPath);
    free(albumPath);
    free(musicPath);
    free(userPath);
    free(historyPath);

    return error;
}

// opens a file, gets its tokens and processes the line accordingly using a callback 
int parseFile (char* pathToFile, void (processLine)(char**, void*, Output*), void* manager, Output* output) {
    FILE* fileData = openFile (pathToFile);
    char str[DEFAULT];
    if (fgets(str, sizeof(str), fileData) == NULL) { // skip header
            perror ("skipping artist header error");
            return 1;
        }
    while (fgets (str, sizeof (str), fileData) != NULL) {
        char* tokens[8];
        parseLine(str, tokens, ";");
        processLine (tokens, manager, output);
    }
    fclose (fileData);
    return 0;
}

// divides a line in tokens
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

// opens the cmd file, gets its tokens and creates the cmd, line by line
int parseCmdFile (char* pathToFile, void* manager) {
    FILE* fileData = openFile (pathToFile);
    if (!fileData) return -1;

    char str[DEFAULT];
    int i;
    for (i = 0; fgets (str, sizeof (str), fileData) != NULL; i++) {
        char* tokens[4];
        int tokensNumber = parseCmdLine(str, tokens);
        processCmdLine (tokens, tokensNumber, manager);
    }
    fclose (fileData);
    return i;
}

// divides a line in tokens using the spaces as separators, except when finding ' " '
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
    }
    return tokenCount;
}

// changes path to the file according to its datatype
char* changePath(char *path, DataType type) {
    const char* file;

    if (type == Users) file = "/users.csv";
    else if (type == Musics) file = "/musics.csv";
    else if (type == Artists) file = "/artists.csv";
    else if (type == Albums) file = "/albums.csv";
    else if (type == Historys) file = "/history.csv";
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

