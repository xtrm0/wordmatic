#ifndef DEFS_H
#define DEFS_H
#include <errno.h>
#include <limits.h>
#include <assert.h>
typedef char char_type;

/*
  Memory error preventing function:
 */
#define TESTMEM(s) if (s == NULL) {\
fprintf(stderr, "(0x45) Erro detetado: Memory Access Error!");      \
exit(ENOMEM);                                                       \
}

/* Maximum lenght for a word */
#define MAXLEN 18

/* Endline character */
#define ENDL "\n"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

/*Function to prevent warnings given by libc's compiled in an uncommon way*/
#define dummy_test(a) if((a)==0) exit(1)

#endif
