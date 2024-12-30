#include <parsingUtils.h>

#ifndef _CMD_H_
#define _CMD_H_

typedef struct cmd CMD;

CMD* createCMD(char** tokens, int count);

CMD* createEmptyCMD ();

void freeCmd (CMD *cmd);

int getCMDquery (CMD* cmd);

char getCMDentity (CMD* cmd);

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

void setCMDQuery(CMD* cmd, int query);

void setCMDEntity(CMD* cmd, char entity);

void setCMDId(CMD* cmd, int id);

void setCMDTopN(CMD* cmd, int topN);

void setCMDCountry(CMD* cmd, const char* paises);

void setCMDAgeMin(CMD* cmd, int ageMin);

void setCMDAgeMax(CMD* cmd, int ageMax);

void setCMDDateMin(CMD* cmd, Date dateMin);

void setCMDDateMax(CMD* cmd, Date dateMax);

void setCMDNoUsers(CMD* cmd, int noUsers);

void setCMDYear(CMD* cmd, short int year);

void setCMDNArtists(CMD* cmd, short int nArtists);
#endif