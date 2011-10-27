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

#endif
