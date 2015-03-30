#include "../include/input_man.h"

trie_node * new_trie_from_dictionary(char * filename) {
  trie_node * trie;
  FILE * fin;
  char read[20];
  int c=0;
  int i=0;
  fin = fopen("filename", "r");
  if (fin==NULL) {
    printf("Erro: Nao foi possivel abrir \"%s\"!\n", filename);
    exit(ENOENT);
  }
  trie = trie_init();
  while ((c=fgetc(fin)) != EOF) {
    if (isspace(c)) {
      if (i>0) {
        if (i>=3 && i<=18) { //so queremos strings com estes tamanhos
          read[i]='\0';
          trie_insert(trie, read);
        }
      }
      i=0;
    } else {
      if (i<19) { //to avoid buffer overflow
        read[i++] = c;
      }
    }
  }
  if (i>=3 && i<=18) {
    read[i]='\0';
    trie_insert(trie,read);
  }
  return trie;
}
