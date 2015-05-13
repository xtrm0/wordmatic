#include "../include/trie.h"

trie_node * trie_init() {
  trie_node * trie = NULL;
  trie = malloc(sizeof(trie_node));
  TESTMEM(trie);
  memset(trie,0,sizeof(trie_node));
  trie->len=1;
  return trie;
}

/*
@private
  Creates a new endnode
*/
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

/*
@private
  Splits a node into 2, at position offset
*/
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

trie_node * trie_insert(trie_node * root, char * word) {
  trie_iterator it;
  trie_node * aux;
  it = it_init(root);
  while(*word) {
    if (it_travel(&it, *word)) {
      if (it.pos + 1 == it.node->len) {
        aux = _trie_new_node(word);
        aux->prox = it.node->son;
        it.node->son = aux;
        return root;
      } else {
        _trie_split_node(it.node, it.pos + 1);
        it.node->son->prox = _trie_new_node(word);
        return root;
      }
    }
    word++;
  }
  if (it.pos + 1 == it.node->len) {
    it.node->bitmask |= BM_ENDNODE;
    return root;
  } else {
    _trie_split_node(it.node, it.pos + 1);
    it.node->bitmask |= BM_ENDNODE;
    return root;
  }
  return root;
}


int trie_search(trie_node * root, char * word) {
  trie_iterator it = it_init(root);
  if (it_travel_s(&it, word)) return 0;
  return (it_isendnode(it));
}


void trie_destroy(trie_node * root) {
  if (root==NULL) return;
  trie_destroy(root->prox);
  trie_destroy(root->son);
  if (root->bitmask & BM_FREE)
    free(root->val);
  free(root);
}


trie_iterator it_init(trie_node * root) {
  trie_iterator it;
  it.node = root;
  it.pos = 0;
  return it;
}

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

int it_travel_s(trie_iterator * it, char *c) {
  while (*c) {
    if (it_travel(it, *c)) {
      return 1;
    }
    c++;
  }
  return 0;
}

int it_isendnode(trie_iterator it) {
  if (it.node->len == (it.pos + 1) && (it.node->bitmask & BM_ENDNODE)) {
    return 1;
  } else {
    return 0;
  }
}
