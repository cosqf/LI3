#include <parsingUtils.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingCmd.h>

typedef struct cmd {
    int query;     // 1, 2, or 3
    int id;         // user ID
    int topN;       // top N places
    char *paises;   // (requires memory allocation)
    int ageMin;     // minimum age
    int ageMax;     // maximum age
} CMD;

CMD* createCMD () {
    CMD* cmd = malloc(sizeof(CMD));
    if (mallocErrorCheck (cmd)) exit (EXIT_FAILURE);
    cmd->query = 0;
    cmd->id = 0;
    cmd->topN = 0;
    cmd->paises = NULL;
    cmd->ageMin = 0;
    cmd->ageMax = 0;
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

    cmd->topN = -1;
    cmd->paises = NULL;
    cmd->ageMin = -1;
    cmd->ageMax = -1;
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
    cmd->id = -1;
    cmd->ageMin = -1;
    cmd->ageMax = -1;
}

void getCommandQuery3 (char* line, CMD* cmd, char* token) {
    token = strsep (&line, " ");
        cmd->ageMin = atoi(token);
        cmd->ageMax = atoi(line);
        
        cmd->id = -1;
        cmd->topN = -1;
        cmd->paises = NULL;
}

void freeCmd (CMD *cmd) {
    if (cmd->paises) free (cmd->paises);
    free (cmd);
}
