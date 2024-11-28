#include <parsingUtils.h>

#ifndef _CMD_H_
#define _CMD_H_

typedef struct cmd CMD;

CMD* createCMD(char** tokens, int count);

void freeCmd (CMD *cmd);

int getCMDquery (CMD* cmd);

int getCMDId (CMD* cmd);

int getCMDtopN (CMD* cmd);

char *getCMDCountry (CMD* cmd);

int getCMDAgeMin (CMD* cmd);

int getCMDAgeMax (CMD* cmd);

char getCMDSeparator (CMD* cmd);

Date getCMDdateMin (CMD* cmd);

Date getCMDdateMax(CMD* cmd);

int getCMDnoUsers(CMD* cmd);

short int getCMDyear(CMD* cmd);

short int getCMDnArtists(CMD* cmd);
#endif