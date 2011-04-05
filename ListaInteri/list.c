/**
 * list.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 04/02/11
 * @package ListaInteri
 *
 * Implementazioni delle funzioni per la gestione di una lista di interi.
 * 
 */

#include "list.h"

/**
 * Inserisce un nodo all'interno della lista
 *
 * Questa funzione utilizza un approccio ricorsivo per inserire un nodo
 * con campo <Value> all'interno della lista con testa <Current>.
 * 
 * NOTA Se un nodo con campo pari a <Value> è già esistente, la lista
 * non viene modificata
 * 
 * @param Value        Campo intero del nodo da inserire.
 * @param Current      Testa della lista in cui inserire il nodo.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *	                   - 0, in caso di inserimento corretto
 *                     - E_MALLOC, in caso di errore nella creazione del nodo
 *                     - W_DUPLICATE, in caso di valore già presente in lista
 *
 * @return Il puntatore alla testa della lista eventualmente modificato.
 */ 
NODO *ListInsert(int Value, NODO *Current, int *ReturnStatus)
{
	NODO *NewNode; /**< puntatore al nuovo nodo creato */
	
	/*se la lista è vuota oppure il nodo è maggiore, inserisci un nuovo nodo */
	if(Current == NULL || Current->Info > Value)
	{
		/*alloca e inizializza il nuovo nodo*/
		NewNode = malloc(sizeof(NODO));
		if( NewNode != NULL )
		{
			NewNode->Info = Value;
			NewNode->Next = Current;
			/* il valore di Current può essere sovrascritto perché salvato in
			 * NewNode->Next */
			Current = NewNode;
			*ReturnStatus = 0; //Nodo inserito
		}
		//errore malloc
		else 
		{
			*ReturnStatus = E_MALLOC; 
		}
	}   
	//Valore già presente in lista
	else if(Current->Info == Value)
	{
		*ReturnStatus = W_DUPLICATE;
	}
	//Valore non trovato
	else
	{
		/* vai avanti nella ricerca */
		Current->Next = ListInsert(Value, Current->Next, ReturnStatus);
	}
	return Current;
}

/**
 * Rimuove un nodo dalla lista
 *
 * Questa funzione utilizza un approccio ricorsivo per rimuovere un nodo
 * con campo <Value> dalla lista con testa <Current>.
 * 
 * NOTA Se un nodo con campo pari a <Value> non esiste, la lista
 * non viene modificata
 * 
 * @param Value        Campo intero del nodo da rimuovere.
 * @param Current      Testa della lista da cui rimuovere il nodo.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *                     - I_FOUND, in caso di nodo trovato e rimosso
 *                     
 *
 * @return Il puntatore alla testa della lista eventualmente modificato.
 */
NODO *ListRemove(int Value, NODO *Current, int *ReturnStatus)
{
	NODO *Temp;
	// cerca il nodo solo se la lista non è vuota
	if(Current != NULL) {
		// se il nodo corrente è quello cercato, cancellalo
		if(Current->Info == Value)
		{
			Temp = Current->Next;
			free(Current);
			Current = Temp;
			*ReturnStatus = I_FOUND; //Nodo trovato e rimosso
		}
		// altrimenti prosegui la ricerca
		else
		{
			Current->Next = ListRemove(Value, Current->Next, ReturnStatus);
		}
	} 
	return Current;
}

/**
 * Stampa i campi della lista, in ordine, utilizzando un approccio ricorsivo.
 *
 * @param Current Testa della lista da stampare a video.
 */
void ListPrint(NODO *Current) 
{
	// stampa la lista, se non vuota, nodo per nodo
	if(Current != NULL)
	{
		printf("%d\t", Current->Info);
		ListPrint(Current->Next);
	}
}

/**
 * Dealloca tutti i nodi della lista, utilizzando un approccio ricorsivo.
 *
 * @param Current Testa della lista da deallocare.
 *
 * @return Il puntatore alla testa eventualmente modificato.
 */
NODO *ListDeallocate(NODO *Current) 
{
	if(Current != NULL)
	{
		/* scorre la lista fino all'ultimo ed effettua la cancellazione
		 * in ordine inversa */
		Current->Next = ListDeallocate(Current->Next);
		free(Current);
		Current = NULL;
	}
	return Current;
}

/*==============================================================================
 * Funzioni di utilità
 *============================================================================*/

/**
 * Legge un intero da standard input, salvandolo nel parametro <Value>.
 * Il formato riconosciuto dalla stringa in ingresso è il seguente:
 * [spazi] [{+ | –}] [0 [{ x | X }]] [numeri]
 *
 * In caso di input non conforme al modello, verrà tentato un parsing fino al 
 * primo carattere non numerico, ovvero:
 *  123abc => 123
 *
 * @param Value [out] Numero digitato dall'utente.
 *
 * @return L'esito della lettura da standard input. Può assumere valore: 
 *		   - 1 se l'operazione ha avuto successo, 
 *		   - 0 se l'operazione non ha avuto successo.
 *
 */
int LeggiIntero(int *Value)
{
	char TempBuffer[13]; /**< 32 bit con segno, più '\n' e '\0' */
	char *EndPtr;		 /**< Buffer per caratteri non consentiti */
	int  Success;		 /**< Flag con valore 0 in caso di errore, 1 altrimenti*/
	
	Success = 1;
	errno = 0;
	
	fgets(TempBuffer, sizeof(TempBuffer), stdin);
	
	/* strtol expects nptr to point to a string of the following form:
	 * [whitespace] [{+ | –}] [0 [{ x | X }]] [digits]
	 * http://msdn.microsoft.com/en-us/library/w4z2wdyc%28v=vs.71%29.aspx 
	 */
	*Value = strtol(TempBuffer, &EndPtr, 10);
	
	//Valore non valido: troppo grande, troppo piccolo oppure stringa
	if( (EndPtr == TempBuffer) || (errno == ERANGE) )
	{
		Success = 0;
	}
	return Success;
}

/**
 * Visualizza un menu per la scelta delle operazioni da effettuare
 *
 * @return L'identificativo dell'operazione da effettuare
 *
 */
char Menu()
{
	char Choice; /**< Voce del menu scelta */
	printf("=================================================\n");
	puts("Lista di interi - Menu");
	printf("=================================================\n");
	puts("1 - Inserire un numero nella lista.");
	puts("2 - Eliminare un numero dalla lista.");
	puts("3 - Eliminare tutti i numeri dalla lista.");
	puts("4 - Inserire dei numeri casuali.");
	puts("9 - Stampa la lista a video.");
	puts("0 - Esci");
	puts("Operazione da effettuare? ");
	printf("?>");
	fflush(stdin);
	Choice = _getch();
	
	return Choice;
}

/**
 * Mette il programma in attesa di un singolo input utente
 *
 */
void Pause()
{
	puts("\n\nPremere un tasto per continuare...");
	_getch();
}


