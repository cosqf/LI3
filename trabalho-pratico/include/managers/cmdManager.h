#ifndef _CMDMANAGER_H_
#define _CMDMANAGER_H_

typedef struct cmdmanager cmdManager;

cmdManager* createCmdManager ();

int readCommands (char* path, cmdManager *mngr);

int getCommandsCounter (cmdManager *mngr);

CMD* getCommandFromMngr (cmdManager *mngr, int i);

void freeCmdManager (cmdManager *mngr);
#endif