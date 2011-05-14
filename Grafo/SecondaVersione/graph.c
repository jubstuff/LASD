/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: sab 14 mag 2011 11:07:05 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

GRAPH *InitializeGraph( int MaxNumVertices, G_OPERATIONS *Op )
{
	GRAPH *G; /**< Variabile temporanea */
	int i; /**< Contatore per cicli */

	//Allocare la struct GRAPH
	G = (GRAPH *)malloc( sizeof( GRAPH ) ); /* TODO check errors */
	//Impostare MaxNumVertices a MaxNumVertices + REALLOC_SIZE
	G->MaxNumVertices = MaxNumVertices + REALLOC_SIZE;
	//Impostare NumVertices a zero
	G->NumVertices = 0;
	//Allocare l'array di V_DETAILS[MaxNumVertices]
	G->VertexDetails = (V_DETAILS *)malloc( MaxNumVertices * sizeof( V_DETAILS ) );	//TODO check errors
	//Inizializzare l'array di V_DETAILS
	// - InDegree = 0
	// - OutDegree = 0
	// - Label = NULL
	// - Processed = 0
	// - Data = NULL
	for( i = 0; i < MaxNumVertices; i++ )
	{
		G->VertexDetails[i].InDegree = 0;
		G->VertexDetails[i].OutDegree = 0;
		G->VertexDetails[i].Label = NULL;
		G->VertexDetails[i].Processed = 0;
		G->VertexDetails[i].Data = NULL;
		
	}
	// Copiare Op nel campo del GRAPH
	G->Op = Op;
	// Allocare la struttura dati
	G->DataStructure = G->Op->AllocateDS( G->DataStructure, G->NumVertices, G->MaxNumVertices );

	return G;
}

void DestroyGraph( GRAPH *G )
{
	int i; /**< Contatore per cicli */
	
	//Dealloco la struttura dati rappresentate il grafo
	G->Op->DeallocateDS( G->DataStructure, G->NumVertices );
	//Dealloco l'array di V_DETAILS, avendo cura di deallocare 
	//gli elementi contenuti in ogni singolo elemento
	for( i = 0; i < G->NumVertices; i++ ) 
	{
			free( G->VertexDetails[i].Label );
			free( G->VertexDetails[i].Data );
	}
	free( G->VertexDetails );
	//Dealloco il GRAPH
	free( G );
}

void InsertEdge( GRAPH *G, int Source, int Destination, double Weight )
{
	//Incremento di 1 il grado entrante del vertice Destination
	G->VertexDetails[Destination].InDegree += 1;
	//Incremento di 1 il grado uscente del vertice Source
	G->VertexDetails[Source].OutDegree += 1;
	//Richiamo il metodo AddEdge da Op
	G->Op->AddEdge( G, Source, Destination, Weight );
	//Imposto il peso dell'arco
}

void InsertVertex( GRAPH *G, char *Label, void *Data )
{

	//Se NumVertici = MaxNumVertices
	if( G->NumVertices == G->MaxNumVertices )
	{
		//  - Incremento MaxNumVertices di REALLOC_SIZE
        G->MaxNumVertices += REALLOC_SIZE;
		//  - Realloco V_DETAILS[MaxNumVertices] e inizializzo i nuovi elementi, (da NumVertices in poi)
		G->VertexDetails = (V_DETAILS *)realloc( G->VertexDetails, G->MaxNumVertices * sizeof( V_DETAILS ) );	//TODO check errors 
		//  - Richiamo ALLOCATE_DS con i parametri adatti
		G->DataStructure = G->Op->AllocateDS( G->DataStructure, G->NumVertices, G->MaxNumVertices );
	}
	
	//Imposto l'etichetta relativa al nodo G->NumVertices 
	G->VertexDetails[G->NumVertices].Label = Label;
	//Copio i dati relativi al nuovo vertice
	G->VertexDetails[G->NumVertices].Data = Data;
	//Incremento il numero di vertici del grafo
	G->NumVertices++;
}

void PrintGraph( GRAPH *G )
{
	//Richiamo la stampa relativa alla struttura dati idonea
	G->Op->PrintDS( G );
}

#ifdef IMPLEMENTED
#endif
/**=============================================================================
 * OPERAZIONI PER LISTA
 *============================================================================*/
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
		List_RecursivePrint( AdjList[i], ListOp );
	}
	free( ListOp );

}
/**=============================================================================
 * OPERAZIONI PER MATRICE 
 *============================================================================*/
void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices, int MaxVertices )
{
	int i; /**< Indice per cicli */
	EDGE_M *TempAdjMatrix; /**< Matrice di adiacenza temporanea */

	TempAdjMatrix = NULL;
	//Alloco un array di puntatori EDGE_M[MaxNumVertices]
	TempAdjMatrix = (EDGE_M *)realloc( DataStructure, 
			MaxVertices * MaxVertices * sizeof(EDGE_M) ); /* TODO check errors */

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
