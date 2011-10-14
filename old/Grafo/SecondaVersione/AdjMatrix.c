/*=============================================================================
 *
 * Nome File: AdjMatrix.c
 *
 * Scopo: 
 *
 * Data Creazione: 14-05-2011
 *
 * Ultima Modifica: sab 14 mag 2011 13:22:27 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/
#include "AdjMatrix.h"
#include <stdlib.h>
#include <stdio.h>
/**=============================================================================
 * OPERAZIONI PER MATRICE 
 *============================================================================*/
void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices, int MaxVertices )
{
	int i; /**< Indice per cicli */
	EDGE_M *TempAdjMatrix; /**< Matrice di adiacenza temporanea */

	TempAdjMatrix = NULL;
	//Alloco un array di puntatori EDGE_M[MaxNumVertices]
	TempAdjMatrix = (EDGE_M *)realloc( DataStructure, MaxVertices * MaxVertices * sizeof(EDGE_M) ); /* TODO check errors */
    //TempAdjMatrix = (EDGE_M *)malloc( MaxVertices * MaxVertices * sizeof(EDGE_M) ); /* TODO check errors */
	//Inizializzo tutti gli elementi: Exist = 0, Weight = 0
    for( i = NumVertices; i < MaxVertices * MaxVertices; i++ )
	{
		TempAdjMatrix[i].Exist = 0;
		TempAdjMatrix[i].Weight = 0;
	}

	//Restituisco il puntatore alla matrice
	return (void *)TempAdjMatrix;
}

void DeallocateAdjacencyMatrix( void *DataStructure, int NumVertices )
{
	//Dealloco la matrice di adiacenza
	free( DataStructure );
}
void AddEdgeMatrix( GRAPH *G, int VertexFrom, int VertexTo, double Weight )
{
	EDGE_M *TempEdge; /**< Variabile d'appoggio per l'arco */

	/* Recupero l'arco interessato */
	//TempEdge = &( ((EDGE_M *)(G->DataStructure))[VertexFrom * G->NumVertices + VertexTo] );
	TempEdge = (EDGE_M *)GetCell( (EDGE_M *)G->DataStructure, G->NumVertices, VertexFrom, VertexTo );
	/* Abilito l'arco e imposto il peso corrispondente */
	TempEdge->Exist = 1;
	TempEdge->Weight = Weight;
}

EDGE_M *GetCell( EDGE_M *Matrix, int Dim, int Row, int Column )
{
	//Restituisco l'indirizzo dell'arco (Row, Column)
	return &Matrix[Row * Dim + Column];
}

void PrintAdjMatrix( GRAPH *G )
{
	int i; /**< Indice per cicli */
	int j; /**< Indice per cicli */
	EDGE_M *TempMatrix; /**< Puntatore temporaneo alla matrice di adiacenza */
	EDGE_M *TempEdge;   /**< Puntatore temporaneo ad un arco */

	TempMatrix = (EDGE_M *)G->DataStructure;

	for( i = 0; i < G->NumVertices; i++) /* TODO sostituire questi cicli con la funzione di stampa generica */
	{
		for( j = 0; j < G->NumVertices; j++)
		{
			TempEdge = GetCell( TempMatrix, G->NumVertices, i, j );
			printf("(%d) ", TempEdge->Exist);
					
		}
		printf("\n");
	}



}
