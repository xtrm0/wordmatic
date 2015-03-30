#include "../include/trie.h"

int main() {
  FILE *f;
  trie_node * root = trie_init();
  char s1[] = "afonso";
  char s2[] = "afonsofixe";
  char s3[] = "fixe";
  char s4[200];
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

  printf("running long dictionary insert test\n");
  root = trie_init();
  f= fopen("/home/xtrm0/repo/school/aed/proj/dictionaries/input.dic", "r");
  while (fscanf(f,"%s", s4)!=EOF) {
    trie_insert(root, s4);
  }
  trie_destroy(root);
  return 0;
}
