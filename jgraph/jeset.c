#include "jeset.h"
#include "jvset.h"
#include "mem.h"
#include "errors.h"
#include "lista.h"
#include <stdlib.h>


/*============================DEFINIZIONE STRUTTURE==============================*/

struct jedge_tag 
{
    J_VERTEX *DestVertex; /**< Destinazione dell'arco */
    double   Weight;      /**< Peso dell'arco */
};

struct jeset_tag
{
    J_LIST **AdjLists; /**< Vettore delle liste di adiacenza */
};


/*=======================FINE DEFINIZIONE STRUTTURE==============================*/

/*============================METODI PRIVATI=====================================*/
static void *InizializzaNodoAdjList( void *Value );
static int EdgeCmp( const void *Edge1, const void *Edge2 );
static void DeallocaEdge( void *InputValue, void *NodeInfo );

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

