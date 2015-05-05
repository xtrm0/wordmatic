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
  printf("Running long dictionary insert test\n");
  root = trie_init();
  f= fopen("/home/xtrm0/repo/school/aed/proj/dictionaries/input.dic", "r");
  while (fscanf(f,"%s", s4)!=EOF) {
    trie_insert(root, s4);
    if (trie_search(root, s4)!=1) {
      printf("Error: %s\n", s4);
    }
  }
  rewind(f);
  while (fscanf(f,"%s", s4)!=EOF) {
    if (trie_search(root, s4)!=1) {
      printf("Error: %s\n", s4);
    }
  }
  printf("done! press any...\n");
  scanf("%d", s1);


  return 0;
}
