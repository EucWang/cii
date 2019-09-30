/* $Id$ */
#ifndef MEM_INCLUDED
#define MEM_INCLUDED
#include "except.h"
extern const Except_T Memchk_Failed;
extern void *Memchk_alloc (long nbytes,
	const char *file, int line);
extern void *Memchk_calloc(long count, long nbytes,
	const char *file, int line);
extern void Memchk_free(void *ptr,
	const char *file, int line);
extern void *Memchk_resize(void *ptr, long nbytes,
	const char *file, int line);
#define ALLOC(nbytes) \
	Memchk_alloc((nbytes), __FILE__, __LINE__)
#define CALLOC(count, nbytes) \
	Memchk_calloc((count), (nbytes), __FILE__, __LINE__)
#define  NEW(p) ((p) = ALLOC((long)sizeof *(p)))
#define NEW0(p) ((p) = CALLOC(1, (long)sizeof *(p)))
#define FREE(ptr) ((void)(Memchk_free((ptr), \
	__FILE__, __LINE__), (ptr) = 0))
#define RESIZE(ptr, nbytes) 	((ptr) = Memchk_resize((ptr), \
	(nbytes), __FILE__, __LINE__))
#endif
