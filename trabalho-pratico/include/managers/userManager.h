#include <users.h>
#include <glib.h>
#include <output_handling/errorfiles.h>
#include <historyManager.h>
#include <musicManager.h>

typedef struct hashtableManager hashtableManager;

#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_

typedef struct userManager UserManager;

void insertUserHash (UserManager *u_mngr, int key, User *User);

UserManager* initializeHashUser ();

void freeHashUser (UserManager* u_mngr);

User* lookupUserHash (UserManager *u_mngr, int id);

GHashTable* getUserTable (UserManager *u_mngr);

int getDataUser (char* path, hashtableManager* mngr);

void callbackUser(char **tokens, void *manager, Output *output);

bool userMatrixIsInitialized (UserManager* mngr);

void createMatrix(HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr);

void fillUserIDArray(UserManager* u_mngr);

void updateMatrix (gpointer key, gpointer value, gpointer data);

void freeMatrix(int** matrix, int rows);

void freeUserArray(char** array, int rows);

void processHistory (int** matrix, gpointer value, int line, MusicManager* m_mngr);

void recomendations(char* targetID, char* genre_array[10], int lines_used, int noUsers, UserManager* u_mngr, char*** recUsers);

int getUserMatrixLinesAvail (UserManager *u_mngr);

int getUserMatrixLinesUsed (UserManager *u_mngr);

#endif