#include <stdio.h>
#include "jeset.h"
#include "jvset.h"
#include "mem.h"
#include "errors.h"
#include "lista.h"
#include <stdlib.h>


/*============================DEFINIZIONE STRUTTURE==============================*/


struct jeset_tag
{
    J_LIST **AdjLists; /**< Vettore delle liste di adiacenza */
    J_LIST *FreeList;  /**< Lista delle locazioni libere */
    int Size;          /**< Numero totale di vertici */
};


/*=======================FINE DEFINIZIONE STRUTTURE==============================*/

/*============================METODI PRIVATI=====================================*/
static void *InizializzaNodoAdjList( void *Value );
static int EdgeCmp( const void *Edge1, const void *Edge2 );
static void DeallocaEdge( void *InputValue, void *NodeInfo );

/* Metodi per la gestione della FreeList */
static void JEset_InitializeFreeList( int OldSize, J_ESET *Set );
static void *InizializzaNodoInt( void *Value );
static void DeallocaInt( void *InputValue, void *NodeInfo );
static int NumCmp( const void *Num1, const void *Num2 );
static void RecuperaInt( const void *NodeValue, void *OutValue );


/**
 * Alloca un nuovo insieme degli archi
 *
 * */
J_STATUS JEset_New( int HintNumVertices, J_ESET **Set )
{
    J_STATUS ReturnStatus;
    JLIST_METHODS Op; /**< Metodi necessari per FreeList */

    ReturnStatus = SUCCESS;

    /* Alloco l'insieme degli archi */
    ReturnStatus = MemAlloc(sizeof(J_ESET), (void **)Set);

    if( ReturnStatus == SUCCESS )
    {
        /* Se l'insieme è stato correttamente allocato */

        (*Set)->Size = HintNumVertices;

        /* Inizializza la struct con le operazioni per la FreeList */
        Op.Compare = NumCmp;
        Op.InitNode = InizializzaNodoInt;
        Op.Delete = DeallocaInt;
        Op.GetNodeValue = RecuperaInt;

        /* Inizializza la FreeList */
        ReturnStatus = JList_Init(&(*Set)->FreeList, &Op); /* TODO Check error */
        
        JEset_InitializeFreeList(0, (*Set));

        /* alloco i puntatori alle liste di adiacenza */
        ReturnStatus = MemAlloc( (*Set)->Size * sizeof(J_EDGE *),
                (void **)&( (*Set)->AdjLists ) );
        /* TODO check error */
    }

    return ReturnStatus;
}

/**
 * Associa un vertice ad una lista di adiacenza
 *
 * */
J_STATUS JEset_LinkAdjListAndVertex(J_VERTEX *Vertex, J_ESET *EdgeSet)
{
    J_STATUS ReturnStatus;
    int FreeLoc;           /**< Locazione libera da associare al vertice */

    ReturnStatus = SUCCESS;
    if( Vertex )
    {

        /* Se la Freelist non è vuota, recupera il primo elemento
         * ed inserisci il vertice in quella posizione */
        JList_HeadDelete( (void *)&FreeLoc, EdgeSet->FreeList );
        /* Inizializzo la lista di adiacenza */
        EdgeSet->AdjLists[FreeLoc] = NULL;
#ifdef DEBUG
        fprintf(stderr, "[JESET: Estratto %d da FreeList]\n", FreeLoc);
#endif
        JVertex_SetAdjIndex( FreeLoc, Vertex);

    }
    else
    {
        ReturnStatus = ERROR; /* TODO cosa restituire? */
    }

    return ReturnStatus;
    
}



/**
 * Dealloca l'insieme degli archi
 *
 * */
void JEset_Destroy( J_ESET *Set )
{
    /* Dealloca la freelist */
    JList_Destroy( Set->FreeList );

    MemFree( (void **)&(Set->AdjLists) );
    MemFree( (void **)&Set );
}

/**
 * Aggiunge un arco nella lista di adiacenza del vertice sorgente
 *
 * Presuppone che il vertice abbia già una lista di adiacenza associata
 *
 * */
J_STATUS JEset_AddEdge( char *LabelSource, char *LabelDest, double Weight, J_VSET *VSet, J_ESET *ESet )
{
    J_VERTEX *Source;
    J_STATUS ReturnStatus;
    JLIST_METHODS Op;


    ReturnStatus = JVset_FindVertexByLabel(LabelSource, &Source, VSet);
    if( ReturnStatus == SUCCESS )
    {
        /* Sorgente trovata, inserisci l'elemento nella sua lista di adiacenza */

        /* Se la sua lista di adiacenza non è stata inizializzata, fallo adesso */
        if( ESet->AdjLists[Source->AdjIndex] == NULL )
        {

        }
    }

}
/************************************************************************************/
/*    METODI PRIVATI */
/************************************************************************************/
/**
 * Inserisce tutte le locazioni libere nella FreeList
 *
 * */
static void JEset_InitializeFreeList( int OldSize, J_ESET *Set )
{
    int i;
    int TempIndex;

    /* allocare il doppio dello spazio per l'insieme e richiamare l'inserimento */


    /* Se l'insieme è stato reallocato correttamente */

    for( i = OldSize; i < Set->Size; i++)
    {
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
        fprintf(stderr, "[JESET: Inserimento %d in FreeList]\n", TempIndex);
#endif
        /* inserisce l'indice nella freelist */
        JList_HeadInsert( (void *)&TempIndex, Set->FreeList );

    }
}

/*=========================GESTIONE LISTE DI ADIACENZA===========================*/

static void *InizializzaNodoAdjList( void *Value )
{
	J_EDGE *Edge = NULL;
	MemAlloc( sizeof(J_EDGE), (void **)&Edge );
	*Edge = *( (J_EDGE *)Value );
	return (void *)Edge;
}


static void DeallocaEdge( void *InputValue, void *NodeInfo )
{
	free( NodeInfo );
}

/*=========================GESTIONE FREE LIST===================================*/
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
