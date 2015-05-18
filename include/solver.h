/******************************************************************************
 * File Name: solver.h
 * Author:    Afonso / Osvaldo
 * Revision:
 * NAME
 *     matrix - prototypes
 * SYNOPSIS
 *      #include "trie.h"
 *      #include "matrix.h"
 *      #include "stl.h"
 * DIAGNOSTICS
 *          OK
 *****************************************************************************/
#ifndef SOLVER_H
#define SOLVER_H

#include "trie.h"
#include "matrix.h"
#include "stl.h"

/*
  Este solver_data tem coisas que normalmente se definiriam como variaveis globais static,
  mas vamos deixar assim caso se queira paralelizar os diferentes teste de caso
  do ficheiro. [Não implementado nem testado]
*/

typedef struct SOLVER_DATA {
  matrix * mat;
  int k;
  int color[MATRIX_SIDE + 2][MATRIX_SIDE + 2];
  char path[MATRIX_SIDE*MATRIX_SIDE*2+8];
  char word[MATRIX_SIDE*MATRIX_SIDE+4];
  int stop;
  int bestlen, bestval;
  /* Não vamos usar unions para simplificar o código:*/
  avl_node * sol;
  /*Tenta reduzir o espaco de procura, com base nas restricoes do problema */
  int (*prune)(struct SOLVER_DATA*, int, int);
  /*  Testa se se deve adicionar//substituir a solucao  */
  int (*test_solution)(struct SOLVER_DATA*, int, int);
  /*     Adiciona / substitui a solucao   */
  int (*add_solution)(struct SOLVER_DATA*, int, int);
} solver_data;

/*  Initializes a new solver*/
solver_data * solver_init(matrix * mat, int k, int (*prune)(struct SOLVER_DATA*, int, int), int (*test_solution)(struct SOLVER_DATA*, int, int), int (*add_solution)(struct SOLVER_DATA*, int, int));
/*  Resets a solver state to allow for a new dfs (keeps the old solutions)*/
void solver_restart(solver_data * s);
/*  Frees a solver and all of its solutions*/
void solver_destroy(solver_data * s);

/*  Performs a dfs on the matrix with the settings previously set on 
 * solver_init to s.
 *  This dfs has a prunning function, a testing function and an adding function 
 * depending on the game mode*/
void dfs(solver_data * s, trie_iterator it, int i, int j, int len, int val, int depth);
/*  This function calls the dfs for every cell on the game matrix*/
void dfs_caller(solver_data * s, trie_node * trie);

/*All of the varianteX functions works in the following way, depending on the game mode(X):
    1 - set the solver according to the game mode
    2 - call dfs_caller with the solver
    3 - prints solution(s) according the game mode*/
void variante1(FILE * fout, trie_node * trie, matrix * mat, int k);
void variante2(FILE * fout, trie_node * trie, matrix * mat, int k);
void variante3(FILE * fout, trie_node * trie, matrix * mat);
void variante4(FILE * fout, trie_node * trie, matrix * mat);
void variante5(FILE * fout, trie_node * trie, matrix * mat, int k);
void variante6(FILE * fout, trie_node * trie, matrix * mat, int k);

#endif
