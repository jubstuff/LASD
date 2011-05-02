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
 *
 * @return -1, 0, 1 se Nodo1->Info [>,==,<] Persona rispettivamente
 * */
int ConfrontaNodoCitta( const void *Nodo1, const void *Persona )
{
	NODE *Nodo = (NODE *)Nodo1;
	//Recupero il campo del primo elemento della lista
	PERSONA *P1 =  (PERSONA *)(Nodo->Info);
	PERSONA *P2 =  (PERSONA *)Persona;

	return strcasecmp( P1->Citta, P2->Citta );
}


/**
 * Inserisce un nodo nella lista
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
/**
 * Gestisce l'inserimento di una persona nella lista, nel caso esista già
 * una persona residente nella stessa città.
 *
 * @param Persona       Riferimento alla struct PERSONA da inserire nella lista
 * @param HeadContainer Riferimento al nodo contenente la testa della lista 
 *                      relativa alla città di residenza della persona in input
 *
 * */
void DuplicatoCitta( void *Persona, NODE *HeadContainer )
{
	//A questa funzione viene passato l'indirizzo della struct Persona e
	//un riferimento al nodo in cui è stato trovato il duplicato
	OPERATIONS *InnerOp;
	int ReturnStatus;

	ReturnStatus = 0;

	InnerOp = InizializzaOperazioniListaPersone();
    printf("Inserisco il duplicato\n");
	HeadContainer->Info = List_RecursiveOrderedInsert(Persona, HeadContainer->Info,
		   	&ReturnStatus, InnerOp); //TODO check error

	free(InnerOp);

}
/**
 * Scorre la lista esterna, richiamando la funzione di stampa della libreria sul
 * campo info (che è la testa della lista interna relativa a quella città)
 *
 * @param Head Testa della lista relativa ad una città
 * */
void StampaListaCitta( const void *Head )
{
	/* che deve fare questa funzione? Gli viene passato
	 * un nodo come valore, quindi deve richiamare la funzione 
	 * stampa della lista interna, semplicemente
	 * */
	OPERATIONS *InnerOp;
	InnerOp = InizializzaOperazioniListaPersone();

	List_RecursivePrint( (NODE *)Head, InnerOp );
	free(InnerOp);

}
/**
 * Elimina una persona dalla lista
 *
 * Elimina una persona dalla lista relativa ad una data città,
 * dati in input Nome, Cognome e città di residenza.
 *
 * @param Persona  Riferimento alla persona da eliminare
 * @param NodeInfo Testa della lista relativa alla città di residenza della
 *                 persona da eliminare
 *
 * */
void EliminaNodoCitta(void *Persona, void *NodeInfo)
{
	NODE *HeadTemp = (NODE *)NodeInfo;
    int ReturnStatus; 
	OPERATIONS *InnerOp;

	InnerOp = InizializzaOperazioniListaPersone();

	HeadTemp = List_RecursiveDelete( Persona, HeadTemp, &ReturnStatus, InnerOp ); 
	free(InnerOp);
}
/*============================================================================*
 * OPERAZIONI LISTA INTERNA - ORDINATA PER PERSONA
 *===========================================================================*/
/**
 * Confronta in ordine lessicografico due persone per cognome e poi per nome.
 *
 * @param Pers1 Riferimento alla prima struct PERSONA da confrontare
 * @param Pers2 Riferimento alla seconda struct PERSONA da confrontare
 *
 * @return -1, 0, 1 se Pers1 [>,==,<] Pers2 rispettivamente
 * */
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
/**
 * Alloca e inizializza una struct OPERATIONS contenente i puntatori a funzioni
 * per la gestione di una lista di struct PERSONA.
 *
 * @return Riferimento alla struct OPERATIONS inizializzata
 *
 * NOTA
 * È compito del programmatore deallocare la struct dopo l'utilizzo
 *
 * */
OPERATIONS *InizializzaOperazioniListaPersone( void )
{
	OPERATIONS *InnerOp;

	InnerOp = (OPERATIONS *)malloc( sizeof(OPERATIONS) );
	if( InnerOp != NULL )
	{
		InnerOp->InitNode = InizializzaPersona;
		InnerOp->Compare = ConfrontaPersona;
		InnerOp->DeleteNode = CancellaPersona;
		InnerOp->Print = StampaPersona;
		InnerOp->ManageDuplicate = DuplicatoPersona; 
	}

	return InnerOp;
}
/**
 * Alloca e inizializza una struct PERSONA e tutti i suoi campi, copiandoli 
 * dalla struct PERSONA passata in input.
 *
 * @param InputPers Struct PERSONA da cui copiare i valori della persona da 
 *                  creare.
 *
 * @return Riferimento alla struct PERSONA allocata
 * */
void *InizializzaPersona( void *InputPers )
{
	//Questa dovrebbe creare una struct PERSONA, copiare i valori da
	//<InputPers> e poi ritornarne l'indirizzo.
	PERSONA *PersTemp = (PERSONA *)InputPers;
	PERSONA *NewPers = (PERSONA *)malloc( sizeof( PERSONA ) );

	NewPers->Nome = (char *) malloc( (strlen(PersTemp->Nome) + 1) * sizeof(char) ); 
	NewPers->Cognome = (char *) malloc( (strlen(PersTemp->Cognome) + 1) * sizeof(char) ); 
	NewPers->Citta = (char *) malloc( (strlen(PersTemp->Citta) + 1) * sizeof(char) ); 

	strcpy( NewPers->Nome, PersTemp->Nome); 
	strcpy( NewPers->Cognome, PersTemp->Cognome);   
	strcpy( NewPers->Citta, PersTemp->Citta);

	return NewPers;
}
/**
 * Dealloca una struct PERSONA e tutti i suoi campi
 *
 * @param Value Valore da eliminare dalla lista
 * @param NodeInfo Riferimento al campo da deallocare
 *
 * */
void CancellaPersona( void *Value, void *NodeInfo )
{
   PERSONA *PersTemp = (PERSONA *)NodeInfo;
   free( PersTemp->Nome );
   free( PersTemp->Cognome );
   free( PersTemp->Citta );
   free( PersTemp );
}	
/**
 * Visualizza nome, cognome e città di residenza di una persona sullo stdout
 *
 * */
void StampaPersona( const void *Value )
{
	PERSONA *P = (PERSONA *)Value;
	printf("%s %s - %s\n", P->Nome, P->Cognome, P->Citta);
}
/**
 * Visualizza un messaggio sullo stdout, notificando che una persona con 
 * nome e cognome uguale a quella passata in input, è già presente in quella
 * determinata città 
 *
 * */
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
