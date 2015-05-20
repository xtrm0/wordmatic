/******************************************************************************
 * File Name:   avl.c
 * Author:      Afonso / Osvaldo
 * Revision:
 * NAME:        WordMatic - IST/AED - 2015 2º Sem
 * SYNOPSIS:    avl.h
 * DESCRIPTION: .
 * DIAGNOSTICS: tested
 *****************************************************************************/
#include "../include/avl.h"

/******************************************************************************
 * avl_init()
 *
 * Arguments:   none
 * Returns:     avl_node
 * Side-Effects: none
 * Description: Creates a new avl tree
 *****************************************************************************/
avl_node * avl_init() {
  return NULL;
}

/******************************************************************************
 * avl_newnode()
 *
 * Arguments:   w, p, len, val
 * Returns:     avl_node
 * Side-Effects: none
 * Description: Creates a new avl node, initialized with the given parameters
 *****************************************************************************/
avl_node * avl_newnode(char * w, char *p, int len, int val) {
  avl_node * n = malloc(sizeof(avl_node));
  element_val * v = ev_init(w, p, len, val);
  memset(n,0,sizeof(avl_node));
  n->v = v;
  n->h = 1;
  return n;
}

/******************************************************************************
 * avl_destroy()
 *
 * Arguments:   avl_node
 * Returns:     void
 * Side-Effects: none
 * Description: Destroys an avltree recursively
 *****************************************************************************/
void avl_destroy(avl_node * l) {
  if (l==NULL) return;
  avl_destroy(l->l);
  avl_destroy(l->r);
  ev_destroy(l->v);
  free(l);
}

/******************************************************************************
 * height()
 *
 * Arguments:   root
 * Returns:     int
 * Side-Effects: none
 * Description:  Gets the height of a node + 1
  Complexity: O(1)
 *****************************************************************************/
int height(avl_node * root) {
  if (root==NULL)
    return 0;
  return root->h;
}

/******************************************************************************
 * rotate_left()
 * rotate_right()
 *
 * Arguments:   root
 * Returns:     avl_node
 * Side-Effects:
 * Description:  Default avl rotations
 *****************************************************************************/
avl_node * rotate_left (avl_node * root) {
  if (root==NULL) return root;
  if (root->r==NULL) return root;
  avl_node * x = root->r;
  avl_node * b = x->l;
  x->l         = root;
  root->r      = b;

  root->h = max(height(root->l), height(root->r))+1;
  x->h    = max(height(x->l), height(x->r))+1;

  return x;
}
avl_node * rotate_right (avl_node * root) {
  if (root==NULL) return root;
  if (root->l==NULL) return root;
  avl_node * x = root->l;
  avl_node * b = x->r;
  x->r         = root;
  root->l      = b;

  root->h = max(height(root->l), height(root->r))+1;
  x->h    = max(height(x->l), height(x->r))+1;

  return x;
}

/******************************************************************************
 * avl_insert()
 *
 * Arguments:   root, w, p, len, val
 * Returns:     avl_node
 * Side-Effects:
 * Description:  Inserts a node into an avl tree
 * Complexity: logarithmic on the number of nodes in the tree
 *****************************************************************************/
avl_node * avl_insert(avl_node * root, char * w, char *p, int len, int val) {
  int h1,h2,h3;
  int cmp;
  if (root==NULL) {
    return avl_newnode(w,p,len,val);
  }
  cmp = strcmp(w,root->v->word);
  if (cmp==0) return root;
  if (cmp<0) {
    root->l = avl_insert(root->l,w,p,len,val);
  } else {
    root->r = avl_insert(root->r,w,p,len,val);
  }
  root->h = max(height(root->l),height(root->r)) + 1;
  h1 = height(root->l);
  h2 = height(root->r);
  h3 = h1-h2;

  if (cmp < 0 && h3 > 1)
    return root = rotate_right(root);
  if (cmp > 0 && h3 < -1)
    return root = rotate_left(root);
  if (cmp < 0 && h3 < -1) {
    root->l =  rotate_left(root->l);
    return root = rotate_right(root);
  }
  if (cmp > 0 && h3 > 1) {
    root->r =  rotate_right(root->r);
    return root = rotate_left(root);
  }
  return root;
}
