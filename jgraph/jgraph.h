/*
 * jgraph.h
 *
 * Scopo : Intestazioni per la libreria jgraph
 *
 * Autore : Giustino Borzacchiello
 * */

#define NUM_VERTICES 100

typedef struct jedge_tag {
	char *Label;
	double *Weight;
} J_EDGE;

typedef struct jgraph_tag {
	J_EDGE AdjLists[NUM_VERTICES];
} J_GRAPH;

J_GRAPH InitializeGraph( );
