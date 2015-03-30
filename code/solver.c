#include "../include/solver.h"
//NOTA no wc sao percorrido

void dfs_var1(solver_data * s, trie_iterator it, int i, int j, int depth) {
  int x, y;
  if (s->stop) return;
  
  for (x=i-1; x<=i+1; i++) {
    for (y=j-1; y<=j+1; j++) {
      if (s->color[x][y]) {
        s->color[x][y] = 0;
        dfs_var1(s, it, x, y, depth+1);
        s->color[x][y] = 1;        
      }
    }
  }

}

void variante1(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(fout, trie, mat, k);
  trie_iterator it;
  int i, j;
  for (i=1; i<=MATRIX_SIDE; i++) {
    for (j=i; j<=MATRIX_SIDE; j++) {
      if (s->stop) break;
      //TODO set iterator to this
      dfs_var1(s, it, i, j, 111111);
    }
  }
  
  solver_destroy(s);
}

solver_data * solver_init(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = malloc(sizeof(solver_data));
  TESTMEM(s);
  s->fout   = fout;
  s->trie   = trie;
  s->mat    = mat;
  s->k      = k;
  s->stop   = 0;
  solver_restart(s);
  return s;
}

void solver_restart(solver_data * s) {
  int i,j;
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
