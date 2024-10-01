#include <processInput.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//1 Uid
//2 int "string" <- filtro
//3 int int <- idades max/min


CMD* getCommand (char* line, CMD* cmd) {
    char *token = strsep(&line, " ");
    cmd->querry = atoi(token);

    if (cmd->querry == 1) {
        cmd->id = atoi (line+1);

        cmd->topN = -1;
        cmd->paises = NULL;
        cmd->ageMin = -1;
        cmd->ageMax = -1;
    }
    else if (cmd->querry == 2) {
        token = strsep (&line, " ");
        cmd->topN = atoi(token);
        if (line && line[0] != '\0') {
            token = strsep(&line, "\"");
            token = strsep(&line, "\""); 
            cmd->paises = malloc(strlen(token) + 1);
            if (cmd->paises != NULL) strcpy(cmd->paises, token); 
            else {
                perror ("Malloc Error\n");
                return NULL;
            }
        }
        else cmd->paises = NULL;
        cmd->id = -1;
        cmd->ageMin = -1;
        cmd->ageMax = -1;
        }
    else if (cmd->querry == 3) { // add verify to make sure ageMin < ageMax and that ageMin >= 0
        token = strsep (&line, " ");
        cmd->ageMin = atoi(token);
        cmd->ageMax = atoi(line);
        
        cmd->id = -1;
        cmd->topN = -1;
        cmd->paises = NULL;
    }
    else {
        perror ("Error getting the command from input\n");
        return NULL;
    }
    return cmd;
}