#include "../include/stl.h"

list * list_init() {
  return NULL;
}

list * list_new(char * w, char *p, int len, int val) {
  list_val * v = malloc(sizeof(list_val));
  list * li = malloc(sizeof(list));
  TESTMEM(v);
  TESTMEM(li);
  strcpy(v->word, w);
  strcpy(v->path, p);
  v->len        = len;
  v->val        = val;
  li->next      = NULL;
  li->val       = v;
  return li;
}

void list_destroy_node(list * l) {
  free(l->val);
  free(l);
}

void list_destroy(list * l) {
  list * aux;
  aux = l;
  while (aux!=NULL) {
    aux = l->next;
    list_destroy_node(l);
  }
}

queue * queue_init() {
  queue * q = malloc(sizeof(queue));
  memset(q,0,sizeof(queue));
  return q;
}

void queue_push(queue * q, char * w, char * p, int len, int val) {
  list * li = list_new(w, p, len, val);
  if (q->front == NULL) {
    q->front = q->back = li;
  } else {
    q->back->next = li;
    q->back       = li;
  }
}

list_val * queue_front(queue * q) {
  if (q->front == NULL) return NULL;
  return q->front->val;
}

void queue_pop(queue * q) {
  list * aux;
  if (q->front == NULL) return;
  aux      = q->front;
  q->front = q->front->next;
  list_destroy_node(aux);
}

int queue_empty(queue * q) {
  return q->front == NULL;
}

void queue_destroy(queue * q) {
  while (!queue_empty(q)) {
    queue_pop(q);
  }
  free(q);
}

list * merge_uniq(list * left, list * right) {
  list * ans;
  list * aux;
  if (right==NULL) {
    return left;
  }
  if (left==NULL) {
    return right;
  }
  if (strcmp(left->val->word,right->val->word)<=0) {
    ans = left;
    left = left->next;
  } else {
    ans = right;
    right = right->next;
  }
  while (left!=NULL && right!=NULL) {
    if (strcmp(left->val->word,right->val->word)<=0) {
      if (strcmp(ans->val->word, left->val->word)!=0) {
        ans->next = left;
        left = left->next;
      } else {
        aux = left->next;
        list_destroy_node(left);
        left = aux;
      }
    } else {
      if (strcmp(ans->val->word, right->val->word)!=0) {
        ans->next = right;
        right = right->next;
      } else {
        aux = right->next;
        list_destroy_node(right);
        right = aux;
      }
    }
  }
  while (left!=NULL) {
    ans->next = left;
    left = left->next;
  }
  while (right!=NULL) {
    ans->next = right;
    right = right->next;
  }
  return ans;
}

list * merge_sort_uniq(list * left) {
    list * right;
    list * aux;
    if (left->next == NULL) {
      return left;
    }
    if (left->next->next == NULL) {
      right = left->next;
      left->next = NULL;
      return merge_uniq(left, right);
    }

    right=aux=left;
    while (aux->next!=NULL && aux->next->next != NULL) {
      right=right->next;
      aux=aux->next->next;
    }
    aux = right->next;
    right->next = NULL;
    right = aux;
    return merge_uniq(merge_sort_uniq(left), merge_sort_uniq(right));
}

/*
  Returns a queue that is sorted version of the initial queue
*/
void queue_sort_uniq(queue * q) {
  q->front = merge_sort_uniq(q->front);
  list * aux = q->front;
  if (aux==NULL) {
    q->back = NULL;
    return;
  }
  while(aux->next!=NULL) aux=aux->next;
  q->back = aux;
}
