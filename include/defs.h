/******************************************************************************
 * File Name: defs.h
 * Author:    Afonso / Osvaldo
 * Revision:
 * DESCRIPTION
 *          funcoes e definicoes de apoio de uso geral
 * DIAGNOSTICS
 *          OK
 *****************************************************************************/
#ifndef DEFS_H
#define DEFS_H

#include <errno.h>
#include <limits.h>
#include <assert.h>
typedef char char_type;

/*Memory error preventing function:*/
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
#define assert_read(a) if((a)==0) exit(1)

/*Change return codes to 0, in order to comply to guidelines*/
#ifdef EINVAL
#undef EINVAL
#define EINVAL 0
#endif
#ifdef ENOENT
#undef ENOENT
#define ENOENT 0
#endif
#ifdef ENOMEM
#undef ENOMEM
#define ENOMEM 0
#endif

#endif
