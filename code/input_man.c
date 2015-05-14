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

void calculate_needed_lenghts(char * filename, int * lens, FILE * fout) {
  int i;
  int mode, k;
  int maxlen, maxval;
  int N;
  FILE * fin;
  matrix M;

  for (i=0;i<MAXLEN+2;i++) lens[i]=0;

  fin = fopen(filename, "r");
  if (fin==NULL) {
    printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);
    fprintf(fout, "-1" ENDL ENDL);
    exit(ENOENT);
  }

  dummy_test(fscanf(fin, "%d", &N));
  while (N--) {
    dummy_test(fscanf(fin, "%d %d", &mode, &k));
    read_matrix(fin, &M, &maxlen, &maxval);
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

trie_node * new_trie_from_dictionary(char * filename, int * lens, FILE * fout) {
  trie_node * trie;
  FILE * fin;
  char read[MAXLEN+2];
  int c=0;
  int i=0;
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
        if (lens[i]) { /*so queremos strings com estes tamanhos*/
          read[i]='\0';
          trie_insert(trie, read);
        }
      }
      i=0;
    } else {
      if (i<=MAXLEN) { /*to avoid buffer overflow*/
        read[i++] = c;
      }
    }
  }
  if (lens[i]) {
    read[i]='\0';
    trie_insert(trie,read);
  }
  fclose(fin);
  return trie;
}
