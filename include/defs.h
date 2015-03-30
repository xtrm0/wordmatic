#ifndef DEFS_H
#define DEFS_H
#include <errno.h>
typedef char char_type;

/*
  Funcao para prevenir erros de memoria:
 */
#define TESTMEM(s) if (s == NULL) {\
fprintf(stderr, "(0x45) Erro detetado: Memory Access Error!");      \
exit(ENOMEM);                                                       \
}


#endif
