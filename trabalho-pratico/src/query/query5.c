// /**
//  * @brief Calcula recomendações de utilizadores
//  *
//  * @param idUtilizadorAlvo Id do utilizador alvo para gerar recomendações
//  * @param matrizClassificacaoMusicas Uma matriz contendo para cada utilizador
//  * (linhas) o número de vezes que ouviu músicas de cada género de música
//  * (colunas)
//  * @param idsUtilizadores Um array contendo os ids de cada utilizador seguindo a
//  * mesma ordem da matriz
//  * @param nomesGeneros Um array contendo o nome de cada género de música
//  * seguindo a mesma ordem da matriz
//  * @param numUtilizadores O número total de utilizadores
//  * @param numGeneros O número total de géneros de música
//  * @param numRecomendacoes O número de recomendações para calcular
//  * @return Um array de ids de utilizadores recomendados com tamanho
//  * <b>numRecomendacoes</b>
//  * @note O número máximo de recomendações é <b>numUtilizadores - 1</b>. Caso
//  * <b>numRecomendacoes</b> ultrapasse este valor, o mesmo será automaticamente
//  * truncado.
//  */
// char **recomendaUtilizadores(char *idUtilizadorAlvo,
//                              int **matrizClassificacaoMusicas,
//                              char **idsUtilizadores, char **nomesGeneros,
//                              int numUtilizadores, int numGeneros,
//                              int numRecomendacoes);

#include <query5.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <history.h>
#include <historyManager.h>
#include <cmd.h>
#include <recomendador.h>

typedef struct {
    MusicManager* m_mngr;
    int** matrix;
    int matrix_lines;
    int users_read;
    char** user_array;
} Q5Feeder;

void query5 (CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr, int counter){
    //printf("#1 start q5\n"); //DEBUG
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", counter);

    Output* output = openOutputFile (filename);

    int id = getCMDId(cmd);
    User* targetUser = lookupUserHash(u_mngr, id);
    if(!targetUser){
        writeNewLine(output);
        closeOutputFile(output);
        deleteUser(targetUser);
        return;
    }
    deleteUser(targetUser);
    char* targetID = formatUserID(id); //idUtilizadorAlvo

    int noUsers = getCMDnoUsers(cmd); //numRecomendacoes

    // Initial allocation for the matrix and the array that contain the users IDs
    int matrix_lines = 100000; //212685
    int** matrix = (int**)malloc(matrix_lines * sizeof(int*));
    char** user_array = (char**)malloc(matrix_lines * sizeof(char*));
    for (int i = 0; i < matrix_lines; i++) {
        matrix[i] = calloc(10, sizeof(int));
        user_array[i] = calloc(9, sizeof(char));
    }

    //printf("#1.5 allocations successful\n"); //DEBUG
    
    char* genre_array [10] = {"Metal", "Reggae", "Jazz", "Hip Hop", "Classical", "Rock", "Blues", "Country", "Pop", "Electronic"};

    Q5Feeder feeder = {.m_mngr = m_mngr,
                       .matrix = matrix,
                       .matrix_lines = matrix_lines,
                       .users_read = 0,
                       .user_array = user_array
                      };

    traverseHistorybyUser(h_mngr, updateMatrix, &feeder);
    //printf("#2 traversion done\n"); //DEBUG

    int lines_used = feeder.users_read;
    matrix_lines = feeder.matrix_lines;
    matrix = feeder.matrix;
    user_array = feeder.user_array;

     //printf("matrix_lines: %d / users_read: %d\n", feeder.matrix_lines, feeder.users_read); //DEBUG
     //printMatrix(matrix_lines, 10, matrix);


    // if (lines_used < matrix_lines) {
    //     matrix = resizeMatrix(matrix, matrix_lines, lines_used, 10);
    //     user_array = resizeUserArray(user_array, matrix_lines, lines_used, 9);
    // }
    //matrix_lines = lines_used;
    //printf("#3 trims done\n"); //DEBUG
    //printf("matrix_lines: %d / users_read: %d\n", feeder.matrix_lines, feeder.users_read); //DEBUG
    //printMatrix(matrix_lines, 10, matrix);

    char** recUsers = recomendaUtilizadores(targetID, matrix, user_array, genre_array, lines_used, 10, noUsers);
    //printf("\n#4 recs obtained\n"); //DEBUG

    if (!recUsers) writeNewLine(output);
    else {
        for (int i = 0; i < noUsers; i++) {
            setOutput (output, &recUsers[i], 1);
            writeQuerys (output, cmd);
        }
    }

    closeOutputFile(output);
    //printf("#5 outputted\n"); //DEBUG

    freeMatrix(matrix, lines_used);
    freeUserArray(user_array, lines_used);

    //printf("#6 freed\n"); //DEBUG

    // // Free recUsers
    // for (int i = 0; i < noUsers; i++){
    //     free(recUsers[i]);
    //     recUsers[i] = NULL;
    // }
    if (recUsers) free(recUsers);
    recUsers = NULL;

    //printf("#7 ending\n\n"); //DEBUG
}

