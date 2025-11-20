#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "matrix.h"
#include "math.h"

t_matrix newMatrix(int row, int col){
  t_matrix matrix;
  matrix.row = row;
  matrix.col = col;
  matrix.value = malloc(row*sizeof(double));
  for (int i = 0; i < matrix.row; i++) {
    matrix.value[i] = malloc(col * sizeof(double));
  }
  return matrix;
}


t_matrix zeroMatrix(int row, int col){
  t_matrix matrix;
  matrix.row = row;
  matrix.col = col;
  for (int i = 0; i < matrix.row; i++) {
    for (int j = 0; j < matrix.col; j++) {
      matrix.value[i][j] = 0.0;
    }
  }
  return matrix;
}

t_matrix adjMatrix(adjacency_list *adjlist) {
  int n = adjlist->size;
  t_matrix adjmatrix = newMatrix(n,n);
  adjmatrix = zeroMatrix(n,n);
  for (int i = 0; i < n; i++) {
    t_cell *curr = adjlist->array[i].head;
    while (curr->next != NULL) {
      int j = curr->end;
      adjmatrix.value[i][j]= curr->proba;
      curr = curr->next;
    }
  }
  return adjmatrix;
}

t_matrix copyMatrix(t_matrix *matrix){
  t_matrix c = newMatrix(matrix->row, matrix->col);
  for (int i = 0; i < matrix->row; i++) {
    for (int j = 0; j < matrix->col; j++) {
      c.value[i][j] = matrix->value[i][j];
    }
  }
  return c;
}

t_matrix multiplyMatrix(t_matrix *matrix1, t_matrix *matrix2){
  t_matrix m = newMatrix(matrix1->row, matrix2->col);
  if (matrix1->row != matrix2-> col){
    return m = newMatrix(0,0);
  }
  for (int i = 0; i < matrix1->row; i++) {
    for (int j = 0; j < matrix2->col; j++) {
      m.value[i][j] = 0;
      for (int k = 0; k < matrix1->col; k++) {
        m.value[i][j] += matrix1->value[i][k] * matrix2->value[k][j];
      }
    }
  }
  return m;
}

double diffmatrix(t_matrix *M, t_matrix *N){
  double sum = 0.0;
  if (M->row != N->row || M->col != N->col){
    printf("matrix incompatible\n");
    return -0.01;
  }
  for (int i = 0; i < M->row; i++) {
    for (int j = 0; j < M->col; j++) {
      sum = sum + fabs(M->value[i][j] - N->value[i][j]);
    }
  }
  return sum;
}