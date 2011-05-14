/*=============================================================================
 *
 * Nome File: AdjList.c
 *
 * Scopo: 
 *
 * Data Creazione: 14-05-2011
 *
 * Ultima Modifica: sab 14 mag 2011 13:13:17 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/
#include "AdjList.h"
#include <stdlib.h>
#include <stdio.h>
OPERATIONS *InitOperationAdjList( void )
{
	OPERATIONS *InnerOp;

	InnerOp = (OPERATIONS *)malloc( sizeof(OPERATIONS) );
	if( InnerOp != NULL )
	{
		InnerOp->InitNode = InitNodeAdjList;
		InnerOp->Compare = NULL;
		InnerOp->Delete = DeleteNodeAdjList;
		InnerOp->Print = PrintNodeAdjList;
		InnerOp->ManageDuplicate = NULL; 
	}

	return InnerOp;
}

void *InitNodeAdjList( void *Edge )
{
	return Edge;
}
/**
 * Dealloca un arco dalla lista di adiacenzo
 *
 * @param InputValue Valore da eliminare passato in ingresso
 * @param Edge   Riferimento al valore da deallocare
 *
 * */
void DeleteNodeAdjList( void *InputValue, void *Edge )
{
	free( Edge );
}

void PrintNodeAdjList( const void *Edge )
{
	printf( "(%d)", ( (EDGE_L *)Edge )->DestVertex );
}
void DeallocateAdjacencyList( void *DataStructure, int NumVertices )
{
	int i; /**< Indice per cicli */
	NODE **AdjList;   /**< Puntatore temporaneo alle liste di adiacenza */
	OPERATIONS *ListOp; /**< Puntatore alle operazioni per la lista */

	//inizializzo le operazioni per la gestione della lista
	ListOp = InitOperationAdjList();

	AdjList = (NODE **)DataStructure;
	for( i = 0; i < NumVertices; i++ )
	{
		//Richiamo List_Destroy su ogni elemento di DataStructure
		AdjList[i] = List_RecursiveDestroy(AdjList[i], ListOp );
	}
	//Dealloco DataStructure
	free( DataStructure );
	free( ListOp );
}

void *AllocateAdjacencyList( void *DataStructure, int NumVertices, int MaxNumVertices )
{
	NODE **AdjList; /**< Puntatore temporaneo alla lista di adiacenza */
	int i; /**< Contatore per cicli */

	//Alloco un array di puntatori a NODE[MaxNumVertices]
	AdjList = (NODE **)realloc( DataStructure, MaxNumVertices * sizeof( NODE *) );
	//Inizializzo a NULL tutti i puntatori
	for( i = 0; i < MaxNumVertices; i++ )
	{
		AdjList[i] = NULL;
	}
	//Restituisco il puntatore all'array
	return (void *)AdjList;
}

void AddEdgeAdjList( GRAPH *G, int Source, int Destination, double Weight ) 
{
	EDGE_L *TempEdge; /**< Puntatore temporaneo al nuovo arco */
	OPERATIONS *ListOp; /**< Puntatore alle operazioni per la lista */
	int ReturnStatus; /**< Codice di ritorno delle funzioni */
	NODE **AdjList;   /**< Puntatore temporaneo alle liste di adiacenza */

	AdjList = (NODE **)G->DataStructure;

	//Alloco un EDGE_L a
	TempEdge = (EDGE_L *)malloc( sizeof( EDGE_L ) ); 
	if( TempEdge )
	{
		//inizializzo le operazioni per la gestione della lista
		ListOp = InitOperationAdjList();
		// - imposto a.DestVertex = Destination
		TempEdge->DestVertex = Destination;
		// - imposto a.Weight = Weight
		TempEdge->Weight = Weight;
		//Inserisco il nodo nella lista relativa a DataStructure[Source], passando a come valore
		G->DataStructure = List_Insert( (void *)TempEdge, (NODE *)( AdjList[Source] ), &ReturnStatus, ListOp ); 
		//dealloco la struttura delle operazioni per la lista
		free( ListOp );
	}
	else 
	{
		//TODO ritornare codice di errore
	}
}
void PrintAdjList( GRAPH *G )
{
	int i;            /**< Indice per cicli */
	OPERATIONS *ListOp; /**< Puntatore alle operazioni per la lista */
	NODE **AdjList;   /**< Puntatore temporaneo alle liste di adiacenza */

	//Recuperare il vettore di liste di adiacenza
	AdjList = (NODE **)G->DataStructure;

	//inizializzo le operazioni per la gestione della lista
	ListOp = InitOperationAdjList();
	for( i = 0; i < G->NumVertices; i++ )
	{
		//Stampare la lista associata ad ogni vertice 
		printf("Vertice %d", i);
		List_RecursivePrint( AdjList[i], ListOp );
		printf("\n");
	}
	free( ListOp );

}
