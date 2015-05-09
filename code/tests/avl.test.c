#include "../../include/stl.h"

void tree_infix_print(avl_node * r) {
  if (r==NULL) return;
  tree_infix_print(r->l);
  printf("%s\n", r->v->word);
  tree_infix_print(r->r);
}

int main() {
  avl_node * r = avl_init();
  char nil[] = "nil";
  char a[][2] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

  r = avl_insert(r,a[0],nil,0,0);
  r = avl_insert(r,a[1],nil,0,0);
  r = avl_insert(r,a[2],nil,0,0);
  r = avl_insert(r,a[3],nil,0,0);
  r = avl_insert(r,a[4],nil,0,0);
  r = avl_insert(r,a[5],nil,0,0);
  r = avl_insert(r,a[6],nil,0,0);
  r = avl_insert(r,a[7],nil,0,0);
  r = avl_insert(r,a[8],nil,0,0);
  r = avl_insert(r,a[9],nil,0,0);
  tree_infix_print(r);
  return 0;
}
