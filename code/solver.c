#include "../include/solver.h"

void variante1(trie_node * trie, matrix * mat, int k, FILE * fout) {
  solver_data data = solver_init(trie, mat, k, fout);
  
}


solver_data * solver_init(trie_node * trie, matrix * mat, int k, FILE * fout) {
  solver_data * s = malloc(sizeof(solver_data));
  s->fout = fout;
  s->trie = trie;
  s->mat  = mat;
  s->k    = k;
  solver_restart(s);
  return s;
}

void solver_restart(solver_data * s) {
  memset(s->color, 0, sizeof(s->color));
  for (i=1; i<=MATRIX_SIDE; i++) {
    for (j=1; j<=MATRIX_SIDE; j++) {
      s->color[i][j]=1;
    }
  }
  memset(s->path, 0, sizeof(s->path));
}

void solver_destroy(solver_data * s) {
  free(s);
}
