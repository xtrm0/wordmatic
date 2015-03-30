#ifndef SOLVER_H
#define SOLVER_H
#include "trie.h"
#include "matrix.h"

/*
  Este solver data tem coisas que normalmente se definiriam como variavel global static
  
*/
typedef struct SOLVER_DATA {
  FILE * fout;
  trie_node * trie;
  matrix * mat;
  int k;
  int color[MATRIX_SIDE + 2][MATRIX_SIDE + 2];
  int path[MATRIX_SIDE*MATRIX_SIDE+3];
  int stop;
} solver_data;

solver_data * solver_init(FILE * fout, trie_node * trie, matrix * mat, int k);
void solver_restart(solver_data * s);
void solver_destroy(solver_data * s);

void variante1(FILE * fout, trie_node * trie, matrix * mat, int k);
void variante2(FILE * fout, trie_node * trie, matrix * mat, int k);
void variante3(FILE * fout, trie_node * trie, matrix * mat);
void variante4(FILE * fout, trie_node * trie, matrix * mat);
void variante5(FILE * fout, trie_node * trie, matrix * mat, int k);
void variante6(FILE * fout, trie_node * trie, matrix * mat, int k);







#endif
