/*=============================================================================
 *
 * Nome File: graph.h
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: ven 13 mag 2011 13:10:11 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "../../lib/lista.h"
#define REALLOC_SIZE 5

typedef struct g_operations_tag G_OPERATIONS;

typedef struct vertex_details_tag
{
	char *Label;    /**< Etichetta dei vertici */
	int  InDegree;  /**< Grado entrante del vertice */
	int  OutDegree; /**< Grado uscente del vertice */
	int  Processed; /**< Colorazione del vertice */
	void *Data;     /**< Dati associati al vertice */
} V_DETAILS;

typedef struct graph_tag
{
	void *DataStructure;      /**< Struttura dati rappresentante il grafo */
	int MaxNumVertices;       /**< Massimo Numero di vertici */
	int NumVertices;          /**< Numero Attuale di vertici */
	V_DETAILS *VertexDetails; /**< Informazioni sui vertici */
    G_OPERATIONS *Op;         /**< Metodi operanti sul grafo */
} GRAPH;                                                               

/**
 * Alloca e inizializza una struttura dati atta a contenere la struttura
 * sul grafo
 * */
typedef void *(*ALLOCATE_DS)( void *DataStructure, int NumVertices, int MaxVertices ); 
typedef void (*DEALLOCATE_DS)(void *DataStructure, int NumVertices ); 
typedef void (*ADD_EDGE)(GRAPH *G, int Source, int Destination, double Weight);
typedef void (*PRINT_DS)( GRAPH *G );

typedef struct g_operations_tag
{
	ALLOCATE_DS AllocateDS;
    DEALLOCATE_DS DeallocateDS;
	ADD_EDGE AddEdge;
	PRINT_DS PrintDS;
} G_OPERATIONS;

typedef struct edge_m_tag
{
	int    Exist;  /**< 1 se l'arco esiste, 0 altrimenti */
	double Weight; /**< Peso associato all'arco, default 0 */
} EDGE_M;

typedef struct edge_l_tag
{
	int    DestVertex; /**< Destinazione dell'arco */
	double Weight;     /**< Peso associato all'arco, default 0 */
} EDGE_L;

/**
 * DEFINIZIONI FUNZIONI GRAFO
 * */
GRAPH *InitializeGraph( int MaxNumVertices, G_OPERATIONS *Op );
void DestroyGraph( GRAPH *G );
void InsertEdge( GRAPH *G, int Source, int Destination, double Weight );
void InsertVertex( GRAPH *G, char *Label, void *Data );
void PrintGraph( GRAPH *G );

/**
 * OPERAZIONI PER LISTA
 * */
void *AllocateAdjacencyList( void *DataStructure, int NumVertices, int MaxNumVertices );
OPERATIONS *InitOperationAdjList( void );
void *InitNodeAdjList( void *Edge );
void DeleteNodeAdjList( void *InputValue, void *Edge );
void DeallocateAdjacencyList( void *DataStructure, int NumVertices );
void PrintAdjList( GRAPH *G );
/**
 * OPERAZIONI PER MATRICE
 * */
void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices, int MaxVertices );
void AddEdgeMatrix( GRAPH *G, int VertexFrom, int VertexTo, double Weight );
EDGE_M *GetCell( EDGE_M *Matrix, int Dim, int Row, int Column );
void DeallocateAdjacencyMatrix( void *DataStructure, int NumVertices );
void PrintAdjMatrix( GRAPH *G );
#endif /* _GRAPH_H_ */                      

