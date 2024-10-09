#ifndef _PARSINGCMD_H_
#define _PARSINGCMD_H_

typedef struct cmd {
    int query;     // 1, 2, or 3
    int id;         // user ID
    int topN;       // top N places
    char *paises;   // (requires memory allocation)
    int ageMin;     // minimum age
    int ageMax;     // maximum age
} CMD;

CMD* getCommand(char* , CMD* );

void getCommandQuery1 (char* line, CMD* cmd);

void getCommandQuery2 (char* line, CMD* cmd, char* token) ;

void getCommandQuery3 (char* line, CMD* cmd, char* token);

#endif