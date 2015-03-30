#include "../include/trie.h"

int main() {
  trie_node * root = trie_init();
  char s1[] = "afonso";
  char s2[] = "afonsofixe";
  char s3[] = "fixe";
  printf("running first insert\n");
  trie_insert(root,s1);
  trie_insert(root,s2);
  trie_insert(root,s3);
  /*output should be 1001*/
  printf("%d\n", trie_search(root,s1));
  printf("%d\n", trie_search(root, s1+1));
  s1[5]=0;
  printf("%d\n", trie_search(root, s1));
  s1[5]='o';
  printf("%d\n", trie_search(root, s1));
  trie_destroy(root);
  return 0;
}
