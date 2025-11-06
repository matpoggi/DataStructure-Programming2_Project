#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// CREATE A CELL (EDGE)
t_cell* createCell(int end, float proba) {
    t_cell *cell = malloc(sizeof(t_cell));
    if (!cell) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    cell->end = end;
    cell->proba = proba;
    cell->next = NULL;
    return cell;
}

// CREATE EMPTY LIST
t_list createEmptyList() {
    t_list list;
    list.head = NULL;
    return list;
}

// ADD AN EDGE TO A LIST
void addCell(t_list *list, int end, float proba) {
    t_cell *newcell = createCell(end, proba);

    if (list->head == NULL) {
        list->head = newcell;
    } else {
        t_cell *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newcell;
    }
}

// DISPLAY A SINGLE LIST
void displayList(t_list *list) {
    t_cell *temp = list->head;
    while (temp != NULL) {
        printf("-> (%d, %.2f) ", temp->end, temp->proba);
        temp = temp->next;
    }
    printf("\n");
}

// CREATE EMPTY ADJACENCY LIST
adjacency_list createEmptyAdjacencyList(int size) {
    adjacency_list adjlist;
    adjlist.size = size;
    adjlist.array = malloc(size * sizeof(t_list));
    if (adjlist.array == NULL) {
        perror("Failed to allocate adjacency list");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        adjlist.array[i] = createEmptyList();
    }

    return adjlist;
}

// DISPLAY THE ENTIRE ADJACENCY LIST
void displayAdjacencyList(adjacency_list adjlist) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < adjlist.size; i++) {
        printf("Vertex %d ", i + 1);
        displayList(&adjlist.array[i]);
    }
}

// READ GRAPH FROM FILE
adjacency_list readGraph(const char *filename) {
    printf("[readGraph] Opening file: %s\n", filename);

    FILE *file = fopen(filename, "rt");
    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    int nbvert;
    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    printf("[readGraph] Number of vertices: %d\n", nbvert);

    adjacency_list adjlist = createEmptyAdjacencyList(nbvert);
    printf("[readGraph] Adjacency list created (size=%d)\n", adjlist.size);

    int start, end;
    float proba;
    int line = 0;
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3) {
        line++;
        printf("[readGraph] Line %d: %d -> %d (%.2f)\n", line, start, end, proba);

        if (start < 1 || start > adjlist.size) {
            printf("[ERROR] Start index %d out of bounds!\n", start);
            break;
        }

        addCell(&adjlist.array[start - 1], end, proba);
    }

    fclose(file);
    printf("[readGraph] Done reading file.\n");

    displayAdjacencyList(adjlist);
    return adjlist;
}

// CHECK IF THE GRAPH IS A MARKOV GRAPH
int ismarkov (adjacency_list adjlist) {
    int truemarkov = 1;
    for (int i = 0; i < adjlist.size; i++) {
        float proba = 0.0;
        t_cell *curr = adjlist.array[i].head;
        while (curr != NULL) {
            proba += curr->proba;
            curr = curr->next;
        }
        if (proba <0.99 || proba > 1.00) {
            truemarkov = 0;
            printf ("the sum of the probability of the vertex %d is %.2f \n", i+1, proba);
        }
    }
    if (truemarkov == 1) {
        printf ("The graph is a Markov graph\n");
    }else{
        printf ("The graph is not a Markov graph\n");
    }
    return truemarkov;
}
