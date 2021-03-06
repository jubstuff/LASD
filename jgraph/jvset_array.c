#include "jvset.h"
#include "lista.h"
#include "mem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*============================DEFINIZIONE STRUTTURE==============================*/

/**
 * Implementazione dell'interfaccia J_VSET utilizzando un array
 *
 * */


/*=======================FINE DEFINIZIONE STRUTTURE==============================*/

/*=======================DEFINIZIONE METODI PRIVATI==============================*/

/* Metodi privati dell'insieme dei vertici */
static int JVset_IsMember(char *Label, J_VSET *Set);
static J_STATUS JVset_FindVertexIndexByLabel( char *Label, int *Index, J_VSET *Set );
static void JVset_InitializeVerticesAndFreeList( int OldSize, J_VSET *Set );
static int CalculateVertexID(char *Label);
/* Metodi per la gestione della FreeList */
static void *InizializzaNodoInt( void *Value );
static void DeallocaInt( void *InputValue, void *NodeInfo );
static int NumCmp( const void *Num1, const void *Num2 );
static void RecuperaInt( const void *NodeValue, void *OutValue );

/*============================FINE METODI PRIVATI================================*/


/*============================METODI PUBBLICI=====================================*/

/* Metodi per l'insieme dei vertici */


/**
 * Alloca e inizializza l'insieme dei vertici.
 *
 * Questa funzione alloca un nuovo insieme dei vertici ed inizializza tutti i 
 * suoi membri.
 * Prende in ingresso una stima del numero di vertici che saranno inseriti
 * nell'insieme. 
 * Dopo aver allocato l'insieme, alloca la FreeList e inserisce in testa tutti gli
 * indici delle locazioni disponibili (all'atto dell'inizializzazione sono tutte
 * libere).
 *
 * @param HintNumVertices Stima del numero di vertici da inserire nell'insieme
 * @param Set             Indirizzo del puntatore dell'insieme da inizializzare
 *
 * @return Lo stato dell'operazione
 * */
J_STATUS JVset_Init( int HintNumVertices, J_VSET **Set )
{
    J_STATUS ReturnStatus;
    JLIST_METHODS Op; /**< Metodi necessari per FreeList */

    ReturnStatus = SUCCESS;

    /* Alloco la struct che rappresenta l'insieme */
    ReturnStatus = MemAlloc(sizeof(J_VSET), (void **)Set);

    if( ReturnStatus == SUCCESS )
    {
        /* Se l'insieme è stato correttamente allocato */

        /* Inizializza la struct con le operazioni per la FreeList */
        Op.Compare = NumCmp;
        Op.InitNode = InizializzaNodoInt;
        Op.Delete = DeallocaInt;
        Op.GetNodeValue = RecuperaInt;

        /* Inizializza la FreeList */
        ReturnStatus = JList_Init(&(*Set)->FreeList, &Op);
        if( ReturnStatus == SUCCESS )
        {
            /* se la Freelist è stata allocata correttamente */

            /* inizializzo gli indici */
            (*Set)->NumActiveVertices = 0;
            (*Set)->Size = HintNumVertices;

            /* alloco l'array di puntatori ai vertici */
            ReturnStatus = MemAlloc( (*Set)->Size * sizeof(J_VERTEX *), 
                    (void **)&( (*Set)->Vertices ) );
            if( ReturnStatus == SUCCESS )
            {
                /* Se l'array di puntatori a vertici è stato correttamente
                 * allocato, inizializza la freelist con tutte le locazioni
                 * disponibili
                 * */
                JVset_InitializeVerticesAndFreeList( 0, (*Set) );
            }
            else
            {
                /* se l'array di puntatori a vertici non è stato allocato */

                /* dealloca Freelist */
                JList_Destroy( (*Set)->FreeList );
                /* dealloca insieme dei vertici */
                MemFree( (void **)&Set );
            }
        }
        else
        {
            /* se la Freelist non è stata allocata */

            /* deallocare l'insieme dei vertici */
            MemFree( (void **)&Set );
        }
    }

    return ReturnStatus;
}

/**
 * Dealloca l'insieme di vertici.
 *
 * Questa funzione dealloca tutti gli elementi dell'insieme dei vertici:
 * dapprima tutti i vertici, poi la FreeList, quindi l'array contenente i
 * puntatori ai vertici ed infine l'insieme stesso.
 *
 * @param Set L'insieme da deallocare
 *
 * */
void JVset_Destroy( J_VSET *Set )
{
    int i;

    for( i = 0; i < Set->Size; i++ )
    {
        /* Elimina tutti i vertici dall'insieme */
        JVertex_Destroy( Set->Vertices[i] );
    }
    /* Dealloca la freelist */
    JList_Destroy( Set->FreeList );
    /* Dealloca l'insieme */
    MemFree( (void **)&( Set->Vertices ) );
    MemFree( (void **)&Set );
}

