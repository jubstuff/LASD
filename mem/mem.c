/** 
 * mem.c
 *
 * implementation of the mem interface
 *
 * */

#include <stdlib.h>
#include <stddef.h>
#include "mem.h"

J_STATUS MemAlloc( long Nbytes, void *OutPtr)
{
	void *Ptr;
	J_STATUS Status;

	status = SUCCESS;

	Ptr = malloc(Nbytes);
	if( ptr != NULL )
	{
		OutPtr = Ptr;
	}
	else
	{
		status = ERROR;
		OutPtr = NULL;
	}
	return Status;

}

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
