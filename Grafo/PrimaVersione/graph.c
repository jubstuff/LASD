/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 06-05-2011
 *
 * Ultima Modifica: sab 07 mag 2011 12:33:58 CEST
 *
 * Autore: Giustino Borzacchiello - 566/3291 - giustinob@gmail.com
 *
 *
 =============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

GRAPH *InitGraph( int MaxVertices )
{
	GRAPH *G;

	/* Alloco la struct che conterrà le info sul grafo */
	G = (GRAPH *)malloc( sizeof(GRAPH) ); /* TODO check errors */

    G->DataStructure = NULL;

	G->Op = (G_OPERATIONS *)malloc( sizeof(G_OPERATIONS) ); /* TODO check errors */

    G->Op->AllocateDS = AllocateAdjacencyMatrix; /* TODO Passare come parametro struct operazioni*/
	G->Op->DeallocateDS = FreeAdjacencyMatrix;

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
	//G->DataStructure = G->Op->AllocateDS( G->DataStructure, MaxVertices );
	G->DataStructure = G->Op->AllocateDS( G->DataStructure, G->NumVertices, MaxVertices );
	/* Alloco il vettore contenente le etichette dei vertici */
	G->Labels = (char **)malloc( MaxVertices * sizeof(char *) ); /* TODO check errors */

	return G;
}


void DestroyGraph( GRAPH *G )
{
	free( G->Labels );
	G->Op->DeallocateDS( G->DataStructure );
	free( G );
}

void AddEdge( GRAPH *G, int VertexFrom, int VertexTo, double Weight )
{
	EDGE_M *TempEdge; /**< Variabile d'appoggio per l'arco */

	/* Inserisco l'arco solo se i vertici di partenza e arrivo appartengono
	 * al grafo
	 * */
    if( VertexFrom <= G->NumVertices && VertexTo <= G->NumVertices )
	{
		/* Recupero l'arco interessato */
		TempEdge = &( ((EDGE_M *)(G->DataStructure))[VertexFrom * G->NumVertices + VertexTo] ); //TODO sostituire con funzione di recupero archi generica
		/* Abilito l'arco e imposto il peso corrispondente */
		TempEdge->Exist = 1;
		TempEdge->Weight = Weight;
	}
}

void AddVertex( GRAPH *G, char *Label ) 
{
	int i;
	/* Se il numero di vertici supera quelli allocati, ne alloco una quantità
	 * superiore
	 * */
	if( G->NumVertices == G->MaxVertices )
	{      /* TODO Sostituire questa parte sottostante con la reallocazione della DS generale */
		/* Alloco più di un vertice, così da non dover richiamare realloc
		 * troppe volte
		 * Il numero di vertici aggiuntivi da allocare può essere deciso in base
		 * all'utilizzo, modificando la costante REALLOC_SIZE
		 * */
		G->MaxVertices += REALLOC_SIZE;
		/* Realloco e inizializzo gli archi aggiuntivi */
		G->AdjacencyMatrix = (EDGE_M *)realloc(G->AdjacencyMatrix, 
				G->MaxVertices * G->MaxVertices * sizeof(EDGE_M) ); /* TODO check errors */
		for( i = G->NumVertices; i < G->MaxVertices * G->MaxVertices; i++ )
		{
			G->AdjacencyMatrix[i].Exist = 0;
			G->AdjacencyMatrix[i].Weight = 0;
		}
		/* Realloco il vettore contenente le etichette dei vertici */
		G->Labels = (char **)realloc( G->Labels, G->MaxVertices * sizeof(char *) ); /* TODO check errors */
	}
	/* L'etichetta viene assegnata al nuovo vertice ed il numero di vertici incrementato */
	G->Labels[G->NumVertices] = Label;
	G->NumVertices++;
}


void PrintGraph( GRAPH *G )
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
	for( i = 0; i < G->NumVertices; i++) /* TODO sostituire questi cicli con la funzione di stampa generica */
	{
		printf("%-*s ", MaxLabelLength, G->Labels[i]); 
		for( j = 0; j < G->NumVertices; j++)
		{
			printf("(%d, %*.2f) ", ((EDGE_M *)(G->DataStructure))[i * G->NumVertices + j].Exist,
					MaxLabelLength, ((EDGE_M *)(G->DataStructure))[i * G->NumVertices + j].Weight );
		}
		printf("\n");
	}
}

/**
 * FUNZIONI PER MATRICE DI ADIACENZA
 * */
void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices, int MaxVertices )
{
	int i; /**< Indice per cicli */
	EDGE_M *TempAdjMatrix;

	TempAdjMatrix = (EDGE_M *)realloc( DataStructure, 
			MaxVertices * MaxVertices * sizeof(EDGE_M) ); /* TODO check errors */

    for( i = NumVertices; i < MaxVertices * MaxVertices; i++ )
	{
		TempAdjMatrix[i].Exist = 0;
		TempAdjMatrix[i].Weight = 0;
	}

	return (void *)TempAdjMatrix;
}

void FreeAdjacencyMatrix( void *DataStructure )
{
	free( DataStructure );
}

