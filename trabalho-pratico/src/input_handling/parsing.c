#include <parsing.h>
#include <utils.h>
#include <output_handling/errorfiles.h>
#include <userManager.h>
#include <cmdManager.h>

/* 1. Artists, because it doesn't mess with any other hashtable
   2. Musics, because it needs the artists' hastable for validation
   3. Users, because it needs the musics' hashtable for validation
*/

void getData (char *path, hashtableManager *mngr) {
    char *artistPath = changePath(path, Artists);
    char *musicPath = changePath(path, Musics);
    char *userPath = changePath(path, Users);

    getDataArtist (artistPath, getArtistManager (mngr));
    getDataMusic (musicPath, mngr);
    getDataUser (userPath, mngr);
    
    free(artistPath);
    free(musicPath);
    free(userPath);
}

void parseFile (char* pathToFile, void (processLine)(char**, void*, Output*), void* manager, Output* output) {
    FILE* fileData = openFile (pathToFile);
    char str[DEFAULT];
    if (fgets(str, sizeof(str), fileData) == NULL) { // skip header
            perror ("skipping artist header error");
            exit(EXIT_FAILURE);
        }
    while (fgets (str, sizeof (str), fileData) != NULL) {
        char* tokens[8];
        parseLine(str, tokens, ";");
        processLine (tokens, manager, output);
    }
    fclose (fileData);
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

int parseCmdFile (char* pathToFile, void* manager) {
    FILE* fileData = openFile (pathToFile);
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

