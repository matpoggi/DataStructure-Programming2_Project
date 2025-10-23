#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// CREATE EMPTY CELL //
t_cell* createEmptyCell(int value) {
    t_cell *cell = malloc(sizeof(t_cell));
    cell->value = value;
    cell->next = NULL;
    return cell;
}

// CREATE EMPTY LIST //
t_list createEmptyList() {
    t_list list;
    list.head = NULL;
    return list;
}

// ADD A GIVEN CELL TO A GIVEN LIST //
void addCell(t_list *list, t_cell *cell) {
  t_cell *newcell = createEmptyCell(cell->value);
  if (list->head == NULL) {
    list->head = newcell;
  }
  else {
    t_cell *temp = list->head;
    while (temp->next != NULL) {
      temp->next = newcell;
    }
  }
  return;
}

// DISPLAY A GIVEN LIST //
void displayList(t_list *list) {
  t_cell *temp = list->head;
  while (temp != NULL) {
    printf("%d ", temp->value);
    temp = temp->next;
  }
  return;
}

//
adjacency_list createEmptyAdjacencyList(int size) {
  adjacency_list * adjlist;
  adjlist->size = size;
  adjlist = malloc(sizeof(adjacency_list));
  for (int i = 0; i < size; i++) {
    adjlist->array[i] = createEmptyList();
  }
  return *adjlist;
}

void displayAdjacencyList(adjacency_list adjlist) {
  for (int i = 0; i < adjlist.size; i++) {
    displayList(&adjlist.array[i]);
  }
  return;
}