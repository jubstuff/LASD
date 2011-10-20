/** 
 * mem.c
 *
 * implementation of the mem interface
 *
 * */

#include <stdlib.h>
#include <stddef.h>
#include "mem.h"

J_STATUS MemAlloc( long Nbytes, void **OutPtr)
{
	void *Ptr;
	J_STATUS Status;

	Status = SUCCESS;

	Ptr = malloc(Nbytes);
	if( Ptr != NULL )
	{
		*OutPtr = Ptr;
	}
	else
	{
		Status = ERROR;
		*OutPtr = NULL;
	}
	return Status;

}

J_STATUS MemCalloc( long Count, long Nbytes, void **OutPtr)
{
	void *Ptr;
	J_STATUS Status;

	Status = SUCCESS;

	Ptr = calloc(Count, Nbytes);
	if( Ptr != NULL )
	{
		*OutPtr = Ptr;
	}
	else
	{
		Status = ERROR;
		*OutPtr = NULL;
	}
	return Status;

}

J_STATUS MemFree( void **Ptr )
{
	J_STATUS Status;

	Status = SUCCESS;

	if( *Ptr )
	{
		free(*Ptr);
	}
	else
	{
		Status = ERROR;
	}
	*Ptr = NULL;
	return Status;
}

J_STATUS MemRealloc( long Nbytes, void **Ptr )
{
    J_STATUS Status;
    void *TempPtr;

    Status = SUCCESS;

    TempPtr = realloc( *Ptr, Nbytes );
    if( TempPtr != NULL )
	{
		*Ptr = TempPtr;
	}
	else
	{
		Status = ERROR;
		*Ptr = NULL;
	}

	return Status;
}
