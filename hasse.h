#ifndef __HASSE_H__
#define __HASSE_H__

typedef struct {
    int id;
    int nb;
    int accessnb;
    int boolindic;
}t_tarjan_vertex;

typedef struct {
    int from;
    int to;
} t_link;

typedef struct {
    t_link *links;
    int log_size;
    int capacity;
} t_link_array;


void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif