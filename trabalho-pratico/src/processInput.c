#include <processInput.h>
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


User* parseDataU(char *str, User *user) {
    if (!str || !user) return NULL; 

    char *token = NULL;

    // Parsing the user ID, skipping the U 
    token = trimString(strsep(&str, ";"));
    if (token && token[0] == 'U') user->username = atoi(token + 1);

    // Parsing the email
    token = strsep(&str, ";");
    if (token) user->email = strdup(trimString(token));
    else {
        perror("Email parsing error");
        return NULL;
    }

    // Parsing first name
    token = strsep(&str, ";");
    if (token) user->first_name = strdup(trimString(token));
    else {
        perror("First name parsing error");
        return NULL;
    }

    // Parsing last name
    token = strsep(&str, ";");
    if (token) user->last_name = strdup(trimString(token));
    else {
        perror("Last name parsing error");
        return NULL;
    }

    // Parsing the birth date
    token = strsep(&str, ";");

    if (token) user->buffer = strdup(trimString(token));
    else {
        perror("Date parsing error");
        return NULL;
    }
    /*
    if (token) {
        Date date = parseDate(trimString(token)); 
        if (date.error == 1) {
            perror("Date parsing error");
            return NULL; 
        }

        user->birth_date = date;
    } else {
        perror("Birth date parsing error");
        return NULL;
    }
*/
    // Parsing the country
    token = strsep(&str, ";");
    if (token) user->country = strdup(trimString(token));
    else {
        perror("Country parsing error");
        return NULL;
    }

    // Parsing the subscription type
    token = strsep(&str, ";");
    if (token) {
        if (strcmp (trimString(token), "normal") == 0) user->subscription_type = 0;
        else user->subscription_type = 1;
    }
    else {
        perror("Subscription type parsing error");
        return NULL;
    }

    // Parsing the liked music IDs
    user->liked_musics_id = parseIDs(str, user);
    if (user->liked_musics_id == NULL) {
        perror("Liked music IDs parsing error");
        return NULL;
    }

    return user;
}

char *trimString(char *str) {
    if (!str) return NULL;

    while (*str == '"' || *str == ' ' || *str == '[' || *str == ']' || *str == '\'') {
        str++;
    }

    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '"' || str[len - 1] == ' ' || str[len - 1] == '[' || str[len - 1] == ']' || str[len - 1] == '\'')) {
        str[--len] = '\0';
    }

    return str;
}

Date parseDate(char* dateStr) {
    Date date;
    if (sscanf(dateStr, "%d/%d/%d", &date.year, &date.month, &date.day) != 3) date.error = 1;
    else date.error = 0;
    return date;
}

int* parseIDs(char *line, User *user) {
    if (line == NULL) return NULL;

    char * token = NULL;
    int *ids = NULL;
    int count;

    int len = strlen (line);
    line [len - 1] = '\0';
    line = trimString (line);

    for (count = 0; (token = strsep (&line, ",")) != NULL; count ++) {
        token = trimString (token);
        if (token != NULL && token[0] == 'S') {
            ids = realloc (ids, sizeof(int) * (count + 1));
            if (ids == NULL) {
                perror ("Realloc error");
                exit (EXIT_FAILURE);
            }
            ids[count] = atoi (token + 1);
        }
    }
    user->liked_musics_count = count;
    return ids;
}

void parseDataA (char *str) {
   // filtra ()
}

void parseDataM (char *str) {
   // filtra ()
}