#ifndef SOLVER_H
#define SOLVER_H
#include "trie.h"
#include "matrix.h"

typedef struct SOLVER_DATA {
  FILE * fout;
  trie * trie;
  matrix * mat;
  int k;
  int color[MATRIX_SIDE + 2][MATRIX_SIDE + 2];
  int path[MATRIX_SIDE*MATRIX_SIDE+3];
} solver_data;

solver_data * solver_init(trie_node * trie, matrix * mat, int k, FILE * fout);
void solver_restart(solver_data * s);
void solver_destroy(solver_data * s);

void variante1(trie_node * trie, matrix * mat, int k);
void variante2(trie_node * trie, matrix * mat, int k);
void variante3(trie_node * trie, matrix * mat);
void variante4(trie_node * trie, matrix * mat);
void variante5(trie_node * trie, matrix * mat, int k);
void variante6(trie_node * trie, matrix * mat, int k);







#endif
