#include <stdio.h>
#include <stdlib.h>
#include "../src/lista.h"
#include "gestione_citta.h"
#include <string.h>

/*============================================================================*
 * OPERAZIONI LISTA ESTERNA - ORDINATA PER CITTA'
 *===========================================================================*/
/**
 * Confronta la città memorizzata nel primo elemento della lista puntata da 
 * <Nodo1> con la città memorizzata in <Persona>
 * Confronta in ordine lessicografico le città memorizzate in 
 * due struct PERSONA
 * */
int ConfrontaNodoCitta( const void *Nodo1, const void *Persona )
{
	//TODO Questi devono essere nodi?
	//No, devono essere un nodo e una persona, perché non
	//devo modificare la libreria
	NODE *Nodo = (NODE *)Nodo1;
	PERSONA *P1 =  (PERSONA *)(Nodo->Info);
	PERSONA *P2 =  (PERSONA *)Persona;

	return strcasecmp( P1->Citta, P2->Citta );
}


void *InizializzaNodoCitta( void *Value )
{
	//A questa funzione viene passato l'indirizzo della struct Persona
	NODE *InnerHead;
	OPERATIONS *InnerOp;
	int ReturnStatus;

	InnerHead = NULL;         
	ReturnStatus = 0;

	InnerOp = InizializzaOperazioniListaPersone();

	InnerHead = List_RecursiveOrderedInsert(Value, InnerHead, &ReturnStatus, InnerOp);

	free(InnerOp);

	return (void *)InnerHead;
}

void DuplicatoCitta( void *Value, NODE *Current )
{
	//A questa funzione viene passato l'indirizzo della struct Persona e
	//un riferimento al nodo in cui è stato trovato il duplicato
	OPERATIONS *InnerOp;
	int ReturnStatus;

	ReturnStatus = 0;

	InnerOp = InizializzaOperazioniListaPersone();
    printf("Inserisco il duplicato\n");
	Current->Info = List_RecursiveOrderedInsert(Value, Current->Info, &ReturnStatus, InnerOp); //TODO check error

	free(InnerOp);

}
/*============================================================================*
 * OPERAZIONI LISTA INTERNA - ORDINATA PER PERSONA
 *===========================================================================*/
int ConfrontaPersona( const void *Pers1, const void *Pers2 )
{
	int ReturnStatus;
	PERSONA *P1 =  (PERSONA *)Pers1;
	PERSONA *P2 =  (PERSONA *)Pers2;

	ReturnStatus = strcasecmp( P1->Cognome, P2->Cognome );
	if( ReturnStatus == 0 )
	{
		ReturnStatus = strcasecmp( P1->Nome, P2->Nome );
	}

	return ReturnStatus;
}

OPERATIONS *InizializzaOperazioniListaPersone( void )
{
	OPERATIONS *InnerOp;

	InnerOp = (OPERATIONS *)malloc( sizeof(OPERATIONS) ); //TODO check errors

	InnerOp->InitNode = SalvaPersona;
	InnerOp->Compare = ConfrontaPersona;
	InnerOp->DeleteNode = CancellaPersona;
	InnerOp->Print = StampaPersona;
	//InnerOp->ManageDuplicate =  //TODO aggiungere funzione per duplicati

	return InnerOp;
}

void *SalvaPersona( void *Value )
{
	//Questa dovrebbe creare una struct PERSONA, copiare i valori da
	//<Value> e poi ritornarne l'indirizzo.
	return Value;
}

void CancellaPersona( void *Value )
{
}	

void StampaPersona( const void *Value )
{
}
