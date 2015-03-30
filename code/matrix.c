#include "../include/matrix.h"

matrix * matrix_init() {
  matrix * m = malloc(sizeof(matrix));
  memset(m, 0, sizeof(matrix));
  m->R = MATRIX_SIDE;
  m->C = MATRIX_SIDE;
  return m;
}

void matrix_destroy(matrix * m) {
  free(m);
}

int read_matrix(FILE * fin, matrix * mat) {
  int i, j, read_chars;
  read_chars = 0;
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      fscanf(fin, "%s", mat->M[i][j].val);
      switch(mat->M[i][j].val[1]) {
      case '\0':
        mat->M[i][j].type = 0;
        read_chars++;
        break;
      case '\\':
        mat->M[i][j].type = 1;
        read_chars++;
        break;
      default:
        mat->M[i][j].type = 2;
        read_chars += strlen(mat->M[i][j].val);
        break;
      }
    }
  }
  
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      fscanf(fin, "%d", &(mat->val[i][j]));
    }
  }

  return read_chars;
}
