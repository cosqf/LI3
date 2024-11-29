#include <parsingUtils.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <cmd.h>

typedef struct cmd {
    int query;          // 1, 2, 3, 4, 5, or 6
    char entity;       // A or U (Q1)
    int id;             // entity ID
    int topN;           // top N places
    char *paises;       // (requires memory allocation)
    int ageMin;         // minimum age
    int ageMax;         // maximum age
    Date dateMin;       // minimum date
    Date dateMax;       // max date
    int noUsers;        // number of users to compare with
    short int year;     // year
    short int nArtists; // number of artists
    char separator;     // separator for output (';' or '=')
} CMD;

CMD* createCMD (char** tokens, int counter) {
    CMD* cmd = malloc(sizeof(CMD));
    if (mallocErrorCheck (cmd)) exit (EXIT_FAILURE);
    cmd->query = -1;
    cmd->entity = '\0';
    cmd->id = -1;
    cmd->topN = -1;
    cmd->paises = NULL;
    cmd->ageMin = -1;
    cmd->ageMax = -1;
    cmd->noUsers = 0;
    cmd->year = 0;
    cmd->nArtists = 0;
    cmd->separator = ';';

    int query;
    if (tokens[0]) {
        if (tokens[0][1] == 'S') {
            tokens[0][1] = '\0';
            cmd->separator = '=';
        }

        if (convertToInt(tokens[0], &query)) cmd->query = query;
    }
    else {
        perror ("Error getting cmd query number");
        exit (EXIT_FAILURE);
    }
    switch (cmd->query) {
    case 1:
        cmd->entity = tokens[1][0];//strdup(tokens[1][0]);
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
        if (tokens[2] && convertToInt (tokens[2], &ageMax)) cmd->ageMax = ageMax;
        break;
    case 4:
        if (counter == 3) {
            if (tokens[1]) cmd->dateMin = parseDate (tokens[1]);
            if (tokens[2]) cmd->dateMax = parseDate (tokens[2]);
        }
        break;
    case 5:
        int noUsers;
        if (tokens[1] && convertToInt (tokens[1]+1, &id)) cmd->id = id;
        if (tokens[2] && convertToInt (tokens[2], &noUsers)) cmd->noUsers = noUsers;
        break;
    case 6:
        int year, nArtists;
        if (tokens[1] && convertToInt (tokens[1]+1, &id)) cmd->id = id;
        if (tokens[2] && convertToInt (tokens[2], &year)) cmd->year = year;
        if (tokens[3] && counter == 4 && convertToInt (tokens[3], &nArtists)) cmd->nArtists = nArtists;
        break;
    }

    return cmd;
}

void freeCmd (CMD *cmd) {
    //if (cmd->entity) free (cmd->entity);
    if (cmd->paises) free (cmd->paises);
    free (cmd);
}

int getCMDquery (CMD* cmd) {
    return cmd->query;
}

char getCMDentity (CMD* cmd) {
    //if (cmd->entity == NULL) return NULL;
    //else return strdup (cmd->entity);
    return cmd->entity;
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

Date getCMDdateMin (CMD* cmd) {
    return cmd->dateMin;
}

Date getCMDdateMax(CMD* cmd) {
    return cmd->dateMax;
}

int getCMDnoUsers(CMD* cmd) {
    return cmd->noUsers;
}

short int getCMDyear(CMD* cmd) {
    return cmd->year;
}

short int getCMDnArtists(CMD* cmd) {
    return cmd->nArtists;
}