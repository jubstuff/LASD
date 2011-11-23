/**
 * lista.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/10/11
 *
 * Implementazioni delle funzioni per la gestione di una lista a concatenazione
 * singola
 *
 * */
#include <stdlib.h>
#include "lista.h"
#include "mem.h"

/*=============================================================================*
 * Definizioni struttura nodo
 =============================================================================*/
struct node_tag {
	NODE *Next; /**< Puntatore al nodo successivo */
	void *Info;        /**< Campo del nodo */
};

struct list_tag
{
	NODE *Head;
	JLIST_METHODS *Op;
};


/**
 * DEFINIZIONE METODI PRIVATI
 * */
static NODE *List_RecursiveOrderedInsert ( void *Value, NODE *Current, J_STATUS *ReturnStatus, JLIST_METHODS *Op );
static NODE *ListCreateNewNode(void *Value, JLIST_METHODS *Op);
static NODE *List_RecursiveDelete(void *Value, NODE *Current, J_STATUS *ReturnStatus, JLIST_METHODS *Op);
static void List_RecursivePrint( NODE *Current, JLIST_METHODS *Op );
static NODE *List_RecursiveDestroy(NODE *Current, JLIST_METHODS *Op);
static NODE *List_RecursiveDeleteRange( NODE *Current, void *Inf, void *Sup, JLIST_METHODS *Op );
static NODE *List_RecursiveSearch( void *Value, NODE *Current, J_STATUS *ReturnStatus, JLIST_METHODS *Op);

/**
 * Inizializza una lista con i relativi metodi.
 *
 * */
J_STATUS JList_Init( J_LIST **L, JLIST_METHODS *Op )
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    ReturnStatus = MemAlloc(sizeof(J_LIST), (void **)L);

    if( ReturnStatus == SUCCESS )
    {
        /* Inizializzo la testa della lista e i relativi metodi */
        (*L)->Head = NULL;
        ReturnStatus = MemAlloc(sizeof(JLIST_METHODS), (void **)&((*L)->Op) );
        if( ReturnStatus == SUCCESS )
        {
            /* Copia i membri della struct Op passata in input
             * nella struct Op appena allocata */
            *((*L)->Op) = *Op;
        }
        else
        {
            /* TODO deallocare lista */
        }
    }

    return ReturnStatus;
}
int JList_isEmpty( J_LIST *L )
{
    return L->Head == NULL;
}

/**
 * Inserisce Value in lista, rispettando la relazione d'ordine definito nel COMPARATOR
 *
 * Necessita dei metodi
 * COMPARATOR
 * INITIALIZER
 * DUPLICATE
 * */
J_STATUS JList_OrderedInsert( void *Value, J_LIST *L )
{
    J_STATUS ReturnStatus;

    L->Head = List_RecursiveOrderedInsert( Value, L->Head, &ReturnStatus, L->Op );
    return ReturnStatus;
}

/**
 * Inserisce un nodo in testa alla lista
 *
 * Necessita dei metodi:
 * INITIALIZER
 * */
J_STATUS JList_HeadInsert( void *Value, J_LIST *L )
{
    J_STATUS ReturnStatus;
    NODE *NewNode;

    ReturnStatus = SUCCESS;

    /*alloca e inizializza il nuovo nodo*/
    NewNode = ListCreateNewNode( Value, L->Op );
    if ( NewNode != NULL )
    {
        /* Posiziona il nuovo nodo prima del nodo corrente */
        NewNode->Next = L->Head;
        L->Head = NewNode;
    }
    else 
    {   
        ReturnStatus = E_NO_MEM;
    }

    return ReturnStatus;
}

/**
 * Rimuove un nodo dalla testa della lista.
 *
 * Necessita dei metodi:
 *
 * GETTER
 * DELETER
 *
 * */
