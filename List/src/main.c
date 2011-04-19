#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"


int *InizializzaNodoInt( int *Value )
{
	int *Num = (int *) malloc( sizeof(int) );
	printf("Inizializzo il numero....\n");
	*Num = *Value;
	return Num;
}

void StampaNodoInt( void *Value )
{
	printf("%d\n", *((int *)Value));
}

void DeallocaInt( int *Value )
{
	free(Value);
}


int NumCmp( const void *FirstArg, const void *SecondArg )
{
	int ReturnValue;
	int First = *((int *)FirstArg);
	int Second = *((int *)SecondArg);

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

	int *Num = (int *) Value;
	printf("Stai cercando di inserire un nodo duplicato\n");
	printf("Il valore che stavi cercando di inserire è %d\n", *Num);
}

int main(void)
{
	NODE *Head;
   	OPERATIONS Op;
	int ReturnStatus;
	int Num;

	Head = NULL;
	ReturnStatus = 0;

   	Op.Compare = (COMPARATOR)NumCmp;
   	Op.InitNode = (INITIALIZER)InizializzaNodoInt;
	Op.DeleteNode = (DELETER)DeallocaInt;
   	Op.Print = (PRINTER)StampaNodoInt;
    Op.ManageDuplicate = (DUPLICATE)Duplicato; 
                                        
	Num = 1;
    Head = List_RecursiveOrderedInsert(&Num, Head, &ReturnStatus, &Op);
    Head = List_RecursiveOrderedInsert(&Num, Head, &ReturnStatus, &Op);
	List_RecursivePrint( Head, &Op );
	return 0;
}
