#include <stdlib.h>
#include "lista.h"

void List_Init(LIST *L, OPERATIONS *Op)
{
	L->Head = NULL;
	L->Op = Op;
}

int List_IsEmpty(LIST *L)
{
	return L->Head == NULL;
}	

int List_Insert( void *Value, LIST *L )
{
	int Status;

	L->Head = List_RecursiveOrderedInsert( Value, L->Head, &Status, L->Op );

	return Status;
}

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
			//Esiste già un nodo con pari campo nella lista
            Op->DuplicateNode();
			*ReturnStatus = E_MALLOC;
		}
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
		Current->Next = List_RecursiveOrderedInsert(Value, Current->Next, ReturnStatus, Op);
	}
	return Current;
}


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


int List_Delete( void *Value, LIST *L )
{
	int Status;

	L->Head = List_RecursiveDelete( Value, L->Head, &Status, L->Op );
    //Rende coerente la funzione con il resto della libreria restituendo
	//0 in caso di successo, -1 altrimenti
	return (Status == I_REMOVED ? 0 : -1);
}

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
			Op->DeleteNode( Current->Info );
			
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

NODE *List_RecursiveDeleteRange( NODE *Current, void *Inf, void *Sup, OPERATIONS *Op )
{
	NODE *Temp;

    //Se la lista non è vuota oppure il limite inferiore è maggiore del limite superiore
	//non fare nulla
	if( (Current != NULL) || (Op->Compare(Inf, Sup) > 0)  )
	{
		if( Op->Compare(Current->Info, Sup) <= 0 )
		{
			Current->Next = List_RecursiveDeleteRange( Current->Next, Inf, Sup, Op );
			if( Op->Compare(Current->Info, Inf) >= 0 )
			{
				Temp = Current->Next;
				Op->DeleteNode(Current->Info);
				free(Current);
				Current = Temp;
			}
		}
	}
	return Current;
}


NODE *List_RecursiveDestroy(NODE *Current, OPERATIONS *Op)
{
    if( Current != NULL )
	{
		/* scorre la lista fino all'ultimo ed effettua la cancellazione
		 * in ordine inversa */
		Current->Next = List_RecursiveDestroy(Current->Next, Op);
		Op->DeleteNode(Current->Info);
		free(Current);
		Current = NULL;
	}
	return Current;
}
/**
 * STAMPA
 * */
int List_Print( LIST *L )
{
	List_RecursivePrint( L->Head, L->Op );
	return 0;
}
void List_RecursivePrint( NODE *Current, OPERATIONS *Op )
{
    /* stampa la lista, se non vuota */
	if( Current != NULL )
	{
		Op->Print(Current->Info);
		List_RecursivePrint(Current->Next, Op);
	}
}
