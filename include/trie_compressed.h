#ifndef TRIE_H
#define TRIE_H
//#include "bitmask.h"
/*
  Representa um no da trie:
  bitmask: uma bitmask com alguns valores para fazer pruning nas buscas:
    bitmask.bit[0] - E um no final?
    bitmask.bit[1..18] - Existe alguma continuacao com 1..18  caracteres?
    bitmask.byte[3] - tamanho 
 */
typedef struct TRIE_NODE {
  int bitmask; 
  struct TRIE_NODE * prox;
} trie_node;


#endif
