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
    char separator  // separator for output (';' or '=')
} CMD;

CMD* createCMD (char** tokens, int counter) {
    CMD* cmd = malloc(sizeof(CMD));
    if (mallocErrorCheck (cmd)) exit (EXIT_FAILURE);
    cmd->query = -1;
    cmd->id = -1;
    cmd->topN = -1;
    cmd->paises = NULL;
    cmd->ageMin = -1;
    cmd->ageMax = -1;
    cmd->separator = ';';

    int query;
    if (tokens[0] && convertToInt (tokens[0][0], &query)) cmd->query = query;
    else {
        perror ("Error getting cmd query number");
        exit (EXIT_FAILURE);
    }
    if (tokens[0][1] && strcmp (tokens[0][1], 'S') == 0) cmd->separator = '=';

    switch (cmd->query) {
    case 1:
        int id;
        if (tokens[1] && convertToInt (tokens[1]+1, &id)) cmd->id = id;
        break;
    case 2:
        int topN;
        if (tokens[1] && convertToInt (tokens[1], &topN)) cmd->topN = topN;
        if (counter == 3 && tokens[2]) cmd->paises = strdup (trimString (tokens[2]));
        break;
    case 3:
        int ageMin, ageMax;
        if (tokens[1] && convertToInt (tokens[1], &ageMin)) cmd->ageMin = ageMin;
        if (tokens[2]&& convertToInt (tokens[2], &ageMax)) cmd->ageMax = ageMax;
        break;
    }

    return cmd;
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

char getCMDSeparator (CMD* cmd) {
    return cmd->separator;
}