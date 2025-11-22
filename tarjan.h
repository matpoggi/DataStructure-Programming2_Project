#ifndef TARJAN_H
#define TARJAN_H
#define NBMAX 50
#include "list.h"

typedef struct s_tarjanVertex {
    int id;
    int index;
    int accessibleNumber;
    int onStack;
} t_tarjanVertex;

typedef struct s_class {
    char name[10];
    t_tarjanVertex *vertices[NBMAX];
    int nbVertices;
} t_class;

typedef struct s_partition {
    t_class *classes;
    int nbClasses;
} t_partition;

typedef struct s_stack {
    t_tarjanVertex *values[NBMAX];
    int nbValues;
} t_stack;

t_tarjanVertex* initTarjanVertices(adjacency_list*);
void push(t_stack *stack, t_tarjanVertex* vertex);
t_tarjanVertex* pop(t_stack *stack);
void parcours(int v, adjacency_list *graph, t_tarjanVertex *vertices, t_stack *stack, int *indexPtr, t_partition *partition);
t_partition *tarjan(adjacency_list *graph);
void displayPartition(t_partition *partition);

#endif //TARJAN_H
