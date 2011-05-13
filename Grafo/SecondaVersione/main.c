/*=============================================================================
 *
 * Nome File: main.c
 *
 * Scopo: 
 *
 * Data Creazione: 12-05-2011
 *
 * Ultima Modifica: ven 13 mag 2011 12:58:29 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/

#include "graph.h"
#include <stdlib.h>



int main(void)
{
	GRAPH *G;
    G_OPERATIONS GraphOp;
	
	G = NULL;
	GraphOp.AllocateDS = AllocateAdjacencyMatrix;
	GraphOp.DeallocateDS = DeallocateAdjacencyMatrix;
	GraphOp.AddEdge = AddEdgeMatrix;
	GraphOp.PrintDS = PrintAdjMatrix;


	G = InitializeGraph( 10, &GraphOp );
	InsertVertex( G, "Uno", NULL );
	PrintGraph( G );
	return 0;
}
