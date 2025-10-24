#include <stdio.h>
#include "list.h"

#include <unistd.h>
#include <limits.h>

// MAIN FUNCTION //
int main() {

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("[main-----] Current working directory: %s\n", cwd);
    }

    printf("[main-----] Starting program...\n\n");

    readGraph("../data/exemple1.txt");

    printf("\n[main-----] Graph loaded successfully.\n");

    return 0;
}
