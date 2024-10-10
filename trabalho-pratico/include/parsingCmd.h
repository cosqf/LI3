#ifndef _PARSINGCMD_H_
#define _PARSINGCMD_H_

typedef struct cmd CMD;

CMD* createCMD();

CMD* getCommand(char* , CMD* );

void getCommandQuery1 (char* line, CMD* cmd);

void getCommandQuery2 (char* line, CMD* cmd, char* token) ;

void getCommandQuery3 (char* line, CMD* cmd, char* token);

void freeCmd (CMD *cmd);

#endif