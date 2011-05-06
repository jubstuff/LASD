/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 06-05-2011
 *
 * Ultima Modifica: sab 07 mag 2011 00:32:22 CEST
 *
 * Autore: Giustino Borzacchiello - 566/3291 - giustinob@gmail.com
 *
 *
 =============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

GRAPH_M *InitGraph( int MaxVertices )
{
	int i; /**< Indice per cicli */

	/* Alloco la struct che conterrà le info sul grafo */
	GRAPH_M *G = (GRAPH_M *)malloc( sizeof(GRAPH_M) ); /* TODO check errors */

	/* Imposto un massimo numero iniziale di vertici, pari a quello passato
	 * in ingresso */
	G->MaxVertices = MaxVertices;
	/* Imposto a zero il numero iniziale dei vertici */
	G->NumVertices = 0;
	/* Alloco e inizializzo la matrice di adiacenza del grafo.
	 *
	 * La matrice viene allocata come un vettore di una dimensione: dunque per
	 * accedere al vertice (A, B) sarà necessario accedere all'elemento
	 * AdjacencyMatrix[A * MaxVertices + B] 
	 * */
	G->AdjacencyMatrix = (EDGE_M *)malloc( MaxVertices * MaxVertices * sizeof(EDGE_M) ); /* TODO check errors */
    for( i = 0; i < MaxVertices * MaxVertices; i++ )
	{
		G->AdjacencyMatrix[i].Exist = 0;
		G->AdjacencyMatrix[i].Weight = 0;
	}
	/* Alloco il vettore contenente le etichette dei vertici */
	G->Labels = (char **)malloc( MaxVertices * sizeof(char *) ); /* TODO check errors */

	return G;
}

void AddEdge( GRAPH_M *G, int VertexFrom, int VertexTo, double Weight )
{
	EDGE_M *TempEdge; /**< Variabile d'appoggio per l'arco */

	/* Inserisco l'arco solo se i vertici di partenza e arrivo appartengono
	 * al grafo
	 * */
    if( VertexFrom < G->MaxVertices && VertexTo < G->MaxVertices )
	{
		/* Recupero l'arco interessato */
		TempEdge = &( G->AdjacencyMatrix[VertexFrom * G->MaxVertices + VertexTo] );
		/* Abilito l'arco e imposto il peso corrispondente */
		TempEdge->Exist = 1;
		TempEdge->Weight = Weight;
	}
}

void AddVertex( GRAPH_M *G, char *Label ) 
{
	G->Labels[G->NumVertices] = Label;
	G->NumVertices++;
}

void PrintGraph( GRAPH_M *G )
{
	int i;
	int j;
	int MaxLabelLength;
	int CurrentLabelLength;

	MaxLabelLength = 0;
    /* Recupero la massima lunghezza di un'etichetta del grafo */
	for( i = 0; i < G->NumVertices; i++)
	{
		CurrentLabelLength = strlen( G->Labels[i] );
		if( CurrentLabelLength > MaxLabelLength )
		{
			MaxLabelLength = CurrentLabelLength;
		}
	}             

	/* Lascio uno spazio pari alla massima lunghezza di un'etichetta nella
	 * riga d'intestazione (incrocio della tabella)
	 * */
	printf("%*s ", MaxLabelLength+1, "");

	/* Stampo le etichette nella riga d'intestazione */
	for( i = 0; i < G->NumVertices; i++)
	{
		printf("%-*s", MaxLabelLength + 6, G->Labels[i]); 
	}
	printf("\n");
	/* Stampo le righe di adiacenza dei vertici */
	for( i = 0; i < G->NumVertices; i++)
	{
		printf("%-*s ", MaxLabelLength, G->Labels[i]); 
		for( j = 0; j < G->NumVertices; j++)
		{
			printf("(%d, %*.2f) ", G->AdjacencyMatrix[i * G->NumVertices + j].Exist,
					MaxLabelLength, G->AdjacencyMatrix[i * G->NumVertices + j].Weight );
		}
		printf("\n");
	}
}
