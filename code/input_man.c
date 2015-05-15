#include "../include/input_man.h"

int isvalid_mode(int mode, int k, int maxlen, int maxval) {
  if (maxlen>MAXLEN) return 0;
  if (mode<1 || mode>6) return 0;
  if (mode==1 || mode==2 || mode==5)
    if (k < 3 || k > maxlen) return 0;
  if (mode==6)
    if (k < 3 || k > maxval) return 0;
  return 1;
}

void _read_matrix_precalc(FILE * fin, matrix * mat, int * maxlenght, int * maxval, int * used_chars) {
  int i, j, k, aux;
  *maxlenght = 0;
  *maxval = 0;
  memset(mat, 0, sizeof(matrix));
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      dummy_test(fscanf(fin, "%s", mat->M[i][j]));
      aux = strlen(mat->M[i][j]);
      *maxlenght += aux;
      for (k=0; k<aux; k++)
        used_chars[mat->M[i][j][k]-'a']=1;
    }
  }
  for (i=0; i<MATRIX_SIDE; i++) {
    for (j=0; j<MATRIX_SIDE; j++) {
      dummy_test(fscanf(fin, "%d", &(mat->val[i][j])));
      *maxval += mat->val[i][j];
    }
  }
}


void calculate_needed_lenghts(char * filename, int * lens, int * used_chars, FILE * fout) {
  int i;
  int mode, k;
  int maxlen, maxval;
  int N;
  FILE * fin;
  matrix M;

  for (i=0;i<MAXLEN+2;i++) lens[i]=0;
  for (i=0;i<='z'-'a';i++) used_chars[i]=0;

  fin = fopen(filename, "r");
  if (fin==NULL) {
    printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);
    fprintf(fout, "-1" ENDL ENDL);
    exit(ENOENT);
  }

  dummy_test(fscanf(fin, "%d", &N));
  while (N--) {
    dummy_test(fscanf(fin, "%d %d", &mode, &k));
    _read_matrix_precalc(fin, &M, &maxlen, &maxval, used_chars);
    if (isvalid_mode(mode,k,maxlen,maxval)==0) continue;
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

trie_node * new_trie_from_dictionary(char * filename, int * lens, int * used_chars, FILE * fout) {
  trie_node * trie;
  FILE * fin;
  char read[MAXLEN+2];
  int c=0;
  int i=0;
  int use=1;
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