/**
 * Aggiunge un vertice con etichetta Label e dati associati all'insieme
 *
 * Questa funzione aggiunge un vertice all'insieme e, se necessario, aumenta la
 * dimensione dell'insieme per ospitare il nuovo vertice.
 * Infatti, se i vertici inseriti non hanno saturato l'insieme, questa funzione
 * recupera il prossimo indice disponibile per l'inserimento dalla FreeList ed
 * alloca un nuovo vertice in quella posizione.
 * Se invece non sono più disponibili locazioni per l'inserimento, l'array
 * contenente i vertici viene reallocato (utilizzando il doppio della dimensione
 * attuale) e la funzione viene richiamata ricorsivamente per procedere
 * all'inserimento nell'insieme ingrandito.
 *
 * @param Label Etichetta da associare al vertice
 * @param Data  Dati da associare al vertice
 * @param Set   Insieme dei vertici
 *
 * @return Esito dell'operazione
 *
 * */
J_STATUS JVset_AddVertex( char *Label, void *Data, J_VSET *Set )
{
    int FreeLoc;           /**< Locazione libera in cui inserire */
    J_STATUS ReturnStatus; /**< Valore di ritorno */
    int OldSize;           /**< Dim precedente dell'insieme */
    int Trovato;

    /* Controllo se esiste già un vertice con l'etichetta passata in input */
    Trovato = JVset_IsMember(Label, Set);

    if( Trovato == 0 )
    {
        if( JList_isEmpty( Set->FreeList ) )
        {
#ifdef DEBUG
            fprintf(stderr, "[JVSET: Esaurite locazioni disponibili. Realloco l'insieme dei vertici]\n");
#endif
            OldSize = Set->Size;
            /* raddoppio la dimensione dell'insieme */
            Set->Size = 2 * Set->Size;
            /* realloco l'insieme dei vertici */
            ReturnStatus = MemRealloc( Set->Size * sizeof(J_VERTEX *), 
                (void **)&( Set->Vertices ));
            if( ReturnStatus == SUCCESS )
            {
                JVset_InitializeVerticesAndFreeList( OldSize, Set );
            }
        }
        /* Se la Freelist non è vuota, recupera il primo elemento
         * ed inserisci il vertice in quella posizione */
        JList_HeadDelete( (void *)&FreeLoc, Set->FreeList );

        /* Creare un nuovo vertice nella locazione libera */
        ReturnStatus = JVertex_New( &Set->Vertices[FreeLoc] );
        if( ReturnStatus == SUCCESS )
        {
            /* Impostare l'etichetta del nuovo vertice */
            ReturnStatus = JVertex_SetLabel(Label, Set->Vertices[FreeLoc] );
            /* calcolare ID del vertice */
            Set->Vertices[FreeLoc]->Id = CalculateVertexID(Label);
            /* TODO inserire dati del vertice */
            if( ReturnStatus == SUCCESS )
            {
                /* Aggiornare il numero di vertici inseriti */
                Set->NumActiveVertices += 1;
            }
#ifdef DEBUG
            fprintf(stderr, "[JVSET: Inserisco il vertice nella locazione %d]\n", FreeLoc);
            fprintf(stderr, "[JVSET: Vertex->Id = %d]\n", Set->Vertices[FreeLoc]->Id);
#endif
        }
    }
    else
    {
        /* Nodo con etichetta passata in input già esistente */
        ReturnStatus = ERROR;
    }
    return ReturnStatus;
}


/**
 * Rimuove un vertice dall'insieme
 *
 * Questa funzione rimuove un vertice dall'insieme, data la sua etichetta.
 *
 * @param Label Etichetta del vertice da rimuovere
 * @param Set   Puntatore all'insieme dei vertici
 *
 * @return Esito dell'operazione
 * */
J_STATUS JVset_RemoveVertex( char *Label, J_VSET *Set )
{
    int VertexToDelete;
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    ReturnStatus = JVset_FindVertexIndexByLabel(Label, &VertexToDelete, Set);
    if( ReturnStatus == SUCCESS )
    {
        /* TODO Aggiungere cancellazione dati vertice */
#ifdef DEBUG
        fprintf(stderr, "[JVSET: Cancellazione del vertice in posizione %d]\n", VertexToDelete);
#endif
        
        MemFree( (void **)&(Set->Vertices[VertexToDelete]->Label) );
        MemFree( (void **)&(Set->Vertices[VertexToDelete]) );
        Set->Vertices[VertexToDelete] = NULL;
        JList_HeadInsert( (void *)&VertexToDelete, Set->FreeList );
        Set->NumActiveVertices -= 1;
    }

    return ReturnStatus;

}

/**
 * Recupera il puntatore ad un vertice, data l'etichetta.
 *
 * */
