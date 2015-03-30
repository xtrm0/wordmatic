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
