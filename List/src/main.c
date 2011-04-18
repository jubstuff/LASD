#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"


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

void Duplicato(void)
{
	printf("Stai cercando di inserire un nodo duplicato\n");
}

int main(void)
{
	NODE *Head;
   	OPERATIONS Op;
	int Status; 
	int Num, Num2;
   	Op.Compare = (COMPARATOR)NumCmp;
   	Op.InitNode = (INITIALIZER)InizializzaNodoInt;
	Op.DeleteNode = (DELETER)DeallocaInt;
   	Op.Print = (PRINTER)StampaNodoInt;
    Op.DuplicateNode = (DUPLICATE)Duplicato; 

	return 0;
}
