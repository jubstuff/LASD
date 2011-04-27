#include <stdio.h>
#include <stdlib.h>
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

/*void EliminaNodoCitta( const void *Value )
{
	List_RecursiveDelete( NODE *Value, ); 
}*/
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
	InnerOp->ManageDuplicate = DuplicatoPersona; //TODO aggiungere funzione per duplicati

	return InnerOp;
}

void *SalvaPersona( void *Value )
{
	//Questa dovrebbe creare una struct PERSONA, copiare i valori da
	//<Value> e poi ritornarne l'indirizzo.
	PERSONA *PersTemp = (PERSONA *)Value;
	PERSONA *NewPers = (PERSONA *)malloc( sizeof( PERSONA ) );

	NewPers->Nome = (char *) malloc( (strlen(PersTemp->Nome) + 1) * sizeof(char) ); 
	NewPers->Cognome = (char *) malloc( (strlen(PersTemp->Cognome) + 1) * sizeof(char) ); 
	NewPers->Citta = (char *) malloc( (strlen(PersTemp->Citta) + 1) * sizeof(char) ); 

	strcpy( NewPers->Nome, PersTemp->Nome); 
	strcpy( NewPers->Cognome, PersTemp->Cognome);   
	strcpy( NewPers->Citta, PersTemp->Citta);

	return NewPers;
}

void CancellaPersona( void *Value )
{
   PERSONA *PersTemp = (PERSONA *)Value;
   free( PersTemp->Nome );
   free( PersTemp->Cognome );
   free( PersTemp->Citta );
   free( PersTemp );
}	

void StampaPersona( const void *Value )
{
	PERSONA *P = (PERSONA *)Value;
	printf("%s %s - %s\n", P->Nome, P->Cognome, P->Citta);
}


void DuplicatoPersona( void *Value, NODE *CurrentNode )
{
	printf("Persona già presente\n"); 
}
/*==============================================================================
 * Funzioni di utilità
 *============================================================================*/

/**
 * Legge una stringa da standard input, di lunghezza massima <LenMax>.
 * NOTE 
 *  - Tutti i caratteri di controllo e, in generale, non alfanumerici vengono 
 *    ignorati.
 *  - La stringa viene restituita senza '\n' finale.
 *
 * @param Buf    Stringa digitata dall'utente.
 * @param LenMax Lunghezza massima consentita alla stringa in input.
 */
void LeggiStringa( char *Buf, int LenMax)
{
	fgets(Buf, LenMax, stdin);

	while ( *Buf < 0 || *Buf > 31) //ignora tutti i caratteri non alfanumerici
	{
		Buf++;
	}
	*Buf = '\0';
}

/**
 * Visualizza un menu per la scelta delle operazioni da effettuare
 *
 * @return L'identificativo dell'operazione da effettuare
 *
 */
char Menu()
{
	char TempBuffer[10];

	printf("=================================================\n");
	puts("Lista di Stringhe - Menu");
	printf("=================================================\n");
	puts("1 - Inserisci una persona nella lista.");
	puts("2 - Eliminare una persona dalla lista.");
	puts("3 - Eliminare tutte le persone dalla lista.");
	puts("9 - Stampa la lista a video.");
	puts("0 - Esci");
	puts("Operazione da effettuare: ");
	printf("?>");
	
	fgets(TempBuffer, sizeof(TempBuffer), stdin);
	
	return TempBuffer[0];
}
