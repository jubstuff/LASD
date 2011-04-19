#include "operazioni_numeri.h"

void *InizializzaNodoInt( void *Value )
{
	int *Num = (int *) malloc( sizeof(int) );
	printf("Inizializzo il numero....\n");
	*Num = *( (int *)Value );
	return (void *)Num;
}

void StampaNodoInt( const void *Value )
{
	printf("%d\n", *( (int *)Value) );
}

void DeallocaInt( void *Value )
{
	free(Value);
}


int NumCmp( const void *FirstArg, const void *SecondArg )
{
	int ReturnValue;
	int First = *( (int *)FirstArg );
	int Second = *( (int *)SecondArg );

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

void Duplicato( void *Value )
{
	int Num = *( (int *)Value );
	printf("Stai cercando di inserire un nodo duplicato\n");
	printf("Il valore che stavi cercando di inserire è %d\n", Num);
}
