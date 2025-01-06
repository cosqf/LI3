#include <users.h>
#include <glib.h>
#include <userManager.h>
#include <almightyManager.h>
#include <musicManager.h>
#include <historyManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <queryUtils.h>
#include <output_handling/errorfiles.h>
#include <validateDatatypes.h>
#include <recomendador.h>

typedef struct userManager {
    GHashTable *user;
    int** listenedGenresMatrix;
    char** usersIDArray;
    int matrix_lines_available;
    int matrix_lines_used;
} UserManager;


//hashtable
void insertUserHash (UserManager *u_mngr, int key, User *user) {
    g_hash_table_insert(u_mngr->user, GINT_TO_POINTER (key), user);
}

UserManager* initializeUserManager () {
    UserManager* u_mngr = malloc (sizeof (UserManager));
    if (u_mngr == NULL) {
        perror("Failed to allocate memory for UserManager");
        exit(EXIT_FAILURE); 
    }
    u_mngr->user = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteUser);
    u_mngr->listenedGenresMatrix = NULL;
    u_mngr->usersIDArray = NULL;
    u_mngr->matrix_lines_available = 0;
    u_mngr->matrix_lines_used = 0;

    return u_mngr;
}

void freeUserManager (UserManager* u_mngr) {
    g_hash_table_destroy (u_mngr->user);
    freeMatrix(u_mngr->listenedGenresMatrix, u_mngr->matrix_lines_available);
    freeUserArray(u_mngr->usersIDArray, u_mngr->matrix_lines_available);
    free (u_mngr);
}

User* lookupUserHash (UserManager *u_mngr, int id) {
    User* user = g_hash_table_lookup (u_mngr->user, GINT_TO_POINTER(id));
    if (user == NULL) return NULL;
    return copyUser (user);
}

void iterateUser(UserManager* u_mngr, void (*UserProcessor)(gpointer key, gpointer value, gpointer user_data), gpointer user_data) {
    g_hash_table_foreach (u_mngr->user, UserProcessor, user_data);
}

int getDataUser (char* path, AlmightyManager* mngr) {
    Output* output = openErrorOutputUser ();
    
    int error = parseFile(path, callbackUser, mngr, output);

    closeOutputFile (output);

    if (error) return 1;
    else return 0;
}

// creates an userString according to its tokens and validates them. 
// if valid, its converted to an user and added to the hashtable
void callbackUser(char **tokens, void *manager, Output *output) { // receives entity manager
    AlmightyManager* mngr = (AlmightyManager*) manager;
    UserManager* user_mngr = getUserManager(mngr);
    MusicManager* music_mngr = getMusicManager(mngr);

    UserString* userS = createUserString(tokens);
    if (!validUser(userS, music_mngr)) insertErrorFileUser(userS, output);
    else {
        User* user = createUser (tokens);
        insertUserHash(user_mngr, getUserID(user), user);
    }
    deleteUserString(userS);
}

//matrix and array

bool userMatrixIsInitialized (UserManager* u_mngr) {
    if (u_mngr->listenedGenresMatrix) return 1;
    else return 0;
}

void createMatrixAndArray (HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr){ //returns the number of lines occupied

    int matrix_lines = g_hash_table_size(u_mngr->user);

    u_mngr->listenedGenresMatrix = (int**)malloc(matrix_lines * sizeof(int*));
    if (mallocErrorCheck (u_mngr->listenedGenresMatrix)) return;
    
    u_mngr->usersIDArray = (char**)malloc(matrix_lines * sizeof(char*));
    if (mallocErrorCheck (u_mngr->usersIDArray)) {
        freeMatrix(u_mngr->listenedGenresMatrix, matrix_lines);
        return;
    }

    for (int i = 0; i < matrix_lines; i++) {
        u_mngr->listenedGenresMatrix[i] = calloc(10, sizeof(int));
        if (mallocErrorCheck (u_mngr->listenedGenresMatrix[i])) {
            freeMatrix(u_mngr->listenedGenresMatrix, matrix_lines);
            freeUserArray(u_mngr->usersIDArray, matrix_lines);
            return;
        }
        u_mngr->usersIDArray[i] = calloc(9, sizeof(char));
        if (mallocErrorCheck (u_mngr->usersIDArray[i])) {
            freeMatrix(u_mngr->listenedGenresMatrix, matrix_lines);
            freeUserArray(u_mngr->usersIDArray, matrix_lines);
            return;
        }
    }

    u_mngr->matrix_lines_available = matrix_lines;
    u_mngr->matrix_lines_used = 0;

    fillUserIDArray(u_mngr);

    MatrixFeeder feeder = {.m_mngr = m_mngr,
                           .u_mngr = u_mngr
                          };

    traverseHistorybyUser(h_mngr, updateMatrix, &feeder);
}

