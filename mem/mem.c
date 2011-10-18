/** 
 * mem.c
 *
 * implementation of the mem interface
 *
 * */

#include <stdlib.h>
#include <stddef.h>
#include "mem.h"

void *Mem_alloc(long nbytes, const char *file, int line)
{
	void *ptr;

	ptr = malloc(nbytes);
	if( ptr == NULL )
	{
		//TODO RAISE ERROR
	}
	return ptr;
}

void *Mem_calloc(long count, long nbytes, const char *file, int line)
{
	void *ptr;

	ptr = calloc(count, nbytes);
	if( ptr == NULL )
	{
		//TODO RAISE ERROR
	}

	return ptr;
}

void Mem_free(void *ptr, const char *file, int line)
{
	if( ptr )
	{
		free(ptr);
	}
}

void *Mem_resize(void *ptr, long nbytes, const char *file, int line)
{
	ptr = realloc(ptr, nbytes);
	if( ptr == NULL )
	{
		//TODO RAISE ERROR
	}
	return ptr;
}
