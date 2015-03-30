#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

#define TRIE_START_CHAR 'a'
#define TRIE_END_CHAR   'z'
#define SC TRIE_START_CHAR

typedef struct TRIE_NODE {
  int endnode;
  struct TRIE_NODE ** prox; /*ponteiro para array de 26 ponteiros*/
} trie_node;

trie_node * trie_init();

trie_node * trie_insert(trie_node * root, char * word);

int trie_search(trie_node * root, char * word);

void trie_destroy(trie_node * root);





#endif
