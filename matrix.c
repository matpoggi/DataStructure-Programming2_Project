#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#include "matrix.h"

t_matrix newMatrix(int row, int col) {
    t_matrix matrix;
    matrix.row = row;
    matrix.col = col;

    matrix.value = (double **)malloc(row * sizeof(double *));
    if (matrix.value == NULL) {
        perror("Allocation error in newMatrix (rows)");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrix.row; i++) {
        matrix.value[i] = (double *)malloc(col * sizeof(double));
        if (matrix.value[i] == NULL) {
            perror("Allocation error in newMatrix (cols)");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

t_matrix zeroMatrix(int row, int col) {
    t_matrix matrix = newMatrix(row, col);

    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.col; j++) {
            matrix.value[i][j] = 0.0;
        }
    }
    return matrix;
}

t_matrix adjMatrix(adjacency_list *adjlist) {
    int n = adjlist->size;

    t_matrix adjmatrix = zeroMatrix(n, n);

    for (int i = 0; i < n; i++) {
        t_cell *curr = adjlist->array[i].head;
        while (curr != NULL) {
            int j = curr->end - 1;
            if (j >= 0 && j < n) {
                adjmatrix.value[i][j] = curr->proba;
            }

            curr = curr->next;
        }
    }
    return adjmatrix;
}

t_matrix copyMatrix(t_matrix *matrix) {
    t_matrix c = newMatrix(matrix->row, matrix->col);
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            c.value[i][j] = matrix->value[i][j];
        }
    }
    return c;
}

t_matrix multiplyMatrix(t_matrix *matrix1, t_matrix *matrix2) {
    if (matrix1->col != matrix2->row) {
        printf("Error: Matrix dimensions incompatible for multiplication\n");
        t_matrix empty = {0, 0, NULL};
        return empty;
    }

    t_matrix m = newMatrix(matrix1->row, matrix2->col);

    for (int i = 0; i < matrix1->row; i++) {
        for (int j = 0; j < matrix2->col; j++) {
            double sum = 0.0;
            for (int k = 0; k < matrix1->col; k++) {
                sum += matrix1->value[i][k] * matrix2->value[k][j];
            }
            m.value[i][j] = sum;
        }
    }
    return m;
}

double diffmatrix(t_matrix *M, t_matrix *N) {
    if (M->row != N->row || M->col != N->col) {
        printf("Error: Matrix dimensions incompatible for diff\n");
        return -1.0;
    }

    double sum = 0.0;
    for (int i = 0; i < M->row; i++) {
        for (int j = 0; j < M->col; j++) {
            sum += fabs(M->value[i][j] - N->value[i][j]);
        }
    }
    return sum;
}

void printMatrix(t_matrix M) {
    for (int i = 0; i < M.row; i++) {
        printf("| ");
        for (int j = 0; j < M.col; j++) {
            printf("%5.2f ", M.value[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

t_matrix powerMatrix(t_matrix M, int p) {
    if (p == 1) return copyMatrix(&M);

    t_matrix res = copyMatrix(&M);
    t_matrix temp;

    for (int i = 1; i < p; i++) {
        temp = multiplyMatrix(&res, &M);
        res = temp;
    }
    return res;
}