/*=============================================================================
 *
 * Nome File: main.c
 *
 * Scopo: 
 *
 * Data Creazione: 12-05-2011
 *
 * Ultima Modifica: mar 17 mag 2011 23:21:44 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/

#include "graph.h"
#include "AdjList.h"
#include "AdjMatrix.h"

#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LISTA 1
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
    str2 = malloc( (strlen("Quattro")+1) * sizeof(char) );
	strcpy( str2, "Quattro" );
	InsertVertex( G, str2, NULL );

    InsertEdge(G, 0, 2, 0);
    InsertEdge(G, 1, 2, 0);
    InsertEdge(G, 1, 3, 0);
    InsertEdge(G, 2, 0, 0);
    InsertEdge(G, 2, 1, 0);
    InsertEdge(G, 2, 3, 0);
    InsertEdge(G, 3, 1, 0);
    InsertEdge(G, 3, 2, 0);
	PrintGraph( G );

	DestroyGraph( G );
	return 0;
}
