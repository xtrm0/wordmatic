#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SIDE 4
#define MAX_CELL_CHARS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

typedef struct MATRIX {
  int val[MATRIX_SIDE][MATRIX_SIDE];
  char M[MATRIX_SIDE][MATRIX_SIDE][MAX_CELL_CHARS+1];
} matrix;

/*
  Allocates and initializes a pointer to a new matrix
*/
matrix * matrix_init();

/*
  Destroys a matrix pointer previously returned by matrix_init()
*/
void matrix_destroy(matrix * m);

/*
  Reads a matrix from the file fin to mat.
  Sets *maxlenght = sum of the number of characters in the matrix
  Sets *maxval    = sum of values in the matrix
*/
void read_matrix(FILE * fin, matrix * mat, int * maxlenght, int * maxval);

#endif