J_STATUS JVset_FindVertexByLabel( char *Label, J_VERTEX **OutVertex, J_VSET *Set )
{
   int Trovato;
   J_STATUS ReturnStatus;

   ReturnStatus = SUCCESS;
   *OutVertex = NULL;

   /* Cerco l'indice del vertice data l'etichetta */
   JVset_FindVertexIndexByLabel(Label, &Trovato, Set);

   if( Trovato != -1 )
   {
       *OutVertex = Set->Vertices[Trovato];
   }
   else
   {
       ReturnStatus = W_SET_NOTFOUND;
   }

   return ReturnStatus;
}

void JVset_IterateOnSet( void (*action)(J_VERTEX *), J_VSET *Set )
{
    int i;

    for( i = 0; i < Set->Size; i++ )
    {
        action(Set->Vertices[i]);
    }

}

/*============================METODI PRIVATI=====================================*/

static int JVset_IsMember(char *Label, J_VSET *Set)
{
   int i;
   int Found;
   int VertexId;

   VertexId = CalculateVertexID(Label);

   Found = 0;
   i = 0;
   VertexId = CalculateVertexID( Label );

   while( (i < Set->Size) && (Found == 0) )
   {
       if( Set->Vertices[i] && (Set->Vertices[i]->Id == VertexId) )
       {
           Found = 1;
       }
       i += 1;
   }

   return Found;
}
/**
 * Recupera l'indice della locazione in cui è memorizzato un vertice
 * data l'etichetta
 * */
static J_STATUS JVset_FindVertexIndexByLabel( char *Label, int *Index, J_VSET *Set )
{
   int i;
   J_STATUS Trovato;
   int VertexDesiredId;

   Trovato = W_SET_NOTFOUND;
   i = 0;
   *Index = -1;
   VertexDesiredId = CalculateVertexID( Label );

   while( (i < Set->Size) && (Trovato != SUCCESS) )
   {
       if( Set->Vertices[i] && (Set->Vertices[i]->Id == VertexDesiredId) )
       {
           Trovato = SUCCESS;
           *Index = i;
       }
       i += 1;
   }

   return Trovato;
}
/**
 * Inserisce tutte le locazioni libere nella FreeList e inizializza i puntatori
 * ai vertici
 *
 * */
static void JVset_InitializeVerticesAndFreeList( int OldSize, J_VSET *Set )
{
    int i;
    int TempIndex;

    /* allocare il doppio dello spazio per l'insieme e richiamare l'inserimento */


    /* Se l'insieme è stato reallocato correttamente */

    for( i = OldSize; i < Set->Size; i++)
    {
        Set->Vertices[i] = NULL;
        /* Inserisce nella freelist dall'ultima locazione disponibile scendendo
         * fino alla precedente dimensione.
         * Es.
         * OldSize = 4
         * NewSize = 8
         *
         * Inserisce in testa alla lista:
         * 8 + 4 - 4 - 1 = 7
         * 8 + 4 - 5 - 1 = 6
         * 8 + 4 - 6 - 1 = 5
         * 8 + 4 - 7 - 1 = 4
         * Risultando nella lista:
         * [4]->[5]->[6]->[7]
         * */
        TempIndex = Set->Size + OldSize - i - 1;
#ifdef DEBUG
        fprintf(stderr, "[JVSET: Inserimento %d in FreeList]\n", TempIndex);
#endif
        /* inserisce l'indice nella freelist */
        JList_HeadInsert( (void *)&TempIndex, Set->FreeList );

    }
}
/**
 * Calcola un identificativo univoco per vertice
 *
 * Questa funzione calcola un identificativo numerico univoco per un vertice. 
 * NOTA
 * È ricavata dalla funzione di hashing del K&R.
 * */
static int CalculateVertexID(char *Label)
{
    int Id;

    for(Id = 0; *Label != '\0'; Label++)
    {
        Id = *Label + 31 * Id;
    }
    return Id;
}

/*============================FINE METODI PRIVATI================================*/



/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * GESTIONE FREE LIST
 * */

static void RecuperaInt( const void *NodeValue, void *OutValue )
{
    int *NumPtr = (int *)OutValue;
    *NumPtr = *( (int *)NodeValue );
    OutValue = (void *)NumPtr;

}
static int NumCmp( const void *Num1, const void *Num2 )
{
	int ReturnValue;
	int First = *( (int *)Num1 );
	int Second = *( (int *)Num2 );

	if ( First < Second )
	{
		ReturnValue = -1;
	}
	else if ( First == Second )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;

}
static void DeallocaInt( void *InputValue, void *NodeInfo )
{
	free( NodeInfo );
}
static void *InizializzaNodoInt( void *Value )
{
	/* int *Num = (int *) malloc( sizeof(int) ); */
	int *Num = NULL;
	MemAlloc( sizeof(int), (void **)&Num );
	
	*Num = *( (int *)Value );
	return (void *)Num;
}

