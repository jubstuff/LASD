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

int main(void)
{
	OPERATIONS ListaStringheOp;
	NODO *Head = NULL;
	int ReturnStatus;
	
	ListaStringheOp.Compare = (int (*)(void *, void *))strcasecmp;
	ListaStringheOp.Initialize = ( void *(*)( void * ) )InizializzaNodoStringa;
	ListaStringheOp.Print = ( void (*)(void *) )StampaNodoStringa;
	ListaStringheOp.Destroy = ( void (*)(void *) )DeallocaStringa;
	
	Head = ListInsert("Pippo", Head, &ReturnStatus, &ListaStringheOp);
	Head = ListInsert("Giustino", Head, &ReturnStatus, &ListaStringheOp);
	Head = ListInsert("Valeria", Head, &ReturnStatus, &ListaStringheOp);
	Head = ListInsert("Andrea", Head, &ReturnStatus, &ListaStringheOp);
	
	printf("Prima della cancellazione\n");
	ListPrint(Head, &ListaStringheOp);
	Head = ListRemove( (char *)"Giustino", Head, &ReturnStatus, &ListaStringheOp);
	
	printf("\n‡Dopo della cancellazione\n");
 	ListPrint(Head, &ListaStringheOp);
	Pause();
    return 0;
}
