#include "operazioni_numeri.h"

int *InizializzaNodoInt( int *Value )
{
	int *Num = (int *) malloc( sizeof(int) );
	*Num = *Value;
	return Num;
}

void StampaNodoInt( int *Value )
{
	printf("%d\n", *Value);
}

void DeallocaInt( int *Value )
{
	free(Value);
}


int NumCmp( const void *FirstArg, const void *SecondArg )
{
	int ReturnValue;
	int First = *(int *)FirstArg;
	int Second = *(int *)SecondArg;

	if ( First < Second )
	{
		ReturnValue = -1;
	}
	else if ( First == Second )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;

}