void fillUserIDArray(UserManager* u_mngr) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, u_mngr->user);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int position = u_mngr->matrix_lines_used;
        int currentID = GPOINTER_TO_INT(key);

        char* IDStr = formatUserID(currentID);
        strcpy(u_mngr->usersIDArray[position], IDStr);
        free(IDStr);

        User* currentUser = lookupUserHash(u_mngr, currentID);
        setUserArrayPosition(currentUser, position);
        insertUserHash(u_mngr, currentID, currentUser); //replaces the User in the hastable with an updated one

        u_mngr->matrix_lines_used++;
    }
}

void updateMatrix(gpointer key, gpointer value, gpointer data) {
    MatrixFeeder* feeder = (MatrixFeeder*)data; 
    MusicManager* m_mngr = feeder->m_mngr;
    UserManager* u_mngr = feeder->u_mngr;

    int userID = GPOINTER_TO_INT(key);
    User* user = lookupUserHash(u_mngr, userID);

    int line = getUserArrayPosition(user);

    processHistory(u_mngr->listenedGenresMatrix, value, line, m_mngr);

    deleteUser(user);
}

int** copyMatrix(int** matrix, int rows, int columns) {
    int** newmatrix = (int**)malloc(rows * sizeof(int*));
    if (mallocErrorCheck (newmatrix)) return NULL;

    for (int i = 0; i < rows; i++) {
        newmatrix[i] = calloc(columns, sizeof(int));
        if (mallocErrorCheck (matrix[i])) {
            freeMatrix(newmatrix, rows);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            newmatrix[i][j] = matrix[i][j];
        }
    }

    return newmatrix;
}

char** copyUserArray (char** array, int slots) {
    char** newarray = (char**)malloc(slots * sizeof(char*));
    if (mallocErrorCheck (newarray)) return NULL;

    for (int i = 0; i < slots; i++) {
        newarray[i] = calloc(9, sizeof(char));
        if (mallocErrorCheck (newarray[i])) {
            freeUserArray(newarray, slots);
            return NULL;
        }
    }

    for (int i = 0; i < slots; i++) {
        strcpy(newarray[i], array[i]);
        newarray[i][8] = '\0';
    }

    return newarray;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeUserArray(char** array, int slots) {
    for (int i = 0; i < slots; i++) {
        free(array[i]);
    }
    free(array);
}

void processHistory (int** matrix, gpointer value, int line, MusicManager* m_mngr) {
    while (value) {
        int musicID = getHistoryMusicId(value);
        Music* music = lookupMusicHash(m_mngr, musicID);

        switch (getMusicGenre(music)) {
            case GENRE_METAL: matrix[line][0]++; break;
            case GENRE_REGGAE: matrix[line][1]++; break;
            case GENRE_JAZZ: matrix[line][2]++; break;
            case GENRE_HIPHOP: matrix[line][3]++; break;
            case GENRE_CLASSICAL: matrix[line][4]++; break;
            case GENRE_ROCK: matrix[line][5]++; break;
            case GENRE_BLUES: matrix[line][6]++; break;
            case GENRE_COUNTRY: matrix[line][7]++; break;
            case GENRE_POP: matrix[line][8]++; break;
            case GENRE_ELECTRONIC: matrix[line][9]++; break;
            default: break;
        }

        value = getNextHistoryByUser(value);
        deleteMusic(music);
    }
}

void recommendations(char* targetID, char* genre_array[10], int lines_used, int noUsers, UserManager* u_mngr, char*** recUsers) {
    int** matrix = copyMatrix(u_mngr->listenedGenresMatrix, lines_used, 10);
    char** userArray = copyUserArray(u_mngr->usersIDArray, lines_used);

    char** recs = recomendaUtilizadores(targetID, matrix, userArray, genre_array, lines_used, 10, noUsers);
    /*after some experimentation we concluded that the array returned by recomendaUtilizadores doesn't allocate memory
    for itself, which led to trouble on our part trying to manage it before understanding. Here we create an independent
    copy of the return array, so that we can freely free the matrix and user array copies, without messing up the user
    recommendations that we need to access in a later stage.*/
    *recUsers = copyUserArray(recs, noUsers);

    freeMatrix(matrix, lines_used);
    freeUserArray(userArray, lines_used);
    free(recs);
}

int getUserMatrixLinesAvail (UserManager *u_mngr) {
    return u_mngr->matrix_lines_available;
}

int getUserMatrixLinesUsed (UserManager *u_mngr) {
    return u_mngr->matrix_lines_used;
}
