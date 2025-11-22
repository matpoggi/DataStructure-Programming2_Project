#include <stdio.h>
#include <string.h>

#include "list.h"
#include "tarjan.h"
#include "hasse.h"
#include "matrix.h"

#define PRINT_SECTION(title) printf("\n=======================================\n   %s\n=======================================\n", title)
#define PRINT_STEP(msg) printf("[Step] %s\n", msg)

int main() {
    // ---------------------------------------------------------
    // INITIALISATION & INPUT
    // ---------------------------------------------------------
    PRINT_SECTION("INITIALIZATION");

    char filepath[200];
    char prefix[] = "..\\data\\";
    char fullpath[250];

    printf("Please enter the file name (e.g., exemple_meteo.txt):\n-> ");

    if (fgets(filepath, sizeof(filepath), stdin) != NULL) {
        filepath[strcspn(filepath, "\n")] = 0;

        for (int i = 0; filepath[i] != '\0'; i++) {
            if (filepath[i] == '/') {
                filepath[i] = '\\';
            }
        }
    }

    strcpy(fullpath, prefix);
    strcat(fullpath, filepath);
    printf("Loading file: %s\n", fullpath);


    // ---------------------------------------------------------
    // PART 1 : LOADING & MARKOV
    // ---------------------------------------------------------
    PRINT_SECTION("PART 1: GRAPH LOADING & CHECKS");

    // 1. Reading of the graph
    PRINT_STEP("Reading graph from file...");
    adjacency_list G = readGraph(fullpath);

    // 2. Vérification if it's a Markov graph or not
    PRINT_STEP("Checking Markov property...");
    isMarkov(G);

    // 3. "Drawing" of the graph
    PRINT_STEP("Generating graph visualization file...");
    drawGraph(G);
    printf("-> File '../output/graph.txt' created.\n");


    // ---------------------------------------------------------
    // PART2 : TOPOLOGY (TARJAN & HASSE)
    // ---------------------------------------------------------
    PRINT_SECTION("PART 2: CONNECTED COMPONENTS & HASSE");

    // 1. Tarjan algorithm (Partition of class)
    PRINT_STEP("Running Tarjan's algorithm to find components...");
    t_partition *partition = tarjan(&G);
    displayPartition(partition);

    // 2. Création between classes (Hasse)
    PRINT_STEP("Building Hasse diagram structure...");
    t_link_array *links = initLinkArray(&G, partition);

    // 3. Generation of file Hasse for Mermaid
    PRINT_STEP("Generating Hasse diagram file...");
    textFileHasse(partition, links);
    printf("-> File 'textFileHasse.txt' created.\n");

    // 4. Analysis of properties (Transient vs Persistent)
    PRINT_STEP("Analyzing class characteristics (Transient/Persistent):");
    displayCharacteristics(partition, links);


    // ---------------------------------------------------------
    // PART 3 : MATRIX CALCULATIONS
    // ---------------------------------------------------------
    PRINT_SECTION("PART 3: MATRIX CALCULATIONS");

    // 1. Conversion Adjacency list -> Matrix
    PRINT_STEP("Converting Graph to Matrix M:");
    t_matrix M = adjMatrix(&G);
    printMatrix(M);

    // 2. Calcul de M^3 (Probabilités après 3 étapes)
    int steps = 3;
    printf("[Step] Calculating M^%d (Distribution after %d steps):\n", steps, steps);

    t_matrix M_pow = powerMatrix(M, steps);
    printMatrix(M_pow);


    PRINT_SECTION("END OF PROGRAM");


    return 0;
}