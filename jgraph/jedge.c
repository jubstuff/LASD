/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* Nome File : jedge.c

* Scopo : Implementazione del tipo di dato Arco

* Data di creazione : 03-01-2012

* Ultima modifica : 03-01-2012

* Autore : Giustino Borzacchiello - matr. 566/3291 - giustinob@gmail.com

_._._._._._._._._._._._._._._._._._._._._.*/

#include "jedge.h"
#include "mem.h"
#include <stdlib.h>


/**
 * Alloca e inizializza un nuovo arco
 *
 * */
J_STATUS JEdge_New( J_EDGE **E )
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    ReturnStatus = MemAlloc( sizeof(J_EDGE), (void **)E );
    if( ReturnStatus == SUCCESS )
    {
        (*E)->DestVertex = NULL;
        (*E)->Weight = 0;
    }

    return ReturnStatus;

}
/**
 * Recupera il peso di un arco
 *
 * */
double JEdge_GetWeight( J_EDGE *E )
{
    return E->Weight;
}

/**
 * Imposta il peso di un arco
 *
 * */
void JEdge_SetWeight( double Weight, J_EDGE *E )
{
    E->Weight = Weight;

}

/**
 * Recupera la destinazione di un arco
 *
 * */
J_VERTEX *JEdge_GetDestVertex( J_EDGE *E )
{
    return E->DestVertex;
}

/**
 * Imposta la destinazione di un arco
 *
 * */
void JEdge_SetDestVertex( J_VERTEX *V, J_EDGE *E)
{
    E->DestVertex = V;
}

/**
 * Dealloca un arco 
 *
 * */
void JEdge_Destroy( J_EDGE *E )
{
    MemFree( (void **)&E );
}
