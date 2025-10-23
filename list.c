#include <stdio.h>
#include <stdlib.h>
#include "list.h"

t_cell* createCell(int value) {
    t_cell *cell = malloc(sizeof(t_cell));
    cell->value = value;
    cell->next = NULL;
    return cell;
}

t_list createList() {
    t_list list;
    list.head = NULL;
    return list;
}

void addcell(t_list *list, t_cell *cell) {
  t_cell *newcell = createCell(cell->value);
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

void display_list(t_list *list) {
  t_cell *temp = list->head;
  while (temp != NULL) {
    printf("%d ", temp->value);
    temp = temp->next;
  }
  return;
}

adjacency_list create_empty_adjacency_list(int size) {
  adjacency_list * adjlist;
  adjlist->size = size;
  adjlist = malloc(sizeof(adjacency_list));
  for (int i = 0; i < size; i++) {
    adjlist->array[i] = createList();
  }
  return *adjlist;
}

void display_adjacency_list(adjacency_list adjlist) {
  for (int i = 0; i < adjlist.size; i++) {
    display_list(&adjlist.array[i]);
  }
  return;
}