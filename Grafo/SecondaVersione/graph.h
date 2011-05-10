/*=============================================================================
 *
 * Nome File: graph.h
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: mar 10 mag 2011 22:38:52 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

/**
 * Alloca e inizializza una struttura dati atta a contenere la struttura
 * sul grafo
 * */
typedef void *(*ALLOCATE_DS)( void *DataStructure, int NumVertices, int MaxVertices ); 
typedef void (*DEALLOCATE_DS)(void *DataStructure ); 

typedef struct g_operations_tag
{
	ALLOCATE_DS AllocateDS;
    DEALLOCATE_DS DeallocateDS;
} G_OPERATIONS;

typedef struct vertex_details_tag
{
	char *Label;            /**< Etichetta dei vertici */
	int  InDegree;          /**< Grado entrante del vertice */
	int  OutDegree;         /**< Grado uscente del vertice */
	int  Processed;         /**< Colorazione del vertice */
} V_DETAILS;

typedef struct graph_tag
{
	void *DataStructure;      /**< Struttura dati rappresentante il grafo */
	int MaxVertices;          /**< Massimo Numero di vertici */
	int NumVertices;          /**< Numero Attuale di vertici */
	V_DETAILS *VertexDetails; /**< Informazioni sui vertici */
    G_OPERATIONS *Op;         /**< Metodi operanti sul grafo */
} GRAPH;                                                               


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

#endif /* _GRAPH_H_ */
