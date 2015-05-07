#ifndef STL_H
#define STL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
typedef struct LIST_VAL {
  char word[20];
  char path[39];
  int len;
  int val;
} list_val;

typedef struct LIST_NODE {
  list_val * val;
  struct LIST_NODE * next;
} list;

typedef struct QUEUE {
  list * front;
  list * back;
} queue;

list * list_init();
list * list_new(char * w, char *p, int len, int val);
void list_destroy_node(list * l);
void list_destroy(list * l);
queue * queue_init();
int queue_empty(queue * q);
void queue_push(queue * q, char * w, char * p, int len, int val);
list_val * queue_front(queue * q);
void queue_pop(queue * q);
void queue_destroy(queue * q);
/*
  Transforma a queue numa nova queue, ordenada e em que cada palavra e unica
*/
void queue_sort_uniq(queue * q);

#endif
