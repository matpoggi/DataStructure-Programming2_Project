#ifndef __HASSE_H__
#define __HASSE_H__

#include "tarjan.h"
#include "list.h"
typedef struct s_link {
    t_class *from;
    t_class *to;
} t_link;

typedef struct s_link_array {
    t_link *links;
    int log_size;
} t_link_array;

t_link_array *initLinkArray(adjacency_list *graph, t_partition *partition);
void textFileHasse(t_partition *partition, t_link_array *linkArray);
void removeTransitiveLinks(t_link_array *p_link_array);
void displayCharacteristics(t_partition *partition, t_link_array *linkArray);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif