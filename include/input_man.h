#ifndef INPUT_MAN_H
#define INPUT_MAN_H
#include "trie.h"
#include <ctype.h>

/*
  Reads a text file and returns a new trie made of its words
  Note: we try to read a dictionary file even if it is not on the format specified. We allow the word separator to be any blankspace, automatically cutoff words larger than admissable and ignore duplicates.
*/
trie_node * new_trie_from_dictionary(char * filename);




#endif
