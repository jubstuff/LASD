/*=============================================================================
 *
 * Nome File: graph.c
 *
 * Scopo: 
 *
 * Data Creazione: 10-05-2011
 *
 * Ultima Modifica: mer 11 mag 2011 23:11:00 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/

GRAPH *InitializeGraph( int MaxNumVertices, OPERATIONS *Op )
{
	GRAPH *G; /**< Variabile temporanea */
	int i; /**< Contatore per cicli */

	//Allocare la struct GRAPH
	//Impostare MaxNumVertices a MaxNumVertices + REALLOC_SIZE
	//Impostare NumVertices a zero
	//Allocare l'array di V_DETAILS[MaxNumVertices]
	//Inizializzare l'array di V_DETAILS
	// - InDegree = 0
	// - OutDegree = 0
	// - Label = NULL
	// - Processed = 0
	// Copiare Op nel campo del GRAPH
	// Allocare la struttura dati
	return G;
}

void DestroyGraph( GRAPH *G )
{
	//Dealloco la struttura dati rappresentate il grafo
	//Dealloco l'array di V_DETAILS, avendo cura di deallocare 
	//gli elementi contenuti in ogni singolo elemento
	//Dealloco il GRAPH
}

void InsertEdge( GRAPH *G, int Source, int Destination, double Weight )
{
	//Incremento di 1 il grado entrante del vertice VertexTo
	//Incremento di 1 il grado uscente del vertice VertexFrom
	//Richiamo il metodo AddEdge da Op
	//Imposto il peso dell'arco
}

void InsertVertex( GRAPH *G, char *Label, void *Data )
{

	//Se NumVertici = MaxNumVertices
	//  - Incremento MaxNumVertices di REALLOC_SIZE
	//  - Realloco V_DETAILS[MaxNumVertices] e inizializzo i nuovi elementi, (da NumVertices in poi)
	//  - Richiamo ALLOCATE_DS con i parametri adatti
	//
	//Imposto l'etichetta relativa al nodo G->NumVertices 
	//Copio i dati relativi al nuovo vertice
	//Incremento il numero di vertici del grafo
}

void *AllocateAdjacencyList( int MaxNumVertices )
{
	//Alloco un array di puntatori a NODE[MaxNumVertices]
	//Inizializzo a NULL tutti i puntatori
	//Restituisco il puntatore all'array
}

void *AllocateAdjacencyMatrix( int MaxNumVertices )
{
	//Alloco un array di puntatori a puntatori di EDGE_M[MaxNumVertices]
	//Per ogni elemento dell'array alloco un array di EDGE_M[MaxNumVertices]
	//Inizializzo tutti gli elementi: Exist = 0, Weight = 0
	//Restituisco il puntatore alla matrice
}

void AddEdgeAdjList( void *DataStructure, int Source, int Destination, double Weight ) 
{
	//Alloco un EDGE_L a
	// - imposto a.DestVertex = Destination
	// - imposto a.Weight = Weight
	//Inserisco il nodo nella lista relativa a DataStructure[Source], passando a come valore
}

void AddEdgeAdjMatrix( void *DataStructure, int Source, int Destination, double Weight )
{
	//Recupero l'EDGE_M di posto [Source][Destination]
	//Imposto Exist = 1
	//Copio Weight nell'arco recuperato
}
