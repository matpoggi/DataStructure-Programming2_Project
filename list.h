#include <stdio.h>
#include <stdlib.h>


struct s_cell {
    int value;
    struct s_cell *next;
};
typedef struct s_cell t_cell;

typedef struct {
    t_cell *head;
} t_list;

typedef struct {
    int size;
    t_list *array;
}adjacency_list;

t_cell* createEmptyCell(int value);
t_list createEmptyList();
void addCell(t_list *list, t_cell *cell);
void displayList(t_list *list);
adjacency_list createEmptyAdjacencyList(int size);
void displayAdjacencyList(adjacency_list adjlist);