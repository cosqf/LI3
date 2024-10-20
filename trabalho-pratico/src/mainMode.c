#include <stdio.h>
#include <modes.h>
#include <string.h>
// will choose the mode (test, normal)

int main (int argc, char** argv){
    if (argc == 3 && strcmp(argv[0], "./programa-principal") == 0) principal(argv);

    else if (argc == 4 && strcmp(argv[0], "./programa-testes") == 0) tests(argv);

    else {
        perror ("Wrong number of arguments");
        return 1;
    }

    return 0;
}