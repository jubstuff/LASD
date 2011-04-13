/**
 * lista.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 05/04/11
 * @package ListaGenerale
 *
 * Implementazioni delle funzioni per la gestione di una lista.
 * 
 */
 
#include "lista.h"

/*==============================================================================
 * Funzioni per la gestione della lista
 *============================================================================*/

int ListIsEmpty(LIST *L)
{
	return L->Head == NULL;
}

NODO *ListCreateNewNode(void *Value, OPERATIONS *Op)
{
	NODO * NewNode;

	//Alloca spazio per il nuovo nodo
	NewNode = (NODO *) malloc(sizeof(NODO));
	if ( NewNode != NULL )
	{
		//Associa il valore passato dall'utente al campo del nodo
		NewNode->Info = Op->Initialize(Value);
		NewNode->Next = NULL;
	}
	return NewNode;
}

NODO *ListInsertBefore( void *Value, NODO *Current, OPERATIONS *Op )
{
	NODO *NewNode;

	/*alloca e inizializza il nuovo nodo*/
	NewNode = ListCreateNewNode( Value, Op );
	if ( NewNode != NULL )
	{
		//Posiziona il nuovo nodo prima del nodo corrente
		NewNode->Next = Current;
		Current = NewNode;
	}
	return NewNode;
}
/**
 * Inserisce un nodo all'interno della lista
 *
 * Questa funzione utilizza un approccio ricorsivo per inserire un nodo
 * con campo <Value> all'interno della lista <Current>.
 * 
 * NOTE Se un nodo con campo pari a <Value> è già esistente, la lista
 * non viene modificata
 * 
 * @param Value        Valore da inserire nel nodo.
 * @param Current      Testa della lista in cui inserire il nodo.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *	                   - 0, in caso di inserimento corretto
 *                     - E_MALLOC, in caso di errore nella creazione del nodo
 *                     - W_DUPLICATE, in caso di valore già presente in lista
 *
 * @return Il puntatore alla testa della lista eventualmente modificato
 */ 
NODO *ListRecursiveOrderedInsert ( void *Value, NODO *Current, int *ReturnStatus, OPERATIONS *Op ) 
{
	//NODO *NewNode; /**< puntatore al nuovo nodo creato */
	
	*ReturnStatus = 0; 
	
	/*se la lista è vuota oppure il nodo è maggiore, inserisci un nuovo nodo */
	if( Current == NULL || ( Op->Compare( (void *)Current->Info, (void *)Value ) > 0 ) )
	{
		Current = ListInsertBefore( Value, Current, Op );
	}   
	/* se il valore del nodo corrente è uguale a quello in ingresso, non
	 * fare nulla, ma notifica la condizione tramite ReturnStatus */
	else if( ( Op->Compare( (void *)Current->Info, (void *)Value ) == 0 )  )
	{
		*ReturnStatus = W_DUPLICATE;
	}
	else
	{
		// vai avanti nella ricerca, aggiornando il campo Next del nodo corrente 
		Current->Next = ListOrderedInsert(Value, Current->Next, ReturnStatus, Op);
	}
	return Current;
}

void ListOrderedInsert( void *Value, LIST *L, OPERATIONS *Op)
{
	int ReturnStatus = 0;
	L->Head = ListRecursiveOrderedInsert(Value, L->Head, &ReturnStatus, Op);
	L->NumElements++;
}

NODO *ListFreeNode( NODO *Current, OPERATIONS *Op ) 
{
    NODO *Temp; /**< Nodo di appoggio per cancellazione */

	Temp = Current->Next;
	//Dealloca il campo chiave del nodo
	Op->Destroy( Current->Info );

	//Libera memoria per il nodo
	free( Current );
	return Temp;
}
/**
 * Rimuove un nodo dalla lista
 *
 * Questa funzione utilizza un approccio ricorsivo per rimuovere un nodo
 * con campo <Value> dalla lista <Current>.
 * 
 * NOTE Se un nodo con campo pari a <Value> non esiste, la lista
 * non viene modificata
 * 
 * @param Value   Valore associata al nodo da rimuovere.
 * @param Current Testa della lista da cui rimuovere il nodo.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *                     - I_FOUND, in caso di nodo trovato e rimosso
 *
 * @return Il puntatore alla testa della lista eventualmente modificato
 */
NODO *ListRemove(void *Value, NODO *Current, int *ReturnStatus, OPERATIONS *Op) 
{
    NODO *Temp; /**< Nodo di appoggio per cancellazione */
    
	/* cerca il nodo solo se la lista non è vuota */
	if( Current != NULL )
    {
        /* se il nodo corrente è quello cercato, cancellalo */
		if( Op->Compare( (void *)Current->Info, (void *)Value ) == 0 )
		{
			Temp = Current->Next;
			//Dealloca il campo chiave del nodo
			Op->Destroy( Current->Info );
			
			//Libera memoria per il nodo
   			free( Current );
			Current = Temp;
			*ReturnStatus = I_FOUND; //Nodo trovato e rimosso
		}
		/* altrimenti prosegui la ricerca */
		else
		{
			Current->Next = ListRemove( Value, Current->Next, ReturnStatus, Op );
		}
	} 
	return Current;
}
/**
 * Dealloca tutti i nodi della lista
 *
 * @param Current Testa della lista da deallocare.
 *
 * @return Il puntatore alla testa eventualmente modificato.
 */
