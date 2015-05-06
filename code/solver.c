#include "../include/solver.h"


void dfs(solver_data * s, trie_iterator it, int i, int j, int len, int val) {
  int x,y;
  char *c;

  if (s->stop) return;
  if (s->color[i][j]==0) return;
  if (it_travel_s(&it, s->mat->M[i][j])) return;

  for (c=s->mat->M[i][j]; c; c++) {
    s->path[len] = *c;
    len++;
  }
  val += s->mat->val[i][j];

  if (s->prune && s->prune(s, len, val)) return;

  s->color[i][j]=0;


  if (it_isendnode(it))
    if(!(s->test_solution) || s->test_solution(s,len,val))
      s->add_solution(s,len,val);

  for (x=i-1; x<=i+1; i++)
    for (y=j-1; y<=j+1; j++)
      dfs(s, it, x, y, len, val);

  s->color[i][j]=1;
  return;
}

int _prune_size_gt_k(s, len, val) {
  if (s->k < val) return 1;
  return 0;
}

int _size_eq_k(s, len, val) {
  if (s->k == val) return 1;
  return 0;
}

int _solution_best(s, len, val) {
  /* TODO */
  return 0;
}
int _solution_single(s, len, val) {
  _solution_best(s,len,val);
  s->stop=1;
  return 0;
}
int _solution_all(s, len, val) {
  /* TODO */
  return 0;
}

int _prune5(s, len, val) {
  if (s->k < len) return 1;
  return 0;
}

int _prune6(s, len, val) {
  if (s->k < val) return 1; /* TODO: Ver se os inteiros da matriz sao todos positivos [PERGUNTAR AO PROF OU DESCOBRIR NO ENUCIADO]*/
  if (s->bestlen < len) return 1;
  return 0;
}

int _comp4(s, len, val) {
  if (s->bestlen < len) return 1;
  return 0;
}
int _comp5(s, len, val) {
  if (s->bestval < val && s->k == len) return 1;
  return 0;
}
int _comp6(s, len, val) {
  if (s->bestlen > len && s->k == val) return 1;
  return 0;
}

void dfs_caller(solver_data * s, trie_node * trie) {
  int i, j;
  trie_iterator it;
  for (i=1; i<=MATRIX_SIDE; i++) {
    for (j=1; j<=MATRIX_SIDE; j++) {
      if (s->stop) break;
      it = it_init(trie);
      dfs(s, it, i, j, 0, 0);
    }
  }
}

void variante1(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(fout, mat, k, _prune_size_eq_k, _size_eq_k, _solution_single);
  dfs_caller(s, trie);
  _print_solution_single(s);
  solver_destroy(s);
}
void variante2(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(fout, mat, k, _prune_size_gt_k, _size_eq_k, _solution_all);
  dfs_caller(s, trie);
  _print_solution_all(s);
  solver_destroy(s);
}
void variante3(FILE * fout, trie_node * trie, matrix * mat) {
  solver_data * s = solver_init(fout, mat, 0, NULL, NULL, _solution_all);
  dfs_caller(s, trie);
  _print_solution_all(s);
  solver_destroy(s);
}
void variante4(FILE * fout, trie_node * trie, matrix * mat) {
  solver_data * s = solver_init(fout, mat, 0, NULL, _comp4, _solution_best);
  dfs_caller(s, trie);
  _print_solution_single(s);
  solver_destroy(s);
}
void variante5(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(fout, mat, k, _prune_size_gt_k, _comp5, _solution_best);
  dfs_caller(s, trie);
  _print_solution_single(s);
  solver_destroy(s);
}
void variante6(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(fout, mat, k, _prune6, _comp6, _solution_best);
  dfs_caller(s, trie);
  _print_solution_single(s);
  solver_destroy(s);
}


solver_data * solver_init(FILE * fout, trie_node * trie, matrix * mat, int k, int (*prune)(struct SOLVER_DATA*, int, int), int (*test_solution)(struct SOLVER_DATA*, int, int), int (*add_solution)(struct SOLVER_DATA*, int, int)) {
  solver_data * s = malloc(sizeof(solver_data));
  TESTMEM(s);
  s->fout   = fout;
  s->trie   = trie;
  s->mat    = mat;
  s->k      = k;
  s->stop   = 0;
  s->prune = prune;
  s->test_solution = test_solution;
  s->add_solution = add_solution;
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
