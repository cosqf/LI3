#include <processInput.h>
#include <validateUser.h>
#include <artists.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

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
        perror ("Error getting the command from input");
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
        if (cmd->paises != NULL) strcpy(cmd->paises, token); 
        else {
            perror ("Malloc Error");
            exit (EXIT_FAILURE);
        }
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


User* parseDataU(char *str, User *user) {
    if (!str || !user) return NULL; 

    char *token = NULL;

    // Parsing the user ID, skipping the U 
    token = trimString(strsep(&str, ";"));
    if (token && token[0] == 'U') user->username = atoi(token + 1);
    else {
        perror ("Id parsing error");
        return NULL;
    }
    // Parsing the email
    token = strsep(&str, ";");
    if (token && validEmail(trimString(token))) user->email = strdup(trimString(token));
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

    if (token) {
        user->buffer = strdup(trimString(token));
        user->birth_date = parseDate(trimString(token));
        if (user->birth_date.error == 1) {
            perror("Invalid birthdate");
            return NULL;
        }
    } else {
        perror("Date parsing error");
        return NULL;
    }
    
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
        else if (strcmp (trimString(token), "premium") == 0) user->subscription_type = 1;
        else {
            perror("Invalid subscription type");
            return NULL;
        }
    }
    else {
        perror("Subscription type parsing error");
        return NULL;
    }

    // Parsing the liked music IDs
    user->liked_musics_id = parseIDs(str, user, Users);
    if (user->liked_musics_id == NULL) {
        perror("Liked music IDs parsing error");
        return NULL;
    }

    return user;
}

Artist* parseDataA (char *str, Artist *artist) {
     if (!str || !artist) return NULL; 

    char *token = NULL;

    // Parsing the user ID, skipping the A 
    token = trimString(strsep(&str, ";"));
    if (token && token[0] == 'A') artist->id = atoi(token + 1);
    else {
        perror ("Id parsing error");
        return NULL;
    }

    // Parsing name
    token = strsep(&str, ";");
    if (token) artist->name = strdup(trimString(token));
    else {
        perror("Name parsing error");
        return NULL;
    }

    // Parsing description
    token = strsep(&str, ";");
    if (token) artist->description = strdup(trimString(token));
    else {
        perror("Description parsing error");
        return NULL;
    }

    // Parsing recipe per stream
    token = strsep(&str, ";");
    if (token) artist->recipe_per_stream = atof(trimString(token));
    else {
        perror("Recipe parsing error");
        return NULL;
    }

    // Parsing the ID constituents
    token = strsep(&str, ";");
    artist->id_constituent = parseIDs(token, artist, Artists);
    if (artist->id_constituent == NULL && artist->id_constituent_counter != 0) {
        perror("ID constituents parsing error");
        return NULL;
    }

    // Parsing the country
    token = strsep(&str, ";");
    if (token) artist->country = strdup(trimString(token));
    else {
        perror("Country parsing error");
        return NULL;
    }

    // Parsing the type
    token = strsep(&str, ";");
    if (token) artist->type = atoi(trimString(token));
    else {
        perror("Type parsing error");
        return NULL;
    }
   return artist;
}

Music* parseDataM (char *str, Music *music) {
    if (!str || !music) return NULL; 

    char *token = NULL;

    // Parsing the user ID, skipping the S
    token = trimString(strsep(&str, ";"));
    if (token && token[0] == 'S') music->id = atoi(token + 1);
    else {
        perror ("Id parsing error");
        return NULL;
    }   
    // Parsing title
    token = strsep(&str, ";");
    if (token) music->title = strdup(trimString(token));
    else {
        perror("Title parsing error");
        return NULL;
    }
    // Parsing the ID constituents
    token = strsep(&str, ";");
    music->artist_id = parseIDs(token, music, Musics);
    if (music->artist_id == NULL && music->artist_id_counter != 0) {
        perror("ID constituents parsing error");
        return NULL;
    }
    // Parsing the duration
    token = strsep(&str, ";");
    if (token) music->buffer = strdup(trimString(token));
    else {
        perror("Duration parsing error");
        return NULL;
    }

    // Parsing the genre
    token = strsep(&str, ";");
    if (token) music->genre = strdup(trimString(token));
    else {
        perror("Genre parsing error");
        return NULL;
    }

    // Parsing the year
    token = strsep(&str, ";");
    if (token) music->year = atoi(trimString(token));
    else {
        perror("Year parsing error");
        return NULL;
    }

    // Parsing lyrics
    token = strsep(&str, ";");
    if (token) music->lyrics = strdup(trimString(token));
    else {
        perror("Lyrics parsing error");
        return NULL;
    }

    return music;
}

// Validating the user's birthdate, ensuring it's in the correct format and not more recent than 09/09/2024
Date parseDate(char* dateStr) {
    Date date;

    if (sscanf(dateStr, "%d/%d/%d", &date.year, &date.month, &date.day) != 3) date.error = 1;
    else if (date.year > 2024) date.error = 1;
    else if (date.year == 2024){
        if (date.month > 9) date.error = 1;
        if (date.month == 9 && (date.day < 1 || date.day > 9)) date.error = 1;
    }
    else if (date.month < 1 || date.month > 12 || date.day < 1 || date.day > 31) date.error = 1;
    else date.error = 0;

    return date;
}

int* parseIDs(char *line, void* IDnum, DataType type) {
    if (line == NULL) return NULL;

    char * token = NULL;
    int *ids = NULL;
    int count=0;

    int len = strlen (line);
    line [len - 1] = '\0';
    line = trimString (line);

    if (strlen (line) == 0) {
        updateCount (IDnum, type, count);
        return NULL;
    }

    for (count = 0; (token = strsep (&line, ",")) != NULL; count ++) {
        token = trimString (token);
        if (token != NULL && (token[0] == 'S' || token[0] == 'A') ) {
            ids = realloc (ids, sizeof(int) * (count + 1));
            if (ids == NULL) {
                perror ("Realloc error");
                exit (EXIT_FAILURE);
            }
            ids[count] = atoi (token + 1);
        }
    }
    updateCount (IDnum, type, count);
    return ids;
}
