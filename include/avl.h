/******************************************************************************
 * File Name: avl.h
 * Author:    Afonso / Osvaldo
 * Revision:
 * NAME
 *     avl - prototypes
 * SYNOPSIS
 *      #include "stl.h"
 * DIAGNOSTICS
 *          OK
 *****************************************************************************/
#ifndef AVL_H
#define AVL_H
#include "stl.h"
typedef struct AVL_NODE {
  int h;
  element_val * v;
  struct AVL_NODE *l, *r;
} avl_node;

avl_node * avl_init();

avl_node * avl_newnode(char * w, char *p, int len, int val);

void avl_destroy(avl_node * l);

int height(avl_node * root);

avl_node * rotate_left (avl_node * root);
avl_node * rotate_right (avl_node * root);

avl_node * avl_insert(avl_node * root, char * w, char *p, int len, int val);


#endif
