#include <history.h>

#ifndef _HISTORYMANAGER_H_
#define _HISTORYMANAGER_H_

typedef struct historyManager HistoryManager;

void insertHistoryHash (HistoryManager *h_mngr, int key, History *history);

HistoryManager* initializeHashHistory ();

void freeHashHistory (HistoryManager* h_mngr);

void getDataHistory (char *path, HistoryManager* mngr);

void callbackHistory(char **tokens, void *manager, Output *output);

#endif