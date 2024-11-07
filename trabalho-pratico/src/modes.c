#define _GNU_SOURCE and #define _POSIX_C_SOURCE 1999309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

#include <modes.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <cmd.h>
#include <query1.h>
#include <query2.h>
#include <query3.h>
#include <hashtableManager.h>
#include <cmdManager.h>

int principal (char* pathData, char* pathCmd) {
    hashtableManager* mngr = initializeHash ();

    getData (pathData, mngr);

    cmdManager* cmdMngr = createCmdManager ();
    int cmdNumber = readCommands (pathCmd, cmdMngr);

    for (int i = 0; i< cmdNumber; i++) {
        CMD* cmd = getCommandFromMngr (cmdMngr, i);
        
        switch (getCMDquery (cmd)) {
        case 1:
            query1 (cmd, getUserManager(mngr), i+1);
            break;

        case 2:
            query2 (cmd, mngr, i+1);
            break;

        case 3:
            query3 (cmd, getUserManager(mngr), getMusicManager(mngr), i+1);
            break;

        default:
            perror ("CMD ERROR");
            exit (EXIT_FAILURE);
        }
    }
    freeCmdManager (cmdMngr);
    freeHash (mngr);
    return 0;
}

void test_principal (char* pathData, char* pathCmd) { // argv[1]: path to data, argv[2]: cmd //flag is 1 if principal is running from the test program, 0 if running alone
    struct timespec cmdstart, cmdend;
    double q1total = 0, q2total = 0, q3total = 0;

    int i = 1, q1c = 0, q2c = 0, q3c = 0; // i counts the total commands run, the others count the commands run for each query
    int correctQ1 = 0, correctQ2 = 0, correctQ3 = 0; // counts the commands that execute correctly
    hashtableManager* mngr = initializeHash ();

    getData (pathData, mngr);

    cmdManager* cmdMngr = createCmdManager ();
    int cmdNumber = readCommands (pathCmd, cmdMngr);

    for (; i< cmdNumber+1; i++) {
        CMD* cmd = getCommandFromMngr (cmdMngr, i-1);

        char output[100];
        char expected[100];

        switch (getCMDquery (cmd)) {
        case 1:
            q1c++;
            clock_gettime(CLOCK_REALTIME, &cmdstart); //Get the start time

            query1 (cmd, getUserManager(mngr), i);

            clock_gettime(CLOCK_REALTIME, &cmdend); //Get the end time
            q1total += (cmdend.tv_sec - cmdstart.tv_sec) + (cmdend.tv_nsec - cmdstart.tv_nsec) / 1e9;

            snprintf(output, sizeof(output), "resultados/command%d_output.txt", i);
            snprintf(expected, sizeof(expected), "outputs_esperados/command%d_output.txt", i);
    
            if(compareFiles(output, expected, i) == true) correctQ1++;

            break;

        case 2:
            q2c++;
            clock_gettime(CLOCK_REALTIME, &cmdstart); //Get the start time

            query2 (cmd, mngr, i);

            clock_gettime(CLOCK_REALTIME, &cmdend); //Get the end time
            q2total += (cmdend.tv_sec - cmdstart.tv_sec) + (cmdend.tv_nsec - cmdstart.tv_nsec) / 1e9;

            snprintf(output, sizeof(output), "resultados/command%d_output.txt", i);
            snprintf(expected, sizeof(expected), "outputs_esperados/command%d_output.txt", i);
    
            if(compareFiles(output, expected, i) == true) correctQ2++;
            break;

        case 3:
            q3c++;
            clock_gettime(CLOCK_REALTIME, &cmdstart); //Get the start time

            query3 (cmd, getUserManager(mngr), getMusicManager(mngr), i);

            clock_gettime(CLOCK_REALTIME, &cmdend); //Get the end time
            q3total += (cmdend.tv_sec - cmdstart.tv_sec) + (cmdend.tv_nsec - cmdstart.tv_nsec) / 1e9;

            snprintf(output, sizeof(output), "resultados/command%d_output.txt", i);
            snprintf(expected, sizeof(expected), "outputs_esperados/command%d_output.txt", i);
    
            if(compareFiles(output, expected, i) == true) correctQ3++;
            break;
        default:
            perror ("CMD ERROR");
            exit (EXIT_FAILURE);
        }
    }

    printf("Q1: %d de %d testes OK.\n", correctQ1, q1c);
    printf("Q2: %d de %d testes OK.\n", correctQ2, q2c);
    printf("Q3: %d de %d testes OK.\n\n", correctQ3, q3c);

    double q1avg = q1total / q1c * 1e3;
    double q2avg = q2total / q2c * 1e3;
    double q3avg = q3total / q3c * 1e3;

    printf("Tempos médios de execução:\n\tQ1: %.2f ms\n\tQ2: %.2f ms\n\tQ3: %.2f ms\n\n", q1avg, q2avg, q3avg);
    
    freeCmdManager (cmdMngr);
    freeHash (mngr);
}


int tests (char* pathData, char* pathCmd) { // argv[1]: path to data, argv[2]: cmd, argv[3]: expected outputs
    struct timespec totalstart, totalend;
    double totalelapsed;
    clock_gettime(CLOCK_REALTIME, &totalstart); // Get the start time

    test_principal(pathData, pathCmd);

    // Memory Usage
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    long int mem = r_usage.ru_maxrss/1024; // Conversion to MBs
    printf("Memória usada: %ld MB\n", mem);

    clock_gettime(CLOCK_REALTIME, &totalend); // Get the end time

    totalelapsed = (totalend.tv_sec - totalstart.tv_sec) + (totalend.tv_nsec - totalstart.tv_nsec) / 1e9; // Total elapsed time

    printf("Tempo total de execução: %.2f segundos\n", totalelapsed);

    return 0;
}


int compareFiles(char* output, char* expected, int queryn) {
    FILE *outp = fopen(output, "r");
    FILE *exp = fopen(expected, "r");

    if (outp == NULL) {
        printf("Erro a abrir %s\n", output);
        return 0;
    }
    if (exp == NULL) {
        printf("Erro a abrir %s\n", expected);
        return 0;
    }

    char line1[500];
    char line2[500];
    int  line = 1;

    // Compare the files line by line
    while (fgets(line1, sizeof(line1), outp) != NULL && fgets(line2, sizeof(line2), exp) != NULL) {
        if (strcmp(line1, line2) != 0) {
            printf("Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", queryn, line, queryn);
            fclose(outp);
            fclose(exp);
            return 0;
        }
        line++;
    }

    fclose(outp);
    fclose(exp);
    return 1;
}