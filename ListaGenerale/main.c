/**
 * main.c
 * 
 * @author Giustino Borzacchiello - giustinob@gmail.com
 *
 * @date 06/04/11
 *
 * Prova per l'inserimento di puntatori a funzione all'interno di struct
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "operazioni_stringhe.h"
#include "operazioni_numeri.h"

int main(void)
{
	OPERATIONS ListaStringheOp;
	OPERATIONS ListaIntOp;
	NODO *Head = NULL;
	int ReturnStatus;
	
	ListaStringheOp.Compare = (int (*)(void *, void *))strcasecmp;
	ListaStringheOp.Initialize = ( void *(*)( void * ) )InizializzaNodoStringa;
	ListaStringheOp.Print = ( void (*)(void *) )StampaNodoStringa;
	ListaStringheOp.Destroy = ( void (*)(void *) )DeallocaStringa;
	
	Head = ListOrderedInsert("Pippo", Head, &ReturnStatus, &ListaStringheOp);
	Head = ListOrderedInsert("Giustino", Head, &ReturnStatus, &ListaStringheOp);
    Head = ListOrderedInsert("Valeria", Head, &ReturnStatus, &ListaStringheOp);
    Head = ListOrderedInsert("Andrea", Head, &ReturnStatus, &ListaStringheOp);
	
	printf("Prima della cancellazione\n");
	ListPrint(Head, &ListaStringheOp);
	Head = ListRemove( (char *)"Giustino", Head, &ReturnStatus, &ListaStringheOp);
	
	printf("\nDopo della cancellazione\n");
 	ListPrint(Head, &ListaStringheOp);

	ListaIntOp.Compare = (int (*)(void *, void *))NumCmp;
	ListaIntOp.Initialize = ( void *(*)( void * ) )InizializzaNodoInt;
	ListaIntOp.Print = ( void (*)(void *) )StampaNodoInt;
	ListaIntOp.Destroy = ( void (*)(void *) )DeallocaInt;
//	Pause();
    return 0;
}
