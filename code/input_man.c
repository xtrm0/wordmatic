/******************************************************************************
 * File Name:   input_man.c
 * Author:      Afonso / Osvaldo
 * Revision:
 * NAME:        WordMait - IST/AED - 2015 2º Sem
 * SYNOPSIS:    #include "input_man.h"
 * DESCRIPTION: .
 * DIAGNOSTICS: tested
 *****************************************************************************/
#include "../include/input_man.h"

/******************************************************************************
 * isvalid_mode()
 *
 * Arguments:   mode:       variante do problema
 *              k:          tamanho ou valor
 *              maxlen      tamanho máximo da palavra
 *              maxval:     valor máximo da palavra
 * Returns:     int
 * Side-Effects: nope
 * Description: Checks if the mode given by the user is valid or not
 *****************************************************************************/
int isvalid_mode(int mode, int k, int maxlen, int maxval) {
  if (maxlen>MAXLEN) return 0;
  if (mode<1 || mode>6) return 0;
  if (mode==1 || mode==2 || mode==5)
    if (k < 3 || k > maxlen) return 0;
  if (mode==6)
    if (k < 3 || k > maxval) return 0;
  return 1;
}

/******************************************************************************
 * _read_matrix_precalc()
 *
 * Arguments:   fin:        ponteiro para o ficheiro .puz
 *              mat:        matriz de caracteres(->m) e de valores (->val)
 *              maxlenght:  tamanho máximo da palavra
 *              maxval:     valor máximo da palavra
 *              used_chars: array de caracteres usados no problema
 * Returns: void
 * Side-Effects:
 *              fin:        incrementa
 *              mat:        preenche a matriz com os valores do fich .puz
 *              maxlenght:  altera
 *              maxval:     altera
 *              used_chars: constroi o array de caracteres usados no problema
 * Description:
 *****************************************************************************/
void _read_matrix_precalc(FILE * fin, matrix * mat, int * maxlenght, int * maxval, int * used_chars) {
  int i, j, k, aux;

  *maxlenght = 0;
  *maxval = 0;
  memset(mat, 0, sizeof(matrix));
  /*coloca os caracters do problema na matriz*/
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      assert_read(fscanf(fin, "%s", mat->M[i][j]));
      /*para o caso de existir + do que 1 caracter na célula*/
      aux = strlen(mat->M[i][j]);
      *maxlenght += aux;
      for (k=0; k<aux; k++)
        used_chars[mat->M[i][j][k]-'a']=1;
    }
  }
  /*coloca os valores dos caracters do problema na matriz*/
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      assert_read(fscanf(fin, "%d", &(mat->val[i][j])));
      *maxval += mat->val[i][j];
    }
  }
}

/******************************************************************************
 * calculate_needed_lenghts()
 *
 * Arguments:   filename:   nome do .dic
 *              lens:
 *              used_chars:
 *              fout:       ponteiro para o ficheiro de saida
 * Returns: void
 * Side-Effects:    lens[]
 *                  used_chars[]
 *
 * Description: Checks what are the lenghts of the words that we should insert
 *          into the trie. (also marks used characters)
 * Complexity: linear on the number of bytes in the .puz file
 *****************************************************************************/
void calculate_needed_lenghts(char * filename, int * lens, int * used_chars, FILE * fout) {
  int i;
  int mode, k;
  int maxlen, maxval;
  int N;
  FILE * fin;
  matrix M;

  /*inicializar*/
  for (i=0;i<MAXLEN+2;i++) lens[i]=0;
  for (i=0;i<='z'-'a';i++) used_chars[i]=0;


  fin = fopen(filename, "r");
  if (fin==NULL) {
    printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);
    fprintf(fout, "-1" ENDL ENDL);
    exit(ENOENT);
  }

  /*lê o 1ro caracter: numero de problemas a resolver: N*/
  assert_read(fscanf(fin, "%d", &N));
  /*while "N" problemas*/
  while (N--) {
    /*lê os 2do e 3os caracteres: variantes do problema "N"*/
    assert_read(fscanf(fin, "%d %d", &mode, &k));
    _read_matrix_precalc(fin, &M, &maxlen, &maxval, used_chars);
    /*verifica se os parametros estão correctos e*/
    if (isvalid_mode(mode,k,maxlen,maxval)==0) continue;
    /*constroi o array das palavras pretendidas*/
    switch (mode) {
      case 1:
      case 2:
        lens[k]=1;
        break;
      case 3:
        for (i=3; i<=maxlen; i++) lens[i]=1;
        break;
      case 4:
        for (i=3; i<=maxlen; i++) lens[i]=1;
        break;
      case 5:
        lens[k]=1;
        break;
      case 6:
        for (i=3; i<=maxlen; i++) lens[i]=1;
        break;
    }
  }
  lens[19]=0;
  fclose(fin);
}

/******************************************************************************
 * new_trie_from_dictionary()
 *
 * Arguments:   filename:   nome do .dic
 *              lens:       array de tamanhos de palavras a incluir na TRIE
 *              used_chars: array de caractares possiveis
 *              fout:       ponteiro para o ficheiro de saida
 * Returns: void
 * Side-Effects:    none
 * Description:
 *              Reads a text file and returns a new trie made of its words
 * Note:    We try to read a dictionary file even if it is not on the format
 *      specified.
 *          We allow the word separator to be any blankspace, automatically
 *      cutoff words not needed and ignore duplicates.
 * Complexity:  worst case: O(1/4 LKN);
 *              K is a constante tha depends on to the number of diferent
 *          characters in the alphabet (in our case 26, which means 1<K<=26),
 *          and the compression factor of the trie generated by the dictionary
 *              N is the number of characters in the dictionary the complexity
 *          highly depends on the overlapping of words in the dictionary, and
 *          the
 *****************************************************************************/
trie_node * new_trie_from_dictionary(char * filename, int * lens, int * used_chars, FILE * fout) {
  trie_node * trie;
  FILE * fin;
  char read[MAXLEN+2];
  int c=0;
  int i=0;
  int use=1;

  /*termina se erro com o ficheiro .dic*/
  fin = fopen(filename, "r");
  if (fin==NULL) {
    printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);
    fprintf(fout, "-1" ENDL ENDL);
    exit(ENOENT);
  }

  trie = trie_init();

  while ((c=fgetc(fin)) != EOF) {
    if (isspace(c)) {
      if (i>0) {
        if (lens[i] && use) { /*we only want strings with these sizes and with valid chars*/
          read[i]='\0';
          trie_insert(trie, read);
        }
      }
      i=0;
      use=1;
    } else {
      if (i<=MAXLEN) { /*to avoid buffer overflow*/
        read[i++] = c;
        if (!used_chars[c-'a']) use=0;
      }
    }
  }
  if (lens[i] && use) {
    read[i]='\0';
    trie_insert(trie,read);
  }
  fclose(fin);
  return trie;
}
