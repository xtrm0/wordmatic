#ifndef AVL_H
#define AVL_H
#include "stl.h"
typedef struct AVL_NODE {
  int h;
  element_val * v;
  struct AVL_NODE *l, *r;
} avl_node;

/*
  Creates a new avl tree
*/
avl_node * avl_init();

/*
  Creates a new avl node, initialized with the given parameters
*/
avl_node * avl_newnode(char * w, char *p, int len, int val);

/*
  Destroys an avltree recursively
*/
void avl_destroy(avl_node * l);

/*
  Gets the height of a node + 1
  Complexity: O(1)
*/
int height(avl_node * root);

/*
  Default avl rotations
*/
avl_node * rotate_left (avl_node * root);
avl_node * rotate_right (avl_node * root);

/*
  Inserts a node into an avl tree

  Complexity: logarithmic on the number of nodes in the tree
*/
avl_node * avl_insert(avl_node * root, char * w, char *p, int len, int val);


#endif
