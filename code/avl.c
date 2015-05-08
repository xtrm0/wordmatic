#include "../include/avl.h"

avl_node * avl_init() {
  return NULL;
}

avl_node * avl_newnode(char * w, char *p, int len, int val) {
  avl_node * n = malloc(sizeof(avl_node));
  element_val * v = ev_init(w, p, len, val);
  memset(n,0,sizeof(avl_node));
  n->v = v;
  n->h = 1;
  return n;
}

void avl_destroy(avl_node * l) {
  if (l==NULL) return;
  free(l->l);
  free(l->r);
  ev_destroy(l->v);
  free(l);
}

int height(avl_node * root) {
  if (root==NULL)
    return 0;
  return root->h;
}

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