NODO * ListDeallocate(NODO *Current, OPERATIONS *Op)
{
    if( Current != NULL )
	{
		/* scorre la lista fino all'ultimo ed effettua la cancellazione
		 * in ordine inversa */
		Current->Next = ListDeallocate(Current->Next, Op);
		/*free( Current->Info );
		free( Current );*/
		Current = ListRemove(Current->Info, Current, NULL, Op);
		Current = NULL;
	}
	return Current;
}
/**
 * Stampa i campi della lista, in ordine
 *
 * @param Current Testa della lista da stampare a video.
 */
void ListPrint( NODO *Current, OPERATIONS *Op )
{
    /* stampa la lista, se non vuota */
	if( Current != NULL )
	{
		Op->Print(Current->Info);
		ListPrint(Current->Next, Op);
	}
}

#ifdef ASDRUBALE
/*==============================================================================
 * Funzioni di File I/O per la lista
 *============================================================================*/

/**
 * Scrive la lista di stringhe su file.
 *
 * Il file generato è in formato testuale per garantirne la portabilità ed è 
 * formattato in questo modo:
 * 
 * StringaNodo1
 * StringaNodo2
 * StringaNodo3
 *
 * @param NomeFile     Nome del file in cui salvare la lista.
 * @param Head         Testa della lista da salvare.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *	                   - 0, in caso di inserimento corretto
 *                     - E_FOPEN, in caso di errore all'apertura del file
 *                     - E_FCLOSE, in caso di errore alla chiusura del file
 *
 */
void ScriviSuFileDiTesto( char *NomeFile, NODO *Head, int *ReturnStatus )
{
	FILE *Fp; /**< Puntatore al file su cui scrivere */
	
	//inizializzazione variabili e parametri
	Fp            = NULL;
	*ReturnStatus = 0;
	
	Fp = fopen(NomeFile, "w");
	if( Fp == NULL )
	{
		*ReturnStatus = E_FOPEN; //errore apertura file
	}
	//File aperto, effettua l'operazione di scrittura
	else
	{
		//Finché ci sono nodi, scrivi la stringa sul file
		while(Head != NULL) {
			fprintf(Fp, "%s\n", Head->Info);
			Head = Head->Next;
		}
	}
	
	if( fclose(Fp) == EOF )
	{
		*ReturnStatus = E_FCLOSE; //errore chiusura del file
	}
}

/**
 * Legge una serie di stringhe da un file, salvandole in una lista concatenata.
 * 
 * Legge un file nel formato:
 * 
 * Stringa1
 * Stringa2
 * Stringa3
 *
 * creando un nodo per ogni stringa, e restituendo la testa della lista creata.
 *
 * @param NomeFile     Nome del file da cui leggere le stringhe.
 * @param Lenmax       Lunghezza massima della riga (in lettura).
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *	                   - 0, in caso di inserimento corretto
 *                     - E_FOPEN, in caso di errore all'apertura del file
 *                     - E_FCLOSE, in caso di errore alla chiusura del file
 *                     - E_MALLOC, in caso di errore nella creazione del nodo
 *
 * @return La testa della lista creata dalla lettura del file
 */

NODO *CaricaListaDaFile ( char *NomeFile, int LenMax, int *ReturnStatus )
{
	NODO *TempHead;    /**< Testa della lista temporanea */
	FILE *Fp;          /**< Puntatore al file da cui leggere */
	char *TempBuffer;  /**< Buffer temporaneo per le stringhe */
	
	//inizializzazione variabili e parametri
	Fp            = NULL;
	TempHead      = NULL;
	*ReturnStatus = 0;
	
	//alloca spazio necessario per memorizzare una riga del file
	TempBuffer = (char *) malloc( (LenMax+1) * sizeof(char) );
	if ( TempBuffer == NULL )
	{
		*ReturnStatus = E_MALLOC; //Errore allocazione buffer temporaneo
	}
	else
	{
		Fp = fopen(NomeFile, "r");
		if( Fp == NULL )
		{
			*ReturnStatus = E_FOPEN; //Errore apertura file
		}
		//File aperto: leggi dal file
		else
		{
			//Leggi il file riga per riga, ricostruendo la lista
			//NOTA: se il Fp non è un descrittore valido, fgets ritorna NULL
			while( fgets(TempBuffer, LenMax, Fp) != NULL )
			{
				TempBuffer[strlen(TempBuffer) - 1] = '\0';
				TempHead = ListInsert(TempBuffer, TempHead, ReturnStatus);
			}
			
			if( fclose(Fp) == EOF )
			{
				*ReturnStatus = E_FCLOSE; //errore chiusura file
			}
		}
		//Libera la memoria allocata
		free(TempBuffer);
	}
	
	return TempHead;
}
#endif
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
void LeggiStringa( char *Buf, int LenMax, FILE *InputStream)
{
	fgets(Buf, LenMax, stdin);
	fflush(stdin);
	while ( *Buf < 0 || *Buf > 31) 
	{
		Buf++;
	}
	*Buf = '\0';
}
#ifdef ASDRUBALE
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
	puts("Lista di Stringhe - Menu");
	printf("=================================================\n");
	puts("1 - Inserisci una stringa nella lista.");
	puts("2 - Eliminare una stringa dalla lista.");
	puts("3 - Eliminare tutti i nodi dalla lista.");
	puts("4 - Salva la lista su file.");
	puts("5 - Caricare la lista da file.");
	puts("9 - Stampa la lista a video.");
	puts("0 - Esci");
	puts("Operazione da effettuare: ");
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
	puts("\n\nBattere un tasto per continuare...");
	_getch();
}
#endif

