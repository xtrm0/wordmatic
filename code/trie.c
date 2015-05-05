#include "../include/trie.h"

trie_node * trie_init() {
  trie_node * trie = NULL;
  trie = malloc(sizeof(trie_node));
  TESTMEM(trie);
  memset(trie,0,sizeof(trie_node));
  return trie;
}

trie_node * trie_insert(trie_node * root, char * word) {
  trie_node * aux;
  if (root==NULL)
    root = trie_init();
  aux = root;
  while (*(word+1)) {
    if (aux->prox[*word-TRIE_START_CHAR] == TRIE_NODE_ASSIGNED) {
      aux->prox[*word-TRIE_START_CHAR] = trie_init();
      aux->prox[*word-TRIE_START_CHAR]->endnode = 1;
    }
    if (aux->prox[*word-TRIE_START_CHAR] == NULL)
      aux->prox[*word-TRIE_START_CHAR] = trie_init();
    aux = aux->prox[*word-TRIE_START_CHAR];
    word++;
  }
  if (aux->prox[*word-TRIE_START_CHAR] == NULL || aux->prox[*word-TRIE_START_CHAR] == TRIE_NODE_ASSIGNED)
    aux->prox[*word-TRIE_START_CHAR] = TRIE_NODE_ASSIGNED;
  else {
    aux->prox[*word-TRIE_START_CHAR]->endnode = 1;
  }

  return root;
}


int trie_search(trie_node * root, char * word) {
  trie_iterator it = it_init(root);
  while (*word) {
    if (it_travel(&it, *word))
      return 0;
    word++;
  }
  return (it_isendnode(&it));
}

void trie_destroy(trie_node * root) {
  int i;
  if (root==NULL || root==TRIE_NODE_ASSIGNED)
    return;
  if (root->prox != NULL) {
    for (i=0; i<=TRIE_END_CHAR - TRIE_START_CHAR; i++) {
      trie_destroy(root->prox[i]);
    }
  }
  if (root->append!=NULL)
    free(root->append);
  free(root);
}


trie_iterator it_init(trie_node * root) {
  trie_iterator it;
  it = root;
  return it;
}

int it_travel(trie_iterator * it, char c) {
  if (*it==NULL || *it == TRIE_NODE_ASSIGNED || (*it)->prox[c-TRIE_START_CHAR]==NULL) {
    return 1;
  }
  *it = (*it)->prox[c-TRIE_START_CHAR];
  return 0;
}

int it_isendnode(trie_iterator * it) {
  if ((*it)==NULL) {
    return 0;
  } else if (*it==TRIE_NODE_ASSIGNED) {
    return 1;
  } else {
    return ((*it)->endnode == 1);
  }
}
