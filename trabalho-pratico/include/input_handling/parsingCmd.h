#ifndef _PARSINGCMD_H_
#define _PARSINGCMD_H_

typedef struct cmd CMD;

CMD* createCMD(int i);

CMD* getCommand(char* , CMD* );

void getCommandQuery1 (char* line, CMD* cmd);

void getCommandQuery2 (char* line, CMD* cmd, char* token) ;

void getCommandQuery3 (char* line, CMD* cmd, char* token);

void freeCmd (CMD *cmd);

int getCMDquery (CMD* cmd);

int getCMDId (CMD* cmd);

int getCMDtopN (CMD* cmd);

char *getCMDCountry (CMD* cmd);

int getCMDAgeMin (CMD* cmd);

int getCMDAgeMax (CMD* cmd);

int getCMDCounter (CMD* cmd);

#endif