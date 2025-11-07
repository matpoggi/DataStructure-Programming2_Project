#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "utils.c"

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

t_list createEmptyList() {
    t_list list;
    list.head = NULL;
    return list;
}

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

void displayList(t_list *list) {
    t_cell *temp = list->head;
    while (temp != NULL) {
        printf("-> (%d, %.2f) ", temp->end, temp->proba);
        temp = temp->next;
    }
    printf("\n");
}

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

void displayAdjacencyList(adjacency_list adjlist) {
    printf("\n[AdjaListDisp] Adjacency List:\n");
    for (int i = 0; i < adjlist.size; i++) {
        printf("[AdjaListDisp] Vertex %d ", i + 1);
        displayList(&adjlist.array[i]);
    }
}

adjacency_list readGraph(const char *filename) {
    printf("\n---------------------------------------\n[readGraph---] Opening file: %s\n", filename);

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
    printf("[readGraph---] Number of vertices: %d\n", nbvert);

    adjacency_list adjlist = createEmptyAdjacencyList(nbvert);
    printf("[readGraph---] Adjacency list created (size=%d)\n", adjlist.size);

    int start, end;
    float proba;
    int line = 0;
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3) {
        line++;

        if (start < 1 || start > adjlist.size) {
            printf("[ERROR] Start index %d out of bounds!\n", start);
            break;
        }

        addCell(&adjlist.array[start - 1], end, proba);

    }
    for (int i = 0; i < adjlist.size; i++) {
        adjlist.array[i] = *sortList(adjlist.array[i]);
    }
    fclose(file);
    printf("[readGraph---] Done reading file.\n---------------------------------------");
    displayAdjacencyList(adjlist);
    printf("---------------------------------------\n[readGraph---] Graph loaded successfully.\n---------------------------------------\n\n");
    return adjlist;
}

void isMarkov (adjacency_list adjlist) {
    int truemarkov = 1;
    for (int i = 0; i < adjlist.size; i++) {
        printf("[markov------] Vertex %d :\n", i + 1);
        printf("[markov------] -- Checking the sum of the probabilities%d\n", i + 1);
        float proba = 0.0;
        t_cell *curr = adjlist.array[i].head;
        while (curr != NULL) {
            proba += curr->proba;
            curr = curr->next;
        }
        if (proba <0.99 || proba > 1.00) {
            truemarkov = 0;
            printf("[markov------] -- Sum of probability = %.2f \n", proba);
            printf ("---------------------------------------\n");
            break;
        }
        printf("[markov------] -- Sum of probability = 1\n");
    }
    if (truemarkov == 1) {
        printf ("---------------------------------------\n[markov------] The graph is a Markov graph\n---------------------------------------\n\n");
    }else{
        printf ("[markov------] The graph is not a Markov graph\n---------------------------------------\n\n");
    }
}

void drawGraph(adjacency_list adjlist) {

    FILE *file = fopen("../output/graph.txt", "w");
    if (file == NULL) {
        perror("[drawGraph---] Could not open file for writing");
    }
    printf("[drawGraph---] Writing the config...\n");
    fprintf(file, "--- \nconfig: \n   layout: elk \n   theme: neo \n   look: neo \n---\n\nflowchart LR");

    for (int i = 0; i < adjlist.size; i++) {
        int vertex_index = i + 1;
        char * vertex_letter;
        vertex_letter = getID(vertex_index);
        fprintf(file,"\n%s((%d))",vertex_letter, vertex_index);
    }

    printf("[drawGraph---] Edge creation : Done\n");

    fprintf(file,"\n\n");

    for (int vertex_index = 1; vertex_index <= adjlist.size; vertex_index++) {

        t_list *edge_list = &adjlist.array[vertex_index - 1];
        t_cell *edge_curr = edge_list->head;
        while (edge_curr != NULL) {

            char * vertex_letter = getID(vertex_index);
            fprintf(file,"%s -->|",vertex_letter);

            char * edge_letter = getID(edge_curr->end);
            fprintf(file,"%.2f|%s\n", edge_curr->proba, edge_letter);

            edge_curr = edge_curr->next;

        }
        printf("[drawGraph---] Vertex %d : Done\n",vertex_index);
    }
    printf("---------------------------------------\n[drawGraph---] Graph draw file create successfully.\n---------------------------------------\n\n");
}

void removeCell(t_cell *cell, t_list *list) {
    if (list->head == NULL || cell == NULL) return;

    if (cell == list->head) {
        list->head = list->head->next;
        return;
    }

    t_cell *prev_cell = list->head;
    t_cell *current_cell = list->head->next;

    while (current_cell != NULL && current_cell != cell) {
        prev_cell = current_cell;
        current_cell = current_cell->next;
    }

    if (current_cell == cell) {
        prev_cell->next = current_cell->next;
    }
}

t_list *sortList(t_list list) {

    t_list *sorted_list = malloc(sizeof(t_list));
    if (sorted_list == NULL) {
        return NULL;
    }

    *sorted_list = createEmptyList();

    while (list.head != NULL) {
        t_cell *lowest_cell = list.head;
        t_cell *current_cell = list.head;

        while (current_cell != NULL) {
            if (current_cell->proba < lowest_cell->proba) {
                lowest_cell = current_cell;
            }
            current_cell = current_cell->next;
        }

        addCell(sorted_list, lowest_cell->end, lowest_cell->proba);
        removeCell(lowest_cell, &list);
    }

    return sorted_list;
}
