#ifndef __HASSE_H__
#define __HASSE_H__

typedef struct s_tarjan_vertex{
    int id;
    int nb;
    int accessnb;
    int boolindic;
    struct s_tarjan_vertex *next;
    // struct s_tarjan_vertex *prev;
}t_tarjan_vertex;

typedef struct {
    int from;
    int to;
} t_link;

typedef struct {
    t_link *links;
    int log_size;
    int capacity;
    struct s_tarjan_vertex *head;
} t_link_array;

typedef struct {
    char name[100];
    int number;
    int *container;
}t_classes;

typedef struct {
    t_classes *classes;
    int size;
}t_partition;

void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif