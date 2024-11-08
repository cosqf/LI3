#include <cmd.h>
#ifndef _CMDMANAGER_H_
#define _CMDMANAGER_H_

typedef struct cmdmanager cmdManager;

cmdManager* createCmdManager ();

void processCmdLine (char** tokens, int numberTokens, cmdManager* manager);

int getCommandsCounter (cmdManager *mngr);

CMD* getCommandFromMngr (cmdManager *mngr, int i);

void freeCmdManager (cmdManager *mngr);
#endif