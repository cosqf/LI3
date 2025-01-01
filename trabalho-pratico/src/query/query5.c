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
#include <userManager.h>
#include <cmd.h>

void query5 (CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, UserManager* u_mngr, int counter){

    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", counter);

    Output* output = openOutputFile (filename);

    // Target user information handling
    int noUsers = getCMDnoUsers(cmd); //numRecomendacoes
    int id = getCMDId(cmd);
    User* targetUser = lookupUserHash(u_mngr, id);
    if(!targetUser || noUsers == 0){
        writeNewLine(output);
        closeOutputFile(output);
        deleteUser(targetUser);
        return;
    }
    deleteUser(targetUser);

    if (!userMatrixIsInitialized(u_mngr)) {
        createMatrixAndArray(h_mngr, m_mngr, u_mngr);
    }

    char* targetID = formatUserID(id); //idUtilizadorAlvo
    char* genre_array [10] = {"Metal", "Reggae", "Jazz", "Hip Hop", "Classical", "Rock", "Blues", "Country", "Pop", "Electronic"}; //nomesGeneros
    int lines_used = getUserMatrixLinesUsed(u_mngr); //numUtilizadores

    char** recUsers = NULL;
    recommendations(targetID, genre_array, lines_used, noUsers, u_mngr, &recUsers);

    if (!recUsers) writeNewLine(output);
    else {
        for (int i = 0; i < noUsers; i++) {
            setOutput (output, &recUsers[i], 1);
            writeQuerys (output, cmd);
        }
    }

    closeOutputFile(output);

    freeUserArray(recUsers, noUsers);
    free(targetID);
}