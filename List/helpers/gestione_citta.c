#include "gestione_citta.h"
#include <string.h>


int ConfrontaNodoCitta( const void *Nodo1, const void *Persona )
{
	//TODO Questi devono essere nodi?
	//No, devono essere un nodo e una persona, perché non
	//devo modificare la libreria
	return ConfrontaCitta( Nodo1->Info, Persona );
}

int ConfrontaCitta( const void *Pers1, const void *Pers2 )
{
	PERSONA P1 = *( (PERSONA *)Pers1 );
	PERSONA P2 = *( (PERSONA *)Pers2 );

	return strcasecmp( P1->Citta, P2->Citta );
}

int ConfrontaPersona( const void *Pers1, const void *Pers2 )
{
	int ReturnStatus;
	PERSONA P1 = *( (PERSONA *)Pers1 );
	PERSONA P2 = *( (PERSONA *)Pers2 );

	ReturnStatus = strcasecmp( P1->Cognome, P2->Cognome );
	if( ReturnStatus == 0 )
	{
		ReturnStatus = strcasecmp( P1->Nome, P2->Nome );
	}

	return ReturnStatus;
}

void *InizializzaPersona( void *Value )
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

OPERATIONS *InizializzaOperazioniListaPersone( void )
{
	OPERATIONS *InnerOp;

	InnerOp = (OPERATIONS *)malloc( sizeof(OPERATIONS) ); //TODO check errors

	InnerOp->InitNode = SalvaPersona;
	InnerOp->Compare = ConfrontaCitta;
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

void StampaPersona( void *Value )
{
}
