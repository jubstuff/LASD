/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: mar 17 mag 2011 20:18:13 CEST
 *
 * Autore: Giustino Borzacchiello - giustinob@gmail.com
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
	G = (GRAPH *)malloc( sizeof( GRAPH ) ); 
	if( G )
	{
		//Impostare MaxNumVertices a MaxNumVertices + REALLOC_SIZE
		G->MaxNumVertices = MaxNumVertices + REALLOC_SIZE;
		//Impostare NumVertices a zero
		G->NumVertices = 0;
		//Allocare l'array di V_DETAILS[MaxNumVertices]
		G->VertexDetails = (V_DETAILS **)malloc( G->MaxNumVertices * sizeof( V_DETAILS * ) );
		if( G->VertexDetails )
		{
			//Inizializzare l'array di V_DETAILS
			for( i = 0; i < G->MaxNumVertices; i++ )
			{
				G->VertexDetails[i] = NULL;

			}
			// Copiare Op nel campo del GRAPH
			G->Op = Op;
			// Allocare la struttura dati

			/* Il puntatore a DataStructure deve essere inizializzato a NULL perché 
			 * altrimenti passerei alla funzione realloc, presente in AllocateDS un
			 * riferimento non valido */
			G->DataStructure = NULL;
			G->DataStructure = G->Op->AllocateDS( G->DataStructure, G->NumVertices, G->MaxNumVertices );
		}
	}
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

int InsertVertex( GRAPH *G, char *Label, void *Data )
{
	V_DETAILS **TempVDetails; /**< Variabile di appoggio controllare il valore restituito da realloc */
    V_DETAILS *TempVertex; /**< Vertice temporaneo di appoggio */
	int ReturnStatus;

	ReturnStatus = 0;

	//Se NumVertici = MaxNumVertices
	if( G->NumVertices == G->MaxNumVertices )
	{
		//  - Incremento MaxNumVertices di REALLOC_SIZE    //TODO ma si può accorpare con l'inizializzazione fatta all'inizio?
        G->MaxNumVertices += REALLOC_SIZE;
		//  - Realloco V_DETAILS[MaxNumVertices] e inizializzo i nuovi elementi, (da NumVertices in poi)
		TempVDetails = (V_DETAILS **)realloc( G->VertexDetails, G->MaxNumVertices * sizeof( V_DETAILS *) );
		if( TempVDetails == NULL )
		{
			//La realloc ha fallito, ma G->VertexDetails è ancora un puntatore valido.
			ReturnStatus = E_REALLOC;
		}
		else
	   	{
			//La realloc è andata a buon fine
			G->VertexDetails = TempVDetails;
		}
		//  - Richiamo ALLOCATE_DS con i parametri adatti
		G->DataStructure = G->Op->AllocateDS( G->DataStructure, G->NumVertices, G->MaxNumVertices );
	}
	if( ReturnStatus != E_REALLOC )
	{
		TempVertex = (V_DETAILS *)malloc( sizeof( V_DETAILS ) );
		if( TempVertex )
		{
			//Imposto l'etichetta relativa al nodo G->NumVertices 
			TempVertex.Label = Label;
			//Copio i dati relativi al nuovo vertice
			TempVertex.Data = Data;
			G->VertexDetails[G->NumVertices] = TempVertex;
			//Incremento il numero di vertici del grafo
			G->NumVertices++;
		}
		else
		{
			ReturnStatus = -1; //TODO creare un insieme di error codes
		}
	}
	return ReturnStatus;
}

void PrintGraph( GRAPH *G )
{
	//Richiamo la stampa relativa alla struttura dati idonea
	G->Op->PrintDS( G );
}

