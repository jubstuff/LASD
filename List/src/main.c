#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "../helpers/gestione_citta.h"


int main(void)
{
	NODE *Head;
   	OPERATIONS Op;
	int ReturnStatus;
	int Num;

	Head = NULL;
	ReturnStatus = 0;

   	Op.Compare = ConfrontaNodoCitta;
   	Op.InitNode = InizializzaNodoCitta;
	Op.DeleteNode = NULL;
   	Op.Print = NULL;
    Op.ManageDuplicate = NULL; 
                                        
	return 0;
}
