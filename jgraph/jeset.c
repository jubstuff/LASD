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


J_STATUS JEset_New( int HintNumVertices, J_ESET **Set )
{
    J_STATUS ReturnStatus;
    JLIST_METHODS Op;

    ReturnStatus = SUCCESS;

    /* Alloco l'insieme degli archi */
    ReturnStatus = MemAlloc(sizeof(J_ESET), (void **)Set);

    if( ReturnStatus == SUCCESS )
    {
        /* Se l'insieme è stato correttamente allocato */

        /* alloco i puntatori alle liste di adiacenza */
        ReturnStatus = MemAlloc( HintNumVertices * sizeof(J_EDGE *),
                (void **)&( (*Set)->AdjLists ) );
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

