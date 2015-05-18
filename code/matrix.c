/******************************************************************************
 * File Name:   matrix.c
 * Author:      Afonso / Osvaldo
 * Revision:
 * NAME:        WordMatic - IST/AED - 2015 2º Sem
 * SYNOPSIS:    #include "input_man.h"
 * DESCRIPTION: .
 * DIAGNOSTICS: tested
 *****************************************************************************/
#include "../include/matrix.h"


matrix * matrix_init() {

  matrix * m = malloc(sizeof(matrix));
  memset(m, 0, sizeof(matrix));
  return m;
}

/******************************************************************************
 * read_matrix()
 *
 * Arguments:   fin
 *              mat
 *              maxlenght
 *              maxval
 * Returns:     apontador para a matriz
 * Side-Effects: nope
 * Description:  Reads a matrix from the file fin to mat.
 *              Sets *maxlenght = sum of the number of characters in the matrix
 *              Sets *maxval    = sum of values in the matrix
 *****************************************************************************/
void read_matrix(FILE * fin, matrix * mat, int * maxlenght, int * maxval) {
  int i, j;

  *maxlenght = 0;
  *maxval = 0;
  memset(mat, 0, sizeof(matrix));
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      assert_read(fscanf(fin, "%s", mat->M[i][j]));
      *maxlenght += strlen(mat->M[i][j]);
    }
  }
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      assert_read(fscanf(fin, "%d", &(mat->val[i][j])));
      *maxval += mat->val[i][j];
    }
  }
}

/******************************************************************************
 * matrix_destroy()
 *
 * Arguments:   matriz a destruir
 * Returns:     void
 * Side-Effects: nope
 * Description:  Destroys a matrix pointer previously returned by matrix_init()
 *****************************************************************************/
void matrix_destroy(matrix * m) {
  free(m);
}
