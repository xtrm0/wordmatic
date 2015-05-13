#include "../include/matrix.h"

matrix * matrix_init() {
  matrix * m = malloc(sizeof(matrix));
  memset(m, 0, sizeof(matrix));
  return m;
}

void matrix_destroy(matrix * m) {
  free(m);
}

void read_matrix(FILE * fin, matrix * mat, int * maxlenght, int * maxval) {
  int i, j;
  *maxlenght = 0;
  *maxval = 0;
  memset(mat, 0, sizeof(matrix));
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      fscanf(fin, "%s", mat->M[i][j]);
      *maxlenght += strlen(mat->M[i][j]);
    }
  }
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      fscanf(fin, "%d", &(mat->val[i][j]));
      *maxval += mat->val[i][j];
    }
  }
}
