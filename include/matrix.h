#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SIDE 4
#define MAX_CELL_CHARS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MATRIX {
  int val[MATRIX_SIDE][MATRIX_SIDE];
  char M[MATRIX_SIDE][MATRIX_SIDE][MAX_CELL_CHARS+1];
} matrix;

matrix * matrix_init();

void matrix_destroy(matrix * m);

void read_matrix(FILE * fin, matrix * mat, int * maxlenght, int * maxval);

#endif
