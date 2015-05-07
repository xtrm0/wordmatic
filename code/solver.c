#include "../include/solver.h"


void dfs(solver_data * s, trie_iterator it, int i, int j, int len, int val, int depth) {
  int x,y;
  char *c;
  if (s->stop) return;
  printf("call: %d %d %s %d %d %d\n", i, j, s->mat->M[i-1][j-1], len, val, depth);

  if (it_travel_s(&it, s->mat->M[i-1][j-1])) return;
  for (c=s->mat->M[i-1][j-1]; *c; c++) {
    s->word[len] = *c;
    len++;
    s->word[len] = 0;
  }
  val += s->mat->val[i-1][j-1];
  printf("prep: %s\n", s->word);

  if (s->prune && s->prune(s, len, val)) return;
  printf("pass: %s\n", s->word);

  s->color[i][j]=0;
  s->path[2*depth] = '0'+i;
  s->path[2*depth+1] = '0'+j;
  s->path[2*depth]=0;


  if (it_isendnode(&it))
    if(!(s->test_solution) || s->test_solution(s,len,val))
      s->add_solution(s,len,val);

  for (x=i-1; x<=i+1; x++)
    for (y=j-1; y<=j+1; y++) {
        printf("%d %d\n", x, y);
        if (s->color[x][y])
          dfs(s, it, x, y, len, val, depth+1);
      }

  s->color[i][j]=1;

  return;
}

int _prune_size_gt_k(solver_data * s, int len, int val) {
  if (s->k < len) return 1;
  return 0;
}

int _size_eq_k(solver_data* s, int len, int val) {
  if (s->k == len) return 1;
  return 0;
}

int _solution_best(solver_data* s, int len, int val) {
  queue_pop(s->sol);
  s->bestlen = len;
  s->bestval = val;
  queue_push (s->sol, s->word, s->path, len, val);
  return 0;
}
int _solution_single(solver_data* s, int len, int val) {
  _solution_best(s,len,val);
  s->stop=1;
  return 0;
}
int _solution_all(solver_data* s, int len, int val) {
  s->bestlen += len;
  queue_push (s->sol, s->word, s->path, len, val);
  /*Para poupar memoria e tempo podemos por aqui uma avl*/
  s->bestval += val;
  return 0;
}

void _print_solution_single_len(FILE * fout, solver_data * s) {
  list_val * ans;
  char * aux;
  if (queue_empty(s->sol)) {
    return;
  }
  ans = queue_front(s->sol);
  ans->word[ans->len]=0;
  fprintf(fout, "%s ", ans->word);
  aux = s->path;
  while (*aux) {
    fprintf(fout, "%c%c ", *aux, *(aux+1));
    aux+=2;
  }
  fprintf(fout, "%d\n", ans->len);
  queue_pop(s->sol);
}

void _print_solution_single_val(FILE * fout, solver_data * s) {
  list_val * ans;
  char * aux;
  if (queue_empty(s->sol)) {
    return;
  }
  ans = queue_front(s->sol);
  fprintf(fout, "%s ", ans->word);
  aux = s->path;
  while (*aux) {
    fprintf(fout, "%c%c ", *aux, *(aux+1));
    aux+=2;
  }
  fprintf(fout, "%d\n", ans->val);
  queue_pop(s->sol);
}

void _print_solution_all_len(FILE * fout, solver_data * s) {
  queue_sort_uniq(s->sol);
  while(!queue_empty(s->sol)) {
    _print_solution_single_len(fout,s);
  }
}

int _prune5(solver_data* s, int len, int val) {
  if (s->k < len) return 1;
  return 0;
}

int _prune6(solver_data* s, int len, int val) {
  if (s->k < val) return 1; /* TODO: Ver se os inteiros da matriz sao todos positivos [PERGUNTAR AO PROF OU DESCOBRIR NO ENUCIADO]*/
  if (s->bestlen < len) return 1;
  return 0;
}

int _comp4(solver_data* s, int len, int val) {
  if (s->bestlen < len) return 1;
  return 0;
}
int _comp5(solver_data* s, int len, int val) {
  if (s->bestval < val && s->k == len) return 1;
  return 0;
}
int _comp6(solver_data* s, int len, int val) {
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
      printf("dfsc: %d %d\n", i, j);
      dfs(s, it, i, j, 0, 0, 0);
    }
  }
}

void variante1(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(mat, k, _prune_size_gt_k, _size_eq_k, _solution_single);
  dfs_caller(s, trie);
  _print_solution_single_len(fout, s);
  fprintf(fout, "%d\n\n", s->bestlen);
  solver_destroy(s);
}
void variante2(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(mat, k, _prune_size_gt_k, _size_eq_k, _solution_all);
  dfs_caller(s, trie);
  _print_solution_all_len(fout, s);
  fprintf(fout, "%d\n\n", s->bestlen);
  solver_destroy(s);
}
void variante3(FILE * fout, trie_node * trie, matrix * mat) {
  solver_data * s = solver_init(mat, 0, NULL, NULL, _solution_all);
  dfs_caller(s, trie);
  _print_solution_all_len(fout, s);
  fprintf(fout, "%d\n\n", s->bestlen);
  solver_destroy(s);
}
void variante4(FILE * fout, trie_node * trie, matrix * mat) {
  solver_data * s = solver_init(mat, 0, NULL, _comp4, _solution_best);
  dfs_caller(s, trie);
  _print_solution_single_len(fout, s);
  fprintf(fout, "%d\n\n", s->bestlen);
  solver_destroy(s);
}
void variante5(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(mat, k, _prune_size_gt_k, _comp5, _solution_best);
  dfs_caller(s, trie);
  _print_solution_single_val(fout, s);
  fprintf(fout, "%d\n\n", s->bestval);
  solver_destroy(s);
}
void variante6(FILE * fout, trie_node * trie, matrix * mat, int k) {
  solver_data * s = solver_init(mat, k, _prune6, _comp6, _solution_best);
  s->bestlen=INT_MAX;
  dfs_caller(s, trie);
  _print_solution_single_val(fout, s);
  fprintf(fout, "%d\n\n", s->bestval);
  solver_destroy(s);
}


solver_data * solver_init(matrix * mat, int k, int (*prune)(struct SOLVER_DATA*, int, int), int (*test_solution)(struct SOLVER_DATA*, int, int), int (*add_solution)(struct SOLVER_DATA*, int, int)) {
  solver_data * s = malloc(sizeof(solver_data));
  TESTMEM(s);
  memset(s,0,sizeof(solver_data));
  s->mat    = mat;
  s->k      = k;
  s->prune  = prune;
  s->sol    = queue_init();
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
  queue_destroy(s->sol);
  free(s);
}
