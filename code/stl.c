/******************************************************************************
 * File Name:   stl.c
 * Author:      Afonso / Osvaldo
 * Revision:
 * NAME:        WordMatic - IST/AED - 2015 2º Sem
 * SYNOPSIS:    stl.h
 * DESCRIPTION: .
 * DIAGNOSTICS: tested
 *****************************************************************************/
#include "../include/stl.h"

/******************************************************************************
 * ev_init()
 *
 * Arguments:   w, p, len, val
 * Returns:     element_val
 * Side-Effects:
 * Description:  Initialization function for element_val
 *****************************************************************************/
element_val * ev_init(char * w, char *p, int len, int val) {
  element_val * v = malloc(sizeof(element_val));
  TESTMEM(v);
  strcpy(v->word, w);
  strcpy(v->path, p);
  v->len        = len;
  v->val        = val;
  return v;
}

/******************************************************************************
 * ev_destroy()
 *
 * Arguments:   element_val
 * Returns:     void
 * Side-Effects: no
 * Description:  Destructor function for element_val
 *****************************************************************************/
void ev_destroy(element_val * v) {
  free(v);
}
