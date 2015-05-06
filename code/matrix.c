#include "../include/matrix.h"

matrix * matrix_init() {
  matrix * m = malloc(sizeof(matrix));
  memset(m, 0, sizeof(matrix));
  return m;
}

void matrix_destroy(matrix * m) {
  free(m);
}

int read_matrix(FILE * fin, matrix * mat) {
  int i, j, read_chars;
  read_chars = 0;
  memset(matrix, 0, sizeof(matrix));
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      fscanf(fin, "%s", mat->M[i][j]);
      read_chars += strlen(mat->M[i][j]);
    }
  }

  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      fscanf(fin, "%d", &(mat->val[i][j]));
    }
  }
  return read_chars;
}
