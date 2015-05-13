#ifndef STL_H
#define STL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
/*
  structure for a solution stored on the avl tree
*/
typedef struct ELEMENT_VAL {
  char word[19];
  char path[37];
  int len;
  int val;
} element_val;

/*
  Initialization function for element_val
*/
element_val * ev_init(char * w, char *p, int len, int val);
/*
  Destructor function for element_val
*/
void ev_destroy(element_val * v);
#include "avl.h"


#endif
