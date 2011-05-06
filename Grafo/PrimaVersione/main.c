/*=============================================================================
 *
 * Nome File: main.c
 *
 * Scopo: main file per la gestione di una libreria di grafi 
 *
 * Data Creazione: 06-05-2011
 *
 * Ultima Modifica: sab 07 mag 2011 00:31:00 CEST
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
	GRAPH_M *G;

	G = InitGraph(NUM_VERTICES);
	AddVertex( G, "Uno");
	AddVertex( G, "Due");
	AddVertex( G, "Tre");
	AddVertex( G, "Quattro");
	AddVertex( G, "Cinque");
	AddVertex( G, "Nove");
	AddVertex( G, "Dieciiiiiiii");

	PrintGraph( G );

	return 0;
}