J_STATUS JList_HeadDelete( void *Value, J_LIST *L )
{
    J_STATUS ReturnStatus;
    NODE *Temp;

    ReturnStatus = SUCCESS;

    if( L->Head != NULL )
    {
        /* Se la lista non è vuota, elimina il nodo in testa */
        L->Op->GetNodeValue( L->Head->Info, Value );
        /* Aggiorno la testa della lista al secondo elemento */
        Temp = L->Head;
        L->Head = L->Head->Next;
        /* Dealloca il campo chiave del nodo */
        L->Op->Delete( Value, Temp->Info );

        /* Libera memoria per il nodo */
        free( Temp );
        ReturnStatus = SUCCESS; /* Nodo trovato e rimosso */
    }
    else
    {
        /* Lista vuota */
        ReturnStatus = ERROR;
    }

    return ReturnStatus;
}

/**
 * Elimina un nodo contenente Value dalla lista
 *
 * Necessita dei metodi:
 * COMPARATOR
 * DELETER
 * */
J_STATUS JList_DeleteNode( void *Value, J_LIST *L )
{
    J_STATUS ReturnStatus;

    L->Head = List_RecursiveDelete( Value, L->Head, &ReturnStatus, L->Op);

    return ReturnStatus;
}

/**
 * Elimina i nodi compresi nell'intervallo [Inf, Sup] da una lista ordinata
 *
 * Necessita dei metodi:
 * COMPARATOR
 * DELETER
 *
 * =NOTA=
 * Il comportamento di questa funzione è indefinito, se applicato a liste non ordinate
 *
 * */
void JList_DeleteRange( void *Inf, void  *Sup, J_LIST *L )
{
    L->Head = List_RecursiveDeleteRange( L->Head, Inf, Sup, L->Op );
}

/* 
 * Stampa la lista
 *
 * Necessita dei metodi:
 * PRINTER
 *
 * */
void JList_Print( J_LIST *L )
{
    List_RecursivePrint( L->Head, L->Op );
}

/**
 * Dealloca l'intera lista
 *
 * Necessita dei metodi:
 * DELETER
 * */
void JList_Destroy( J_LIST *L )
{
    L->Head = List_RecursiveDestroy(L->Head, L->Op);
    MemFree( (void **)&(L->Op) );
    MemFree( (void **)&L );
}

J_STATUS JList_Search( void *Value, J_LIST *L, NODE **NodeFound )
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    *NodeFound = List_RecursiveSearch( Value, L->Head, &ReturnStatus, L->Op);
    
    return ReturnStatus;
}

void *JNode_GetData( NODE *N )
{
    return N->Info;
}

/*********************************************************************************
 * IMPLEMENTAZIONE METODI PRIVATI                                                *
 *                                                                               *
 *********************************************************************************/

static NODE *List_RecursiveSearch( void *Value, NODE *Current, J_STATUS *ReturnStatus, JLIST_METHODS *Op)
{
    *ReturnStatus = W_LIST_NOTFOUND;

	/* cerca il nodo solo se la lista non è vuota */
	if( Current != NULL )
    {
        /* se il nodo corrente è quello cercato */
		if( Op->Compare( Current->Info, Value ) == 0 )
		{
            /* Esegui operazioni sul nodo */
			*ReturnStatus = SUCCESS; 
		}
		/* altrimenti prosegui la ricerca */
		else
		{
			List_RecursiveDelete( Value, Current->Next, ReturnStatus, Op );
		}
	} 
	return Current;
}

