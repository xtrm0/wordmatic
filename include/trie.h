#ifndef TRIE_H
#define TRIE_H

//TODO: WE NEED TO IMPLEMENT A SUPER EFICIENT RADIX TREE HERE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*
  O valor seguinte indica um ponteiro para a HEADER do elf. Na qual obviamente não está nenhum trie armazenada
  Assim, utilizamos este valor para evitar dar algum valor às folhas, e diminuir o tamanho de trie
*/
#define BM_ENDNODE (1<<0)
#define BM_FREE (1<<1)

#define TRIE_START_CHAR 'a'
#define TRIE_END_CHAR   'z'
#define SC TRIE_START_CHAR
typedef char int8;

typedef struct TRIE_NODE {
  int8 bitmask; /* Defined as BM_XXXXX, bitmask bit 0 means endnode, bit 1 means should be free or not*/
  int8 len;
  char * val;
  struct TRIE_NODE * prox;
  struct TRIE_NODE * son;
} trie_node;

/*
  This iterator purpose is to let the user agnostic about wheter we are using a trie or a radix tree
 */
typedef struct TRIE_ITERATOR {
  trie_node * node;
  int8 pos;
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

int it_travel_s(trie_iterator * it, char * c);

int it_isendnode(trie_iterator * it);






#endif
