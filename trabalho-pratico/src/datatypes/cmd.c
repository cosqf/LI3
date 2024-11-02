#include <parsingUtils.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <cmd.h>

typedef struct cmd {
    int query;     // 1, 2, or 3
    int id;         // user ID
    int topN;       // top N places
    char *paises;   // (requires memory allocation)
    int ageMin;     // minimum age
    int ageMax;     // maximum age
    int counter;    // tracks the number of the command
} CMD;

CMD* createCMD (char** tokens, int counter) {
    CMD* cmd = malloc(sizeof(CMD));
    if (mallocErrorCheck (cmd)) exit (EXIT_FAILURE);
    cmd->id = -1;
    cmd->topN = -1;
    cmd->paises = NULL;
    cmd->ageMin = -1;
    cmd->ageMax = -1;

    if (tokens[0]) cmd->query = atoi (tokens[0]);
    else {
        perror ("Error getting cmd query number");
        exit (EXIT_FAILURE);
    }
    switch (cmd->query) {
    case 1:
        if (tokens[1]) cmd->id = atoi (tokens[1]+1);
        break;
    case 2:
        if (tokens[1]) cmd->topN = atoi (tokens[1]);
        if (counter > 2 && tokens[2]) cmd->paises = trimString (tokens[2]);
        break;
    case 3:
        if (tokens[1]) cmd->ageMin = atoi (tokens[1]);
        if (tokens[2]) cmd->ageMax = atoi (tokens[2]);
        break;
    }

    return cmd;
}

CMD* getCommand (char* line, CMD* cmd) {
    char *token = strsep(&line, " ");
    cmd->query = atoi(token);
    switch (cmd->query){
    case 1:
        getCommandQuery1 (line, cmd);
        break;

    case 2:
        getCommandQuery2 (line, cmd, token);
        break;

    case 3:
        getCommandQuery3 (line, cmd, token);
        break;
    default:
        perror ("Error Fetching the command from input");
        return NULL;
    }
    return cmd;
}

void getCommandQuery1 (char* line, CMD* cmd) {
    cmd->id = atoi (line+1);
}

void getCommandQuery2 (char* line, CMD* cmd, char* token) {
    token = strsep (&line, " ");
    cmd->topN = atoi(token);
    if (line && line[0] != '\0') {
        line ++;
        token = strsep(&line, "\"");
        cmd->paises = malloc(strlen(token) + 1);
        if (mallocErrorCheck (cmd->paises)) exit (EXIT_FAILURE);
        strcpy(cmd->paises, token); 
    }
    else cmd->paises = NULL;
}

void getCommandQuery3 (char* line, CMD* cmd, char* token) {
    token = strsep (&line, " ");
        cmd->ageMin = atoi(token);
        cmd->ageMax = atoi(line);
}

void freeCmd (CMD *cmd) {
    if (cmd->paises) free (cmd->paises);
    free (cmd);
}

int getCMDquery (CMD* cmd) {
    return cmd->query;
}

int getCMDId (CMD* cmd) {
    return cmd->id;
}

int getCMDtopN (CMD* cmd) {
    return cmd->topN;
}

char *getCMDCountry (CMD* cmd) {
    if (cmd->paises == NULL) return NULL;
    else return strdup (cmd->paises);
}

int getCMDAgeMin (CMD* cmd) {
    return cmd->ageMin;
}

int getCMDAgeMax (CMD* cmd) {
    return cmd->ageMax;
}

int getCMDCounter (CMD* cmd) {
    return cmd->counter;
}