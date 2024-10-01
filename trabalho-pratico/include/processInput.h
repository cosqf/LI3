#ifndef _PROCESSINPUT_H_
#define _PROCESSINPUT_H_

typedef struct cmd {
    int query;     // 1, 2, or 3
    int id;         // user ID
    int topN;       // top N lugares
    char *paises;   // (requires memory allocation)
    int ageMin;     // minimum age
    int ageMax;     // maximum age
} CMD;

CMD* getCommand(char* input, CMD* cmd);
#define DEFAULT 500

#endif  
