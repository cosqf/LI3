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

void getData (char *path, hashtableManager *mngr) {
    char *artistPath = changePath(path, Artists);
    char *albumPath = changePath(path, Albums);
    char *musicPath = changePath(path, Musics);
    char *userPath = changePath(path, Users);
    char *historyPath = changePath(path, Historys);

    getDataArtist (artistPath, getArtistManager (mngr));
    printf("Artists done!\n"); //DEBUG
    getDataAlbum (albumPath, mngr);
    printf("Albums done!\n"); //DEBUG
    getDataMusic (musicPath, mngr);
    printf("Musics done!\n"); //DEBUG
    getDataUser (userPath, mngr);
    printf("Users done!\n"); //DEBUG
    getDataHistory (historyPath, getHistoryManager(mngr));
    printf("History done!\n"); //DEBUG
    
    free(artistPath);
    free(albumPath);
    free(musicPath);
    free(userPath);
    free(historyPath);
}

// opens a file, gets its tokens and processes the line accordingly using a callback 
void parseFile (char* pathToFile, void (processLine)(char**, void*, Output*), void* manager, Output* output) {
    FILE* fileData = openFile (pathToFile);
    printf("File opened!\n");
    char str[DEFAULT];
    if (fgets(str, sizeof(str), fileData) == NULL) { // skip header
            perror ("skipping file header error");
            exit(EXIT_FAILURE);
        }
    printf("Going strong!\n"); //DEBUG
    while (fgets (str, sizeof (str), fileData) != NULL) {
        char* tokens[8];
        parseLine(str, tokens, ";");
        processLine (tokens, manager, output);
    }
    fclose (fileData);
    printf("File closed!\n"); //DEBUG
}

// divides a line in tokens
int parseLine(char* line, char* tokens[], const char* separator) {
  int tokenCount = 0;
  char* token;
  line[strcspn(line, "\n")] = 0;

  while ((token = strsep(&line, separator)) != NULL) {
    if (*token == '\0') continue;
    tokens[tokenCount] = token;
    //printf("Token[%d]: %s\n", tokenCount, token); //DEBUG
    tokenCount++;
  }
  //printf("\n"); //DEBUG 
  return tokenCount;
}

// opens the cmd file, gets its tokens and creates the cmd, line by line
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

