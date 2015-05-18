/******************************************************************************
 * File Name:   trie.c
 * Author:      Afonso / Osvaldo
 * Revision:
 * NAME:        WordMatic - IST/AED - 2015 2º Sem
 * SYNOPSIS:    #include "trie.h"
 * DESCRIPTION: Implements trie auxiliary functions
 *              This code contains the implementation of a self compressing
 *          trie (radix tree), highly otimized for memory.
 *              It should always be faster than a full prefix hashmap
 *          that uses about the same memory.
 * DIAGNOSTICS: tested
 *****************************************************************************/
#include "../include/trie.h"

/******************************************************************************
 * trie_init()
 *
 * Arguments:
 * Returns:     pointer to root node of the trie
 * Side-Effects: nope
 * Description: Creates a new trie
 *****************************************************************************/
trie_node * trie_init() {
  trie_node * trie = NULL;
  trie = malloc(sizeof(trie_node));
  TESTMEM(trie);
  memset(trie,0,sizeof(trie_node));
  trie->len=1;
  return trie;
}



/******************************************************************************
 * _trie_new_node()
 *
 * Arguments:   word
 * Returns:     pointer to root node of the trie
 * Side-Effects: nope
 * Description: @private
 *                  Creates a new endnode
 *****************************************************************************/
trie_node * _trie_new_node(char * word) {
  trie_node * trie = NULL;

  trie = malloc(sizeof(trie_node));
  TESTMEM(trie);
  memset(trie,0,sizeof(trie_node));
  trie->len = strlen(word);
  trie->val = malloc(sizeof(char)*(trie->len));
  trie->bitmask = BM_ENDNODE | BM_FREE;
  memcpy(trie->val, word, trie->len);
  return trie;
}

/******************************************************************************
 * _trie_split_node()
 *
 * Arguments:   old:
 *              offset:
 * Returns:     void
 * Side-Effects:
 * Description: @private
 *                  Splits a node into 2, at position offset
 *****************************************************************************/
void _trie_split_node(trie_node * old, int8 offset) {
  trie_node * newn = NULL;

  newn = malloc(sizeof(trie_node));
  TESTMEM(newn);
  memset(newn,0,sizeof(trie_node));

  newn->len = old->len - offset;
  newn->val = old->val + offset;
  newn->bitmask = old->bitmask ^ (old->bitmask & BM_FREE); /*desliga o bit free para o filho*/
  newn->son = old->son;

  old->len = offset;
  old->bitmask ^= (old->bitmask & BM_ENDNODE); /*desliga o bit endnode*/
  old->son = newn;
}

/******************************************************************************
 * trie_insert()
 *
 * Arguments:   root:   root of the trie
 *              word:   palavra a insrir na trie
 * Returns:     pointer to root node of the trie
 * Side-Effects: nope
 * Description: Inserts a new node into the trie
 *****************************************************************************/
void trie_insert(trie_node * root, char * word) {
  trie_iterator it;
  trie_node * aux;

  it = it_init(root);
  while(*word) {
    if (it_travel(&it, *word)) {
      if (it.pos + 1 == it.node->len) {
        aux = _trie_new_node(word);
        aux->prox = it.node->son;
        it.node->son = aux;
        return;
      } else {
        _trie_split_node(it.node, it.pos + 1);
        it.node->son->prox = _trie_new_node(word);
        return;
      }
    }
    word++;
  }

  if (it.pos + 1 != it.node->len)
    _trie_split_node(it.node, it.pos + 1);
  it.node->bitmask |= BM_ENDNODE;
  return;
}

/******************************************************************************
 * trie_search()
 *
 * Arguments:   root:   root of the trie
 *              word:   palavra a insrir na trie
 * Returns:     Returns non-zero if word inside the trie
 * Side-Effects: nope
 * Description: Checks whether a given word is inside the trie.
 *****************************************************************************/
int trie_search(trie_node * root, char * word) {
  trie_iterator it = it_init(root);
  if (it_travel_s(&it, word)) return 0;
  return (it_isendnode(it));
}

/******************************************************************************
 * trie_destroy()
 *
 * Arguments:   root:   root of the trie
 * Returns:     void
 * Side-Effects: nope
 * Description: Recursively free's a trie.
 *****************************************************************************/
void trie_destroy(trie_node * root) {
  if (root==NULL) return;
  trie_destroy(root->prox);
  trie_destroy(root->son);
  if (root->bitmask & BM_FREE)
    free(root->val);
  free(root);
}

/******************************************************************************
 * it_init()
 *
 * Arguments:   root:   root of the trie
 * Returns:     trie_iterator
 * Side-Effects: nope
 * Description: Creates a new trie_iterator.
 *****************************************************************************/
trie_iterator it_init(trie_node * root) {
  trie_iterator it;

  it.node = root;
  it.pos = 0;
  return it;
}

/******************************************************************************
 * it_travel()
 *
 * Arguments:   it
 *              c
 * Returns:     trie_iterator
 * Side-Effects:
 * Description: Sets the given trie iterator to point to char if found and
 *              return 0.
 *              If not found, no change happens to the iterator,
 *              and this function returns 1.
 *****************************************************************************/
int it_travel(trie_iterator * it, char c) {
  trie_node * aux;

  if (it->node->len == it->pos + 1) {
    aux = it->node->son;
    while (aux!=NULL) {
      if (aux->val[0]==c) {
        it->node = aux;
        it->pos = 0;
        return 0;
      }
      aux=aux->prox;
    }
    return 1;
  } else {
    if (it->node->val[it->pos+1] == c) {
      it->pos ++;
      return 0;
    } else {
      return 1;
    }
  }

  return 0;
}

/******************************************************************************
 * it_travel_s()
 *
 * Arguments:   it
 *              c
 * Returns:
 * Side-Effects:
 * Description: Make the iterator travel trough strings c, or until a non
 *              match is found (the iterator is left on the last valid state
 *              before the non match).
 *****************************************************************************/
int it_travel_s(trie_iterator * it, char *c) {
  while (*c) {
    if (it_travel(it, *c)) {
      return 1;
    }
    c++;
  }
  return 0;
}

/******************************************************************************
 * it_isendnode()
 *
 * Arguments:   it
 * Side-Effects:
 * Description: Returns 1 if the iterator is at the end of a word in the trie.
 *              Returns 0 otherwise.
 *****************************************************************************/
int it_isendnode(trie_iterator it) {
  if (it.node->len == (it.pos + 1) && (it.node->bitmask & BM_ENDNODE)) {
    return 1;
  } else {
    return 0;
  }
}
