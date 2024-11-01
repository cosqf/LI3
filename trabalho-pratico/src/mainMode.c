#include <stdio.h>
#include <modes.h>
#include <string.h>
// will choose the mode (test, normal)

int main (int argc, char** argv){
    if (argc == 3) principal(argv[1], argv[2]);

    else if (argc == 4) tests(argv[1], argv[2]);

    else {
        perror ("Wrong number of arguments");
        return 1;
    }

    return 0;
}