/**
 * Inserisce un nodo all'interno della lista
 *
 * Questa funzione utilizza un approccio ricorsivo per inserire un nodo
 * con campo <Value> all'interno della lista <Current>.
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
static NODE *List_RecursiveOrderedInsert ( void *Value, NODE *Current, J_STATUS *ReturnStatus, JLIST_METHODS *Op ) 
{
	NODE *NewNode;
	*ReturnStatus = SUCCESS; 
	
	/*se la lista è vuota oppure il nodo è maggiore, inserisci un nuovo nodo */
	if( Current == NULL || ( Op->Compare( Current->Info, Value ) > 0 ) )
	{
		/*alloca e inizializza il nuovo nodo*/
		NewNode = ListCreateNewNode( Value, Op );
		if ( NewNode != NULL )
		{
			/* Posiziona il nuovo nodo prima del nodo corrente */
			NewNode->Next = Current;
			Current = NewNode;
		}
		else 
		{   
			*ReturnStatus = E_NO_MEM;
		}
	}   
	/* se il valore del nodo corrente è uguale a quello in ingresso
	 * notifica la condizione tramite ReturnStatus */
	else if( ( Op->Compare( (void *)Current->Info, (void *)Value ) == 0 )  )
	{
		/* Esiste già un nodo con pari campo nella lista */
		Op->ManageDuplicate( Value, Current );
		*ReturnStatus = W_LIST_DUP;
	}
	else
	{
		/* vai avanti nella ricerca, aggiornando il campo Next del nodo corrente */
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
static NODE *ListCreateNewNode(void *Value, JLIST_METHODS *Op)
{
	NODE * NewNode;
	J_STATUS Status;

	/* Alloca spazio per il nuovo nodo */
	Status = MemAlloc(sizeof(NODE), (void **)&NewNode);
	if( Status == SUCCESS )
    {
		/* Associa il valore passato dall'utente al campo del nodo */
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
 *                     - SUCCESS, in caso di nodo trovato e rimosso
 *                     - W_LIST_NOTFOUND, in caso di nodo non trovato
 * @param Op           Riferimento al record contenente le operazioni di manipolazione
 *                     dei nodi.
 *
 * @return Il puntatore alla testa della lista, eventualmente modificato
 */
static NODE *List_RecursiveDelete(void *Value, NODE *Current, J_STATUS *ReturnStatus, JLIST_METHODS *Op) 
{
    NODE *Temp; /**< Nodo di appoggio per cancellazione */
    
    *ReturnStatus = W_LIST_NOTFOUND;

	/* cerca il nodo solo se la lista non è vuota */
	if( Current != NULL )
    {
        /* se il nodo corrente è quello cercato, cancellalo */
		if( Op->Compare( Current->Info, Value ) == 0 )
		{
			Temp = Current->Next;
			/* Dealloca il campo chiave del nodo */
			Op->Delete( Value, Current->Info );
			
			/* Libera memoria per il nodo */
   			free( Current );
			Current = Temp;
			*ReturnStatus = SUCCESS; /* Nodo trovato e rimosso */
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
static NODE *List_RecursiveDeleteRange( NODE *Current, void *Inf, void *Sup, JLIST_METHODS *Op )
{
	NODE *Temp;

    /* Se la lista non è vuota oppure il limite inferiore è maggiore del limite superiore
	 * non fare nulla */
	if( (Current != NULL) || (Op->Compare(Inf, Sup) > 0)  )
	{
		/* Scorri la lista fino al nodo che supera il limite superiore */
		if( Op->Compare(Current->Info, Sup) <= 0 )
		{
			Current->Next = List_RecursiveDeleteRange( Current->Next, Inf, Sup, Op );
			/* Cancella i nodi finché sono maggiori del limite inferiore */
			if( Op->Compare(Current->Info, Inf) >= 0 )
			{
				Temp = Current->Next;
				Op->Delete( Current->Info, Current->Info);
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
static NODE *List_RecursiveDestroy(NODE *Current, JLIST_METHODS *Op)
{
    if( Current != NULL )
	{
		/* scorre la lista fino all'ultimo ed effettua la cancellazione
		 * in ordine inverso */
		Current->Next = List_RecursiveDestroy(Current->Next, Op);
		Op->Delete( Current->Info, Current->Info);
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
static void List_RecursivePrint( NODE *Current, JLIST_METHODS *Op )
{
    /* stampa la lista, se non vuota */
	if( Current != NULL )
	{
		Op->Print(Current->Info);
		List_RecursivePrint(Current->Next, Op);
	}
}
