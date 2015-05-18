/******************************************************************************
 * File Name: input_man.h
 * Author:    Afonso / Osvaldo
 * Revision:
 * NAME
 *     input_man - prototypes
 * SYNOPSIS
 *      #include "trie.h"
 *      #include "matrix.h"
 *      #include <ctype.h>
 * DESCRIPTION
 *		Implements input auxiliary functions
 * DIAGNOSTICS
 *          OK
 *****************************************************************************/
#ifndef INPUT_MAN_H
#define INPUT_MAN_H

#include <ctype.h>
#include "trie.h"
#include "matrix.h"

int isvalid_mode(int mode, int k, int maxlen, int maxval);
void calculate_needed_lenghts(char * filename, int * lens, int * user_chars, FILE * fout);
trie_node * new_trie_from_dictionary(char * filename, int * lens, int * used_chars, FILE * fout);

#endif
