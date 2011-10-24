/**
 * mem.h
 *
 * Abstraction for C's standard library memory management functions
 *
 * */
#include "errors.h"

#ifndef MEM_H
#define MEM_H

extern J_STATUS MemAlloc( long nbytes, void **OutPtr);
extern J_STATUS MemCalloc( long Count, long Nbytes, void **OutPtr);
extern J_STATUS MemFree( void **Ptr );
extern J_STATUS MemRealloc( long Nbytes, void **Ptr );

#define ALLOC(nbytes, ptr) \
	MemAlloc((nbytes), (ptr))

#define CALLOC(count, nbytes, ptr) \
	MemCalloc((count), (nbytes), (ptr))

#define FREE(ptr) (MemFree((ptr)))

#define RESIZE(nbytes, ptr) (MemRealloc((nbytes), (ptr)))

#define  NEW(p) ((p) = ALLOC((long)sizeof *(p)))

#define NEWO(p) ((p) = CALLOC(1, (long)sizeof *(p)))

#endif
