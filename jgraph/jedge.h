/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* Nome File : jedge.h

* Scopo : Definizione del tipo di dato Arco

* Data di creazione : 03-01-2012

* Ultima modifica : 03-01-2012

* Autore : Giustino Borzacchiello - matr. 566/3291 - giustinob@gmail.com

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef JEDGE_H
#define JEDGE_H

#include "jvertex.h"
#include "errors.h"


typedef struct jedge_tag 
{
    J_VERTEX *DestVertex; /**< Destinazione dell'arco */
    double   Weight;      /**< Peso dell'arco */
} J_EDGE;

/**
 * Alloca e inizializza un nuovo arco
 *
 * */
J_STATUS JEdge_New( J_EDGE **E );

/**
 * Recupera il peso di un arco
 *
 * */
double JEdge_GetWeight( J_EDGE *E );

/**
 * Imposta il peso di un arco
 *
 * */
void JEdge_SetWeight( double Weight, J_EDGE *E );

/**
 * Recupera la destinazione di un arco
 *
 * */
J_VERTEX *JEdge_GetDestVertex( J_EDGE *E );

/**
 * Imposta la destinazione di un arco
 *
 * */
void JEdge_SetDestVertex( J_VERTEX *V, J_EDGE *E);

/**
 * Dealloca un arco 
 *
 * */
void JEdge_Destroy( J_EDGE *E );
#endif
