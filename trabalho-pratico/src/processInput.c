#include <processInput.h>
#include <query1.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

CMD* getCommand (char* line, CMD* cmd) {
    char *token = strsep(&line, " ");
    cmd->query = atoi(token);

    if (cmd->query == 1) {
        cmd->id = atoi (line+1);

        cmd->topN = -1;
        cmd->paises = NULL;
        cmd->ageMin = -1;
        cmd->ageMax = -1;
    }
    else if (cmd->query == 2) {
        token = strsep (&line, " ");
        cmd->topN = atoi(token);
        if (line && line[0] != '\0') {
            token = strsep(&line+1, "\"");
            cmd->paises = malloc(strlen(token) + 1);
            if (cmd->paises != NULL) strcpy(cmd->paises, token); 
            else {
                perror ("Malloc Error");
                return NULL;
            }
        }
        else cmd->paises = NULL;
        cmd->id = -1;
        cmd->ageMin = -1;
        cmd->ageMax = -1;
        }
    else if (cmd->query == 3) { // add verify to make sure ageMin < ageMax and that ageMin >= 0
        token = strsep (&line, " ");
        cmd->ageMin = atoi(token);
        cmd->ageMax = atoi(line);
        
        cmd->id = -1;
        cmd->topN = -1;
        cmd->paises = NULL;
    }
    else {
        perror ("Error getting the command from input");
        return NULL;
    }
    return cmd;
}

void getData (char **argv, dataType dt) {
    FILE* fp = fopen (argv, "r");
    if (!fp) {
        perror("Error: File didn't open");
        return 1;
    }

    char str[DEFAULT];
    while (fgets (str, sizeof str, fp) != NULL){
        parseData (str, dt);
    }
    fclose(fp);
}

void parseData (char *str, dataType dt) {
   // filtra ()
}