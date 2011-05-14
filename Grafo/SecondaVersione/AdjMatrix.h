/*=============================================================================
 *
 * Nome File: AdjMatrix.h
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
#ifndef _ADJ_MATRIX_
#define _ADJ_MATRIX_

#include "graph.h"

typedef struct edge_m_tag
{
	int    Exist;  /**< 1 se l'arco esiste, 0 altrimenti */
	double Weight; /**< Peso associato all'arco, default 0 */
} EDGE_M;

void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices, int MaxVertices );
void AddEdgeMatrix( GRAPH *G, int VertexFrom, int VertexTo, double Weight );
EDGE_M *GetCell( EDGE_M *Matrix, int Dim, int Row, int Column );
void DeallocateAdjacencyMatrix( void *DataStructure, int NumVertices );
void PrintAdjMatrix( GRAPH *G );
#endif
