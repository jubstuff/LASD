#include <stdio.h>
#include <stdlib.h>
#include "../src/lista.h"
#include "gestione_citta.h"
#include <string.h>

/*============================================================================*
 * OPERAZIONI LISTA ESTERNA - ORDINATA PER CITTA'
 *===========================================================================*/
/**
 * Confronta in ordine lessicografico la città memorizzata nel primo elemento
 * della lista puntata da <Nodo1> con la città memorizzata in <Persona>
 *
 * Il primo parametro è il campo info del nodo della lista esterna, mentre
 * il secondo parametro è la struct PERSONA che si vuole inserire nella 
 * lista interna.
 * */
int ConfrontaNodoCitta( const void *Nodo1, const void *Persona )
{
	NODE *Nodo = (NODE *)Nodo1;
	PERSONA *P1 =  (PERSONA *)(Nodo->Info);
	PERSONA *P2 =  (PERSONA *)Persona;

	return strcasecmp( P1->Citta, P2->Citta );
}


/**
 * Funzione che crea un nodo della lista interna.
 *
 * Questa funzione inserisce un nodo con campo pari alla PERSONA passata in
 * ingresso nella lista interna, la cui testa è il campo info del nodo della 
 * lista esterna.
 *
 * Per fare questo, crea un nuovo nodo, a cui associa la PERSONA e poi 
 * restituisce un riferimento a questo nodo, che andrà memorizzato nel campo
 * info della lista esterna.
 * */
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
/**
 * Scorre la lista esterna, richiamando la funzione di stampa della libreria sul
 * campo info (che è la testa della lista interna relativa a quella città)
 * */
void StampaListaCitta( const void *Value )
{
	/* che deve fare questa funzione? Gli viene passato
	 * un nodo come valore, quindi deve richiamare la funzione 
	 * stampa della lista interna, semplicemente
	 * */
	OPERATIONS *InnerOp;
	InnerOp = InizializzaOperazioniListaPersone();

	List_RecursivePrint( (NODE *)Value, InnerOp );
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
	PERSONA *P = (PERSONA *)Value;
	printf("%s %s - %s\n", P->Nome, P->Cognome, P->Citta);
}
