#include <stdlib.h>

typedef struct {
  int row;
  int col;
  double **value;
}t_matrix;

t_matrix newMatrix(int row, int col);
t_matrix zeroMatrix(int row, int col);
t_matrix adjMatrix(adjacency_list *adjlist);
t_matrix copyMatrix(t_matrix *matrix);
t_matrix multiplyMatrix(t_matrix *matrix1, t_matrix *matrix2);

