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

typedef struct adjacency_list {
    int size;
    t_list *array;
};
