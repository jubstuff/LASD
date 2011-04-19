#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "../helpers/operazioni_numeri.h"


int main(void)
{
	NODE *Head;
   	OPERATIONS Op;
	int ReturnStatus;
	int Num;

	Head = NULL;
	ReturnStatus = 0;

   	Op.Compare = NumCmp;
   	Op.InitNode = InizializzaNodoInt;
	Op.DeleteNode = DeallocaInt;
   	Op.Print = StampaNodoInt;
    Op.ManageDuplicate = Duplicato; 
                                        
	Num = 1;
    Head = List_RecursiveOrderedInsert(&Num, Head, &ReturnStatus, &Op);
    Head = List_RecursiveOrderedInsert(&Num, Head, &ReturnStatus, &Op);
	List_RecursivePrint( Head, &Op );
	return 0;
}
