#include "../include/trie.h"

trie_node * trie_init() {
  trie_node * val = NULL;
  val = malloc(sizeof(trie_node));
  TESTMEM(val);
  memset(val,0,sizeof(trie_node));
  
  val->prox = malloc(sizeof(trie_node*)*(TRIE_END_CHAR - TRIE_START_CHAR + 1));
  TESTMEM(val->prox);
  memset(val->prox,0,sizeof(trie_node*)*(TRIE_END_CHAR - TRIE_START_CHAR + 1));
  
  return val;
}

trie_node * trie_insert(trie_node * root, char * word) {  
  if (root==NULL)
    root = trie_init();
  
  if (*word=='\0') {
    root->endnode = 1;
    return root;
  }
  
  root->prox[*word - TRIE_START_CHAR] = trie_insert(root->prox[*word - TRIE_START_CHAR], word+1);
  return root;
}

int trie_search(trie_node * root, char * word) {
  while (*word!='\0') {
    if (root->prox[*word - TRIE_START_CHAR] == NULL)
      return 0;
    root = root->prox[*word - TRIE_START_CHAR];
    word += 1;
  }
  return (root->endnode==1);
}

void trie_destroy(trie_node * root) {
  int i;
  if (root==NULL)
    return;
  for (i=0; i<=TRIE_END_CHAR - TRIE_START_CHAR; i++) {
    trie_destroy(root->prox[i]);
  }
  free(root->prox);
  free(root);
}
