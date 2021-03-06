/*=============================================================================
 *
 * Nome File: AdjList.h
 *
 * Scopo: 
 *
 * Data Creazione: 14-05-2011
 *
 * Ultima Modifica: sab 14 mag 2011 13:23:47 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/
#ifndef _ADJ_LIST_
#define _ADJ_LIST_

#include "../../lib/lista.h"
#include "graph.h"

typedef struct edge_l_tag
{
	int    DestVertex; /**< Destinazione dell'arco */
	double Weight;     /**< Peso associato all'arco, default 0 */
} EDGE_L;

OPERATIONS *InitOperationAdjList( void );
void *InitNodeAdjList( void *Edge );
void DeleteNodeAdjList( void *InputValue, void *Edge );
void PrintNodeAdjList( const void *Edge );
void DeallocateAdjacencyList( void *DataStructure, int NumVertices );
void *AllocateAdjacencyList( void *DataStructure, int NumVertices, int MaxNumVertices );
void AddEdgeAdjList( GRAPH *G, int Source, int Destination, double Weight );
void PrintAdjList( GRAPH *G );

#endif
