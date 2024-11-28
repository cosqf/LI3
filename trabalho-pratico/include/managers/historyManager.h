#include <history.h>
#include <queryUtils.h>
#include "output_handling/outputWriter.h"

#ifndef _HISTORYMANAGER_H_
#define _HISTORYMANAGER_H_

typedef struct historyManager HistoryManager;
void callbackHistory(char **tokens, void *manager, Output *output);
void getDataHistory (char *path, HistoryManager* mngr);
int lengthHistory (HistoryManager* mngr);
History** sortHistory (HistoryManager* mngr);


// trees

GTree* initializeHistoryTree();

void insertInHistoryWeeks (HistoryManager* mngr, void* top10artistWeek, Date firstDayOfWeek);

void freeKeyAndValue(gpointer key, gpointer value, gpointer user_data);

void destroyHistoryWeeks(HistoryManager* mngr);

void traverseTreeInRange(HistoryManager* mngr, gboolean callback(gpointer key, gpointer value, gpointer user_data), gpointer feeder);

#endif