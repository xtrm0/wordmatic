#ifndef DEFS_H
#define DEFS_H
#include <errno.h>
#include <limits.h>
#include <assert.h>
typedef char char_type;

/*
  Funcao para prevenir erros de memoria:
 */
#define TESTMEM(s) if (s == NULL) {\
fprintf(stderr, "(0x45) Erro detetado: Memory Access Error!");      \
exit(ENOMEM);                                                       \
}

/* Maximum lenght for a word */
#define MAXLEN 18

#define ENDL "\r\n"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

#endif
