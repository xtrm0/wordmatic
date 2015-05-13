#ifndef TRIE_H
#define TRIE_H
/*
  This code contains the implementation of a self compressing trie (radix tree), highly otimized for memory
  It should always be faster than a full prefix hashmap that uses about the same memory.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

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

/*
  Creates a new trie
*/
trie_node * trie_init();
/*
  Inserts a new node into the trie
*/
trie_node * trie_insert(trie_node * root, char * word);
/*
  Checks whether a given word is inside the trie
  Returns non-zero if word inside the trie
*/
int trie_search(trie_node * root, char * word);
/*
  Recursively free's a trie
*/
void trie_destroy(trie_node * root);


/*
  Creates a new trie_iterator
*/
trie_iterator it_init(trie_node * root);

/*
  Sets the given trie iterator to point to char if found and return 0
  If not found, no change happens to the iterator, and this function returns 1
*/
int it_travel(trie_iterator * it, char c);

/*
  Make the iterator travel trough strings c, or until a non match is found
   (the iterator is left on the last valid state before the non match)
*/
int it_travel_s(trie_iterator * it, char * c);

/*
  Returns 1 if the iterator is at the end of a word in the trie.
  Returns 0 otherwise
*/
int it_isendnode(trie_iterator it);


#endif
