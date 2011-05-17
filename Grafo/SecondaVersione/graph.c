/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: mar 17 mag 2011 22:48:39 CEST
 *
 * Autore: Giustino Borzacchiello - giustinob@gmail.com
 *
 *
 =============================================================================*/
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int InsertVertex( GRAPH *G, char *Label, void *Data )
{
	V_DETAILS **TempVDetails; /**< Variabile di appoggio controllare il valore restituito da realloc */
    V_DETAILS *TempVertex; /**< Vertice temporaneo di appoggio */
	int ReturnStatus; /**< Valore di ritorno della funzione */

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
			ReturnStatus = ERR_REALLOC;
		}
		else
	   	{
			//La realloc è andata a buon fine
			G->VertexDetails = TempVDetails;
		}
		//  - Richiamo ALLOCATE_DS con i parametri adatti
		G->DataStructure = G->Op->AllocateDS( G->DataStructure, G->NumVertices, G->MaxNumVertices );
	}
	if( ReturnStatus != ERR_REALLOC )
	{
		TempVertex = (V_DETAILS *)malloc( sizeof( V_DETAILS ) );
		if( TempVertex )
		{
			//Imposto l'etichetta relativa al nodo G->NumVertices 
			TempVertex->Label = Label;
			//Copio i dati relativi al nuovo vertice
			TempVertex->Data = Data;
			G->VertexDetails[G->NumVertices] = TempVertex;
			//Incremento il numero di vertici del grafo
			G->NumVertices++;
		}
		else
		{
			ReturnStatus = ERR_MALLOC; 
		}
	}
	return ReturnStatus;
}
void DestroyGraph( GRAPH *G )
{
	int i; /**< Contatore per cicli */
	
	//Dealloco la struttura dati rappresentate il grafo
	G->Op->DeallocateDS( G->DataStructure, G->NumVertices );
	//Dealloco l'array di V_DETAILS, avendo cura di deallocare 
	//gli elementi contenuti in ogni singolo elemento
	for( i = 0; i < G->NumVertices; i++ ) //TODO Controllare se qui deve essere MAXVERTICES
	{
		if( G->VertexDetails[i] )
		{
			free( G->VertexDetails[i]->Label );
			if( G->VertexDetails[i]->Data )
			{
				free( G->VertexDetails[i]->Data );
			}
			free( G->VertexDetails[i] );
		}
	}
	free( G->VertexDetails );
	//Dealloco il GRAPH
	free( G );
}

int SearchLabel( GRAPH *G, const char *Label )
{
	int ReturnStatus = -1;
	int ExaminedVertex;

	ExaminedVertex = 0;
	while( (ReturnStatus == -1) && ExaminedVertex < G->NumVertices ) //TODO controllare sempre i limiti
	{
		if( strcmp( G->VertexDetails[ExaminedVertex]->Label, Label ) == 0 )
		{
			ReturnStatus = ExaminedVertex;
		}
		ExaminedVertex++;
	}

	return ReturnStatus;
}

void InsertEdge( GRAPH *G, int Source, int Destination, double Weight )
{
	//Incremento di 1 il grado entrante del vertice Destination
	G->VertexDetails[Destination]->InDegree += 1;
	//Incremento di 1 il grado uscente del vertice Source
	G->VertexDetails[Source]->OutDegree += 1;
	//Richiamo il metodo AddEdge da Op
	G->Op->AddEdge( G, Source, Destination, Weight );
}

void PrintGraph( GRAPH *G )
{
	//Richiamo la stampa relativa alla struttura dati idonea
	G->Op->PrintDS( G );
}
