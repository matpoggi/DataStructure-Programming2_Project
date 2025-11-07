#include <stdio.h>
#include "list.h"
#include "utils.h"

#include <unistd.h>
#include <limits.h>

// MAIN FUNCTION //
int main() {

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("[main-----] Current working directory: %s\n", cwd);
    }

    printf("[main-----] Starting program...\n\n");

    adjacency_list G = readGraph("../data/exemple_valid_step3.txt");

    printf("\n[main-----] Graph loaded successfully.\n");

    isMarkov(G);

    drawGraph(G);

    return 0;
}
