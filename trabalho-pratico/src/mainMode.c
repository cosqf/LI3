#include <stdio.h>
#include <modes.h>
#include <string.h>
// will choose the mode (test, normal)

int main (int argc, char** argv){
    if (argc == 3) principal(argv);

    else if (argc == 4) tests(argv);

    else {
        perror ("Wrong number of arguments");
        return 1;
    }

    return 0;
}