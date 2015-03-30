#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SIDE 4
#include <stdlib.h>
#include <string.h>

typedef struct MATRIX_CELL {
  int type;
  char val[4];
} cell;
typedef struct MATRIX {
  int R, C;
  int val[MATRIX_SIDE][MATRIX_SIDE];
  cell M[MATRIX_SIDE][MATRIX_SIDE];
} matrix;

matrix * matrix_init();

void matrix_destroy(matrix * m);

#endif
