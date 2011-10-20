/**
 * mem.h
 *
 * Abstraction for C's standard library memory management functions
 *
 * */
#include "errors.h"

#ifndef MEM_H
#define MEM_H

extern void *Mem_alloc( long nbytes, const char *file, int line);
extern J_STATUS MemAlloc( long nbytes, void **OutPtr);
extern J_STATUS MemCalloc( long Count, long Nbytes, void **OutPtr);
extern J_STATUS MemFree( void **Ptr );
extern void *Mem_calloc( long count, long nbytes, const char *file, int line);
extern void Mem_free(void *ptr, const char *file, int line);
extern void *Mem_resize(void *ptr, long nbytes, const char *file, int line);


#define ALLOC(nbytes) \
	Mem_alloc((nbytes), __FILE__, __LINE__)

#define CALLOC(nbytes) \
	Mem_calloc((nbytes), __FILE__, __LINE__)

#define FREE(ptr) ((void)(Mem_free((ptr), \
				__FILE__, __LINE__), (ptr) = 0))

#define RESIZE(ptr, nbytes) ((ptr) = Mem_resize((ptr), \
			(nbytes), __FILE__, __LINE__))

#define  NEW(p) ((p) = ALLOC((long)sizeof *(p)))

#define NEWO(p) ((p) = CALLOC(1, (long)sizeof *(p)))

#endif
