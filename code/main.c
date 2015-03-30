#include <stdio.h>
#include "../include/trie.h"
#include "../include/matrix.h"
#include "../include/input_man.h"
#include "../include/solver.h"

void usage_print(int err) {
  printf(
         "Usage: \n"
         "wordmatic <dictionary>.dic <puzzle>.puz\n"
         );
  exit(err);
}

void wordmatic_solver(char * filename, trie_node * trie) {
  FILE * fin;
  FILE * fout;
  matrix * mat;
  int N;
  int variante, k;
  int i,j;

  fin = fopen(filename, "r");
  if (fin == NULL) {
    printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);
    exit(ENOENT);
  }

  fscanf(fin, "%d", &N);
  while (N--) {
    mat = matrix_init();
    fscanf(fin, "%d %d", &variante, &k);
    for (i=0; i<MATRIX_SIDE; i++) {
      for (j=0; j<MATRIX_SIDE; j++) {
        fscanf(fin, "%s", mat->M[i][j].val);
        switch(mat->M[i][j].val[1]) {
        case '\0':
          mat->M[i][j].type = 0;
          break;
        case '\\':
          mat->M[i][j].type = 1;
          break;
        default:
          mat->M[i][j].type = 2;
          break;
        }
      }
    }

    for (i=0; i<MATRIX_SIDE; i++) {
      for (j=0; j<MATRIX_SIDE; j++) {
        fscanf(fin, "%d", &(mat->val[i][j]));
      }
    }

    //TODO: print -1 in case of invalid k value
#define shortcase(n, ...) case ##n:   \
    variante##n(trie, mat, ##__VA_ARGS__);    \
    break;
    switch(variante) {
      shortcase(1,k);
      shortcase(2,k);
      shortcase(3);
      shortcase(4);
      shortcase(5,k);
      shortcase(6,k);
    default:
      //TODO: print -1 in case of invalid O value
    }

    
    matrix_destroy(mat);
  }  
}

int main(int argc, char ** argv) {
  trie_node * trie;
  int tmp;
  if (argc==2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)) {
    usage_print(0); //in this case we should not return error
  }
  if (argc!=3) {
    usage_print(EINVAL);
  }
  
  tmp = strlen(argv[1]);
  if (tmp >= 4 && strcmp(argv[1] + tmp - 4, ".dic") == 0) {
    printf("Dictionary filename must end in .dic\n");
    usage_print(EINVAL);
  }

  tmp = strlen(argv[2]);
  if (tmp >= 4 && strcmp(argv[2] + tmp - 4, ".puz") == 0) {
    printf("Puzzle filename must end in .puz\n");
    usage_print(EINVAL);
  }
  
  
  //Reads data from dictionary file and creates the trie:
  trie = new_trie_from_dictionary(argv[1]);
  
  //Proceses matrix and instruction input
  wordmatic_solver(argv[2], trie);

  //free stuff
  trie_destroy(trie);

  return 0;
}
