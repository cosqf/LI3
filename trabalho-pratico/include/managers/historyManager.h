#include <history.h>

#ifndef _HISTORYMANAGER_H_
#define _HISTORYMANAGER_H_

typedef struct historyManager HistoryManager;
void callbackHistory(char **tokens, void *manager, Output *output);
void getDataHistory (char *path, HistoryManager* mngr);

#endif