void updateMatrix(gpointer key, gpointer value, gpointer feeder) {
    Q5Feeder* q5feeder = (Q5Feeder*)feeder; 
    MusicManager* m_mngr = q5feeder->m_mngr;
    int** matrix = q5feeder->matrix;
    int lines_available = q5feeder->matrix_lines;
    int lines_used = q5feeder->users_read;
    char** user_array = q5feeder->user_array;

    // Resize matrix if necessary
    if (lines_used == lines_available) {
        lines_available += 100000;

        matrix = resizeMatrix(matrix, lines_used, lines_available, 10);
        user_array = resizeUserArray(user_array, lines_used, lines_available, 9);

        q5feeder->matrix = matrix;
        q5feeder->user_array = user_array;
        q5feeder->matrix_lines = lines_available;
    }

    int userID = GPOINTER_TO_INT(key);
    char* userIDstr = formatUserID(userID);
    strcpy(user_array[lines_used], userIDstr);
    free(userIDstr);

    // Process user history
    while (value) {
        int musicID = getHistoryMusicId(value);
        Music* music = lookupMusicHash(m_mngr, musicID);

        switch (getMusicGenre(music)) {
            case GENRE_METAL: matrix[lines_used][0]++; break;
            case GENRE_REGGAE: matrix[lines_used][1]++; break;
            case GENRE_JAZZ: matrix[lines_used][2]++; break;
            case GENRE_HIPHOP: matrix[lines_used][3]++; break;
            case GENRE_CLASSICAL: matrix[lines_used][4]++; break;
            case GENRE_ROCK: matrix[lines_used][5]++; break;
            case GENRE_BLUES: matrix[lines_used][6]++; break;
            case GENRE_COUNTRY: matrix[lines_used][7]++; break;
            case GENRE_POP: matrix[lines_used][8]++; break;
            case GENRE_ELECTRONIC: matrix[lines_used][9]++; break;
            default: break;
        }

        value = getNextHistoryByUser(value);
        free(music);
    }

    q5feeder->users_read++;
}

int** resizeMatrix(int** matrix, int currentRows, int newRows, int cols) {
    int** newMatrix;
    if (newRows >= currentRows) {
        newMatrix = (int**)realloc(matrix, newRows * sizeof(int*));
        if (!newMatrix) {
            perror("Failed to reallocate memory for rows");
            return NULL;
        }
        for (int i = currentRows; i < newRows; i++) {
            newMatrix[i] = (int*)calloc(cols, sizeof(int));
            if (!newMatrix[i]) {
                perror("Failed to allocate new row");
                return NULL;
            }
        }
    } else if (newRows < currentRows) {
        for (int i = newRows; i < currentRows; i++) {
            free(matrix[i]);
            matrix[i] = NULL;
        }
        newMatrix = realloc(matrix, newRows * sizeof(int*));
        if (!newMatrix) {
            perror("Failed to realloc matrix");
            exit(EXIT_FAILURE);
        }
    }

    return newMatrix;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

char** resizeUserArray(char** array, int currentRows, int newRows, int cols) {
    char** newArray;
    if (newRows >= currentRows) {
        newArray = (char**)realloc(array, newRows * sizeof(char*));
        if (!newArray) {
            perror("Failed to reallocate memory for rows");
            return NULL;
        }
        for (int i = currentRows; i < newRows; i++) {
            newArray[i] = (char*)calloc(cols, sizeof(char));
            if (!newArray[i]) {
                perror("Failed to allocate new row");
                return NULL;
            }
        }
    } else if (newRows < currentRows) {
        for (int i = newRows; i < currentRows; i++) {
            free(array[i]);
            array[i] = NULL;
        }
        newArray = realloc(array, newRows * sizeof(int*));
        if (!newArray) {
            perror("Failed to realloc matrix");
            exit(EXIT_FAILURE);
        }
    }

    return newArray;
}

void freeUserArray(char** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

char* formatUserID (int id) {
    char* formatted = (char*)malloc(9 * sizeof(char));
    sprintf(formatted, "U%07d", id);
    return formatted;
}


//segfaulting on cmd 69 71 73 74

void printMatrix(int rows, int cols, int** matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}