#include "../include/stl.h"

element_val * ev_init(char * w, char *p, int len, int val) {
  element_val * v = malloc(sizeof(element_val));
  TESTMEM(v);
  strcpy(v->word, w);
  strcpy(v->path, p);
  v->len        = len;
  v->val        = val;
  return v;
}

void ev_destroy(element_val * v) {
  free(v);
}
