/*=============================================================================
 *
 * Nome File: graph.h
 *
 * Scopo: Definizioni delle strutture per una libreria sui grafi
 *
 * Data Creazione: 06-05-2011
 *
 * Ultima Modifica: sab 07 mag 2011 12:33:07 CEST
 *
 * Autore: Giustino Borzacchiello - 566/3291 - giustinob@gmail.com
 *
 *
 =============================================================================*/

#define REALLOC_SIZE 5 /**< Numeri di vertici aggiuntivi da allocare */

/**
 * Alloca e inizializza una struttura dati atta a contenere informazioni
 * sul grafo
 * */
typedef void *(*ALLOCATE_DS)(void *DataStructure, int NumVertices); 
typedef void (*DEALLOCATE_DS)(void *DataStructure ); 

typedef struct operations_tag
{
	ALLOCATE_DS AllocateDS;
    DEALLOCATE_DS DeallocateDS;
} G_OPERATIONS;

/**
 * Struct per la definizione di un arco utilizzato nella rappresentazione del 
 * grafo a matrice di adiacenza
 * */
typedef struct edge_m_tag
{
	int    Exist;  /**< 1 se l'arco esiste, 0 altrimenti */
	double Weight; /**< Peso associato all'arco, default 0 */
} EDGE_M;
/**
 * Struct per la definizione di un grafo tramite una matrice di adiacenza
 * */
typedef struct graph_tag
{
	EDGE_M *AdjacencyMatrix;  /**< Matrice di adiacenza */
	void *DataStructure;      /**< Struttura dati rappresentante il grafo */
	int MaxVertices;          /**< Massimo Numero di vertici */
	int NumVertices;          /**< Numero Attuale di vertici */
	char **Labels;            /**< Etichette dei vertici */
    G_OPERATIONS *Op;         /**< Metodi operanti sul grafo */
} GRAPH;

GRAPH *InitGraph( int MaxVertices );
void *AllocateAdjacencyMatrix( void *DataStructure, int NumVertices );
void FreeAdjacencyMatrix( void *DataStructure );
void AddEdge( GRAPH *G, int VertexFrom, int VertexTo, double Weight );
void AddVertex( GRAPH *G, char *Label );
void PrintGraph( GRAPH *G );
void DestroyGraph( GRAPH *G );
