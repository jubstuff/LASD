/*=============================================================================
 *
 * Nome File: graph.h
 *
 * Scopo: Definizioni delle strutture per una libreria sui grafi
 *
 * Data Creazione: 06-05-2011
 *
 * Ultima Modifica: ven 06 mag 2011 23:21:11 CEST
 *
 * Autore: Giustino Borzacchiello - 566/3291 - giustinob@gmail.com
 *
 *
 =============================================================================*/


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
typedef struct graph_matrix_tag
{
	EDGE_M *AdjacencyMatrix; /**< Matrice di adiacenza */
	int MaxVertices;          /**< Massimo Numero di vertici */
	int NumVertices;          /**< Numero Attuale di vertici */
	char **Labels;            /**< Etichette dei vertici */
} GRAPH_M;

GRAPH_M *InitGraph( int MaxVertices );
void AddEdge( GRAPH_M *G, int VertexFrom, int VertexTo, double Weight );
void AddVertex( GRAPH_M *G, char *Label );
void PrintGraph( GRAPH_M *G );
