#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"
#include "list.h"

t_tarjanVertex* initTarjanVertices(adjacency_list* adj) {
    t_tarjanVertex* vertices = malloc(adj->size * sizeof(t_tarjanVertex));
    for (int i = 0; i < adj->size; i++) {
        vertices[i].id = i + 1;
        vertices[i].index = -1;
        vertices[i].accessibleNumber = -1;
        vertices[i].onStack = 0;
    }
    return vertices;
}

void push(t_stack *stack, t_tarjanVertex* vertex) {
    stack->values[stack->nbValues] = vertex;
    stack->nbValues++;
}

t_tarjanVertex* pop(t_stack *stack) {
    stack->nbValues--;
    return stack->values[stack->nbValues];
}

void parcours(int v, adjacency_list *graph, t_tarjanVertex *vertices, t_stack *stack, int *index, t_partition *partition) {
    vertices[v].index = *index;
    vertices[v].accessibleNumber = *index;
    *index += 1;
    vertices[v].onStack = 1;

    push(stack,&vertices[v]);

    t_cell *curr = graph->array[v].head;
    while (curr != NULL) {
        int w = curr->end - 1;

        if (vertices[w].index == -1) {
            parcours(w, graph, vertices, stack, index, partition);
            if (vertices[w].accessibleNumber < vertices[v].accessibleNumber)
                vertices[v].accessibleNumber = vertices[w].accessibleNumber;
        }
        else if (vertices[w].onStack) {
            if (vertices[w].index < vertices[v].accessibleNumber)
                vertices[v].accessibleNumber = vertices[w].index;
        }

        curr = curr->next;
    }

    if (vertices[v].accessibleNumber == vertices[v].index) {
        t_class newClass;
        sprintf(newClass.name, "C%d", partition->nbClasses + 1);
        newClass.nbVertices = 0;

        t_tarjanVertex *w;
        do {
            w = pop(stack);
            w->onStack = 0;

            newClass.vertices[newClass.nbVertices++] = w;
        } while (w != &vertices[v]);

        partition->classes[partition->nbClasses++] = newClass;
    }
}


void displayPartition(t_partition *partition) {
    for (int i = 0; i < partition->nbClasses; i++) {
        printf("Component C%d: {", i+1);
        for (int j = 0; j < partition->classes[i].nbVertices-1; j++) {
            printf("%d,", partition->classes[i].vertices[j]->id);
        }
        printf("%d}\n", partition->classes[i].vertices[partition->classes[i].nbVertices-1]->id);
    }
}

t_partition *tarjan(adjacency_list *graph) {
    int index = 0;

    t_tarjanVertex *vertices = initTarjanVertices(graph);

    t_stack stack;
    stack.nbValues = 0;

    t_partition *partition = malloc(sizeof(t_partition));
    partition->nbClasses = 0;
    partition->classes = malloc(NBMAX * sizeof(t_class));

    for (int v = 0; v < graph->size; v++) {
        if (vertices[v].index == -1) {
            parcours(v, graph, vertices, &stack, &index, partition);
        }
    }

    return partition;
}

