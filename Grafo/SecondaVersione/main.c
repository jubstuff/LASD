/*=============================================================================
 *
 * Nome File: main.c
 *
 * Scopo: 
 *
 * Data Creazione: 12-05-2011
 *
 * Ultima Modifica: sab 14 mag 2011 12:46:59 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/

#include "graph.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

#define MATRICE 1
#define MAX_LENGTH 1000

int main(void)
{
	GRAPH *G;
    G_OPERATIONS GraphOp;
	char *str1, *str2;
	
	G = NULL;
#ifdef MATRICE
	GraphOp.AllocateDS = AllocateAdjacencyMatrix;
	GraphOp.DeallocateDS = DeallocateAdjacencyMatrix;
	GraphOp.AddEdge = AddEdgeMatrix;
	GraphOp.PrintDS = PrintAdjMatrix;
#endif
#ifdef LISTA
	GraphOp.AllocateDS = AllocateAdjacencyList;
	GraphOp.DeallocateDS = DeallocateAdjacencyList;
	GraphOp.AddEdge = AddEdgeAdjList;
	GraphOp.PrintDS = PrintAdjList;
#endif


	G = InitializeGraph( 2, &GraphOp );

    str1 = malloc( (strlen("Uno")+1) * sizeof(char) );
	strcpy( str1, "Uno" );
	InsertVertex( G, str1, NULL );

    str2 = malloc( (strlen("Due")+1) * sizeof(char) );
	strcpy( str2, "Due" );
	InsertVertex( G, str2, NULL );

    str2 = malloc( (strlen("Tre")+1) * sizeof(char) );
	strcpy( str2, "Tre" );
	InsertVertex( G, str2, NULL );

	PrintGraph( G );


	DestroyGraph( G );
	return 0;
}
