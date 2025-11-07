#include <stdio.h>
#include <string.h>
#include "list.h"
#include "utils.h"

#include <unistd.h>
#include <limits.h>

// MAIN FUNCTION
int main() {

    printf("---------------------------------------\n--        Starting program...        -- \n---------------------------------------\n");

    char filepath[200];
    char prefix[] = "..\\data\\";
    char fullpath[250];

    printf("[main--------] Please enter a file path\n->");

    fgets(filepath, sizeof(filepath), stdin);

    for (int i = 0; filepath[i] != '\0'; i++) {
        if (filepath[i] == '/') {
            filepath[i] = '\\';
        }
    }

    filepath[strcspn(filepath, "\n")] = 0;

    strcpy(fullpath, prefix);
    strcat(fullpath, filepath);

    printf("\n---------------------------------------\n[main--------] Starting readGraph...");

    adjacency_list G = readGraph(fullpath);

    printf("---------------------------------------\n[main--------] Starting isMarkov check.\n---------------------------------------\n");

    isMarkov(G);

    printf("---------------------------------------\n[main--------] Starting drawGraph.\n---------------------------------------\n");

    drawGraph(G);

    return 0;
}
