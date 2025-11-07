#ifndef LIST_H
#define LIST_H

typedef struct s_cell {
    int end;            // destination vertex
    float proba;        // probability
    struct s_cell *next;
} t_cell;

typedef struct {
    t_cell *head;
} t_list;

typedef struct {
    int size;       // number of vertices
    t_list *array;  // array of adjacency lists
} adjacency_list;

// Function declarations
t_cell* createCell(int end, float proba);
t_list createEmptyList();
void addCell(t_list *list, int end, float proba);
void displayList(t_list *list);
adjacency_list createEmptyAdjacencyList(int size);
void displayAdjacencyList(adjacency_list adjlist);
adjacency_list readGraph(const char *filename);
void isMarkov (adjacency_list adjlist);
void drawGraph(adjacency_list adjlist);
void removeCell(t_cell *cell, t_list *list);
t_list *sortList(t_list list);

#endif
