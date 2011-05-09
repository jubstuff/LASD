/*=============================================================================
 *
 * Nome File: main.c
 *
 * Scopo: main file per la gestione di una libreria di grafi 
 *
 * Data Creazione: 06-05-2011
 *
 * Ultima Modifica: sab 07 mag 2011 09:26:38 CEST
 *
 * Autore: Giustino Borzacchiello - 566/3291 - giustinob@gmail.com
 *
 *
 =============================================================================*/

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 10 

int main(void)
{
	GRAPH *G;

	G = InitGraph(NUM_VERTICES);
	AddVertex( G, "A");
	AddVertex( G, "B");
	AddVertex( G, "C");
	AddVertex( G, "D");
    printf("Numero Vertici: %d\n", G->NumVertices);
	AddEdge( G, 0, 1, 0); 
	AddEdge( G, 0, 2, 0); 
	AddEdge( G, 1, 0, 0); 
	AddEdge( G, 1, 2, 0); 
	AddEdge( G, 1, 3, 0); 
	AddEdge( G, 2, 0, 0); 
	AddEdge( G, 2, 1, 0); 
	AddEdge( G, 2, 3, 0); 
	AddEdge( G, 3, 1, 0); 
	AddEdge( G, 3, 2, 0);
	/*
	 * A--B
	 * | /|
	 * |/ |
	 * C--D
	 * */
	PrintGraph( G );
    DestroyGraph( G );
	return 0;
}
