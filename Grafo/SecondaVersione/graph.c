/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: ven 13 mag 2011 11:05:32 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/
#include "graph.h"
#include "../../lib/lista.h"
#include <stdlib.h>

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
	G->Op->DeallocateDS( G->DataStructure );
	//Dealloco l'array di V_DETAILS, avendo cura di deallocare 
	//gli elementi contenuti in ogni singolo elemento
	for( i = 0; i < G->MaxNumVertices; i++ ) //TODO qui qual è il limite? MaxNumVertices o NumVertices?
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
	G->Op->AddEdge( Source, Destination, Weight );
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

void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices, int MaxVertices )
{
	int i; /**< Indice per cicli */
	EDGE_M *TempAdjMatrix; /**< Matrice di adiacenza temporanea */

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

void AddEdgeAdjList( void *DataStructure, int Source, int Destination, double Weight ) 
{
	EDGE_L *TempEdge; /**< Puntatore temporaneo al nuovo arco */
	OPERATIONS *ListOp; /**< Puntatore alle operazioni per la lista */
	int ReturnStatus; /**< Codice di ritorno delle funzioni */
	NODE **AdjList;   /**< Puntatore temporaneo alle liste di adiacenza */

	AdjList = (NODE **)DataStructure;

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
		DataStructure = List_Insert( (void *)TempEdge, (NODE *)( AdjList[Source] ), &ReturnStatus, ListOp ); 
		//dealloco la struttura delle operazioni per la lista
		free( ListOp );
	}
	else 
	{
		//TODO ritornare codice di errore
	}
}


#ifdef IMPLEMENTED
void AddEdgeAdjMatrix( void *DataStructure, int Source, int Destination, double Weight )
{
	//Recupero l'EDGE_M di posto [Source][Destination]
	//Imposto Exist = 1
	//Copio Weight nell'arco recuperato
}

void DeallocateAdjacencyList( void *DataStructure, int NumVertices )
{
	//Richiamo List_Destroy su ogni elemento di DataStructure
	//Dealloco DataStructure
}

void DeallocateAdjacencyMatrix( void *DataStructure, int NumVertices )
{
	//Dealloco ogni array di EDGE_M che compone DataStructure
	//Dealloco DataStructure
}
#endif
/**
 * OPERAZIONI PER LISTA
 * */
OPERATIONS *InitOperationAdjList( void )
{
	OPERATIONS *InnerOp;

	InnerOp = (OPERATIONS *)malloc( sizeof(OPERATIONS) );
	if( InnerOp != NULL )
	{
		InnerOp->InitNode = InitNodeAdjList;
		InnerOp->Compare = NULL;
		InnerOp->Delete = DeleteNodeAdjList;
		InnerOp->Print = NULL;
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
void *DeleteNodeAdjList( void *InputValue, void *Edge )
{
	free( Edge );
}
