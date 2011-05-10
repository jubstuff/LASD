#include <stdlib.h>
#include "lista.h"



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
 * @param Op           Riferimento al record contenente le operazioni di manipolazione
 *                     dei nodi.
 *
 * @return Il puntatore alla testa della lista, eventualmente modificato
 */ 
NODE *List_RecursiveOrderedInsert ( void *Value, NODE *Current, int *ReturnStatus, OPERATIONS *Op ) 
{
	NODE *NewNode;
	*ReturnStatus = 0; 
	
	/*se la lista è vuota oppure il nodo è maggiore, inserisci un nuovo nodo */
	if( Current == NULL || ( Op->Compare( Current->Info, Value ) > 0 ) )
	{
		/*alloca e inizializza il nuovo nodo*/
		NewNode = ListCreateNewNode( Value, Op );
		if ( NewNode != NULL )
		{
			//Posiziona il nuovo nodo prima del nodo corrente
			NewNode->Next = Current;
			Current = NewNode;
		}
		else 
		{   
			*ReturnStatus = E_MALLOC;
		}
	}   
	/* se il valore del nodo corrente è uguale a quello in ingresso, non
	 * fare nulla, ma notifica la condizione tramite ReturnStatus */
	else if( ( Op->Compare( (void *)Current->Info, (void *)Value ) == 0 )  )
	{
		//Esiste già un nodo con pari campo nella lista
		Op->ManageDuplicate( Value, Current );
		*ReturnStatus = W_DUPLICATE;
	}
	else
	{
		// vai avanti nella ricerca, aggiornando il campo Next del nodo corrente 
		Current->Next = List_RecursiveOrderedInsert(Value, Current->Next, ReturnStatus, Op);
	}
	return Current;
}


/**
 * Alloca un nuovo nodo, con relativo campo
 *
 * @param Value Valore da inserire nel nodo
 * @param Op    Riferimento al record contenente le operazioni di manipolazione
 *              dei nodi.
 *
 * @return Il riferimento al nuovo nodo creato, oppure NULL in caso di fallimento
 *         nell'allocazione
 * */ 
NODE *ListCreateNewNode(void *Value, OPERATIONS *Op)
{
	NODE * NewNode;

	//Alloca spazio per il nuovo nodo
	NewNode = (NODE *) malloc(sizeof(NODE));
	if ( NewNode != NULL )
	{
		//Associa il valore passato dall'utente al campo del nodo
		NewNode->Info = Op->InitNode(Value);
		NewNode->Next = NULL;
	}
	return NewNode;
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
 * @param Value        Valore associata al nodo da rimuovere.
 * @param Current      Testa della lista da cui rimuovere il nodo.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *                     - I_REMOVED, in caso di nodo trovato e rimosso
 * @param Op           Riferimento al record contenente le operazioni di manipolazione
 *                     dei nodi.
 *
 * @return Il puntatore alla testa della lista, eventualmente modificato
 */
NODE *List_RecursiveDelete(void *Value, NODE *Current, int *ReturnStatus, OPERATIONS *Op) 
{
    NODE *Temp; /**< Nodo di appoggio per cancellazione */
    
	/* cerca il nodo solo se la lista non è vuota */
	if( Current != NULL )
    {
        /* se il nodo corrente è quello cercato, cancellalo */
		if( Op->Compare( Current->Info, Value ) == 0 )
		{
			Temp = Current->Next;
			//Dealloca il campo chiave del nodo
			Op->DeleteNode( Value, Current->Info );
			
			//Libera memoria per il nodo
   			free( Current );
			Current = Temp;
			*ReturnStatus = I_REMOVED; //Nodo trovato e rimosso
		}
		/* altrimenti prosegui la ricerca */
		else
		{
			Current->Next = List_RecursiveDelete( Value, Current->Next, ReturnStatus, Op );
		}
	} 
	return Current;
}

/**
 * Cancella i nodi compresi in un intervallo
 *
 * Permette di cancellare tutti i nodi i cui campi sono compresi tra Inf e Sup,
 * estremi compresi.
 * Si assume Inf < Sup (secondo la relazione di ordinamento applicabile). In caso
 * contrario, la funzione non modifica la lista.
 *
 * @param Current Testa della lista da cui rimuovere i nodi.
 * @param Inf     Estremo inferiore dell'intervallo.
 * @param Sup     Estremo superiore dell'intervallo.
 * @param Op      Riferimento al record contenente le operazioni di manipolazione
 *                dei nodi.
 *
 * @return Il puntatore alla testa della lista, eventualmente modificato
 * */
NODE *List_RecursiveDeleteRange( NODE *Current, void *Inf, void *Sup, OPERATIONS *Op )
{
	NODE *Temp;

    //Se la lista non è vuota oppure il limite inferiore è maggiore del limite superiore
	//non fare nulla
	if( (Current != NULL) || (Op->Compare(Inf, Sup) > 0)  )
	{
		//Scorri la lista fino al nodo che supera il limite superiore
		if( Op->Compare(Current->Info, Sup) <= 0 )
		{
			Current->Next = List_RecursiveDeleteRange( Current->Next, Inf, Sup, Op );
			//Cancella i nodi finché sono maggiori del limite inferiore
			if( Op->Compare(Current->Info, Inf) >= 0 )
			{
				Temp = Current->Next;
				Op->DeleteNode( Current->Info, Current->Info);
				free(Current);
				Current = Temp;
			}
		}
	}
	return Current;
}


/**
 * Dealloca tutti i nodi della lista
 *
 * @param Current Testa della lista da deallocare.
 * @param Op      Riferimento al record contenente le operazioni di manipolazione
 *                dei nodi.
 *
 * @return Il puntatore alla testa eventualmente modificato.
 */
NODE *List_RecursiveDestroy(NODE *Current, OPERATIONS *Op)
{
    if( Current != NULL )
	{
		/* scorre la lista fino all'ultimo ed effettua la cancellazione
		 * in ordine inverso */
		Current->Next = List_RecursiveDestroy(Current->Next, Op);
		Op->DeleteNode( Current->Info, Current->Info);
		free(Current);
		Current = NULL;
	}
	return Current;
}

/**
 * Stampa i campi della lista, in ordine
 *
 * Questa funzione utilizza un approccio ricorsivo per scorrere la lista e
 * stampare a video tutti i campi dei nodi, in ordine.
 * La procedura per stampare i nodi è memorizzata in <Op>.
 *
 * @param Current Testa della lista da stampare a video.
 * @param Op      Riferimento al record contenente le operazioni di manipolazione
 *                dei nodi.
 *
 */
void List_RecursivePrint( NODE *Current, OPERATIONS *Op )
{
    /* stampa la lista, se non vuota */
	if( Current != NULL )
	{
		Op->Print(Current->Info);
		List_RecursivePrint(Current->Next, Op);
	}
}
