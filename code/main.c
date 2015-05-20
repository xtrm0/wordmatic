/******************************************************************************
 * File Name:   main.c
 * Author:      Afonso / Osvaldo
 * Revision:
 * NAME:        WordMatic - IST/AED - 2015 2º Sem
 * SYNOPSIS:    #include <stdio.h>
 *              #include "trie.h"
 *              #include "matrix.h"
 *              #include "input_man.h"
 *              #include "solver.h"
 * DESCRIPTION: WordMatic - função main.
 * DIAGNOSTICS: tested
 * USAGE:       aed$ wordmatic <nome1>.dic <nome2>.puz
 *              <nome1> -> ficheiro dicionário
 *              <nome2> -> ficheiro de matrize(s)
 *****************************************************************************/

#include <stdio.h>
#include "../include/trie.h"
#include "../include/matrix.h"
#include "../include/input_man.h"
#include "../include/solver.h"

void usage_print(int err) {
  /*printf(
         "Usage: \n"
         "wordmatic <dictionary>.dic <puzzle>.puz\n"
       );*/
  exit(err);
}

/******************************************************************************
 * wordmatic_solver()
 *
 * Arguments:   filename:   fich .puz
 *              trie:       trie com o dicionário
 *              fout:       ponteiro para ficheiro solução
 * Returns: void
 * Side-Effects: none
 * Description:     problem solver
 *****************************************************************************/
void wordmatic_solver(char * filename, trie_node * trie, FILE * fout) {
  FILE * fin;
  matrix * mat;
  int N;
  int variante, k;
  int maxlen, maxval;

  fin = fopen(filename, "r");
  if (fin == NULL) {
    /*printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);*/
    fprintf(fout, "-1" ENDL ENDL);
    exit(ENOENT);
  }

  assert_read(fscanf(fin, "%d", &N));
  while (N--) {
    mat = matrix_init();
    assert_read(fscanf(fin, "%d %d", &variante, &k));
    read_matrix(fin, mat, &maxlen, &maxval);

    if (!isvalid_mode(variante, k, maxlen, maxval)) {
      fprintf(fout, "-1" ENDL ENDL);
      matrix_destroy(mat);
      continue;
    }

#define shortcase(n, ...) case n:   \
    variante##n(fout, trie, mat, ##__VA_ARGS__); \
    break;

    switch(variante) {
      shortcase(1,k);
      shortcase(2,k);
      shortcase(3);
      shortcase(4);
      shortcase(5,k);
      shortcase(6,k);
    }

    matrix_destroy(mat);
  }
  fclose(fin);
}

/******************************************************************************
 * main()
 *
 * Arguments: argc - aceita 2 argumentos: ficheiros dicionário e matrizes
 *            argv - <nome1>.dic e <nome2>.puz
 * Returns: 0
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
int main(int argc, char ** argv) {
  FILE * fout;
  trie_node * trie;
  int tmp;
  char * outfile;
  int lens[MAXLEN+2];
  int used_chars['z'-'a'+1];

  if (argc==2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)) {
    usage_print(0); /*in this case we should not return error*/
  }

  /*o num de args deve ser = 3! o nome do prog, o fich .dic e o fich .puz*/
  if (argc!=3) {
    usage_print(EINVAL);
  }

  /*testa se o fich de matrizes tem a extensão correcta*/
  tmp = strlen(argv[2]);
  if (tmp >= 4 && strcmp(argv[2] + tmp - 4, ".puz") != 0) {
    /*printf("Puzzle filename must end in .puz\n");*/
    usage_print(EINVAL);
  }

  /* Abre o ficheiro de saída / sai se algum erro*/
  outfile = malloc((tmp+1)*sizeof(char));
  TESTMEM(outfile);
  strcpy(outfile,argv[2]);
  strcpy(outfile+tmp-3, "sol");
  fout = fopen(outfile, "w");
  if (fout == NULL) {
    /*printf("Erro: Nao foi possivel abrir \"%s\"!\n", outfile);*/
    free(outfile);
    exit(ENOENT);
  }

  /*testa se o fich dicionário tem a extensão correcta*/
  tmp = strlen(argv[1]);
  if (tmp >= 4 && strcmp(argv[1] + tmp - 4, ".dic") != 0) {
    /*printf("Dictionary filename must end in .dic\n");*/
    fprintf(fout, "-1" ENDL ENDL);
    usage_print(EINVAL);
  }

  /*lê os caracteres para uma matrix, verifica quais os cumprimentos de
   * palavras a incluir na TRIE e marca os caracteres que vão ser usados*/
  calculate_needed_lenghts(argv[2], lens, used_chars, fout);

  /*Reads data from dictionary file and creates the trie:*/
  trie = new_trie_from_dictionary(argv[1], lens, used_chars, fout);

  /*Proceses matrix and instruction input*/
  wordmatic_solver(argv[2], trie, fout);

  /*free stuff*/
  /*Note: outfile memory is not freed if we encounter any invalid matrix or some file does not exists // is in invalid format*/
  trie_destroy(trie);
  fclose(fout);
  free(outfile);
  return 0;
}
