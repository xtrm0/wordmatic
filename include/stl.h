#ifndef STL_H
#define STL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
typedef struct ELEMENT_VAL {
  char word[20];
  char path[39];
  int len;
  int val;
} element_val;

element_val * ev_init(char * w, char *p, int len, int val);
void ev_destroy(element_val * v);
#include "avl.h"


#endif
