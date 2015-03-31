#ifndef TRIE_H
#define TRIE_H

//TODO: WE NEED TO IMPLEMENT A SUPER EFICIENT RADIX TREE HERE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

#define TRIE_START_CHAR 'a'
#define TRIE_END_CHAR   'z'
#define SC TRIE_START_CHAR

typedef struct TRIE_NODE {
  int endnode;
  char * append;
  struct TRIE_NODE ** prox; /*ponteiro para array de 26 ponteiros TODO: tornar isto uma array 1d*/
} trie_node;

/*
  This iterator purpose is to let the user agnostic about wheter we are using a trie or a radix tree
 */
typedef struct TRIE_ITERATOR {
  int pos;
  trie_node * node;
} trie_iterator;

trie_node * trie_init();

trie_node * trie_insert(trie_node * root, char * word);

int trie_search(trie_node * root, char * word);

void trie_destroy(trie_node * root);



trie_iterator it_init(trie_node * root);

/*
  Sets the given trie iterator to point to char if available and return 0
  If not available, no change happens to the iterator, and this function returns 1
*/
int it_travel(trie_iterator * it, char c);

int it_isendnode(trie_iterator * it);






#endif
