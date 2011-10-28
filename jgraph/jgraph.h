/*
 * jgraph.h
 *
 * Scopo : Intestazioni per la libreria jgraph
 *
 * Autore : Giustino Borzacchiello
 * */
#ifndef JGRAPH_H
#define JGRAPH_H

#include "errors.h"

typedef struct graph_op_tag JGRAPH_METHODS;

typedef struct graph_tag J_GRAPH;

/*
 * Funzioni per la gestione del grafo
 * */

/*
 * Inizializza il grafo ed i relativi metodi
 * */
J_STATUS JGraph_Init( J_GRAPH **G, JGRAPH_METHODS *Op );

/**
 * Aggiunge un vertice con etichetta Label e dati associati al grafo
 * */
J_STATUS JGraph_AddVertex( char *Label, void *Data, J_GRAPH *G );

/**
 * Aggiunge un arco (con peso Weight) al grafo, dal vertice con etichetta SourceLabel al vertice
 * con etichetta DestLabel
 * */
J_STATUS JGraph_AddEdge( char *SourceLabel, char *DestLabel, double Weight, J_GRAPH *G);

/**
 * Rimuove dal grafo il vertice con etichetta Label (se esiste)
 * */
J_STATUS JGraph_RemoveVertex( char *Label, J_GRAPH *G );

/**
 * Rimuove dal grafo l'arco tra i vertici identificati da SourceLabel e DestLabel
 * */
J_STATUS JGraph_RemoveEdge( char *SourceLabel, char *DestLabel, J_GRAPH *G );

/**
 * Dealloca tutti i vertici, tutti gli archi ed il grafo stesso
 * */
void     JGraph_Destroy( J_GRAPH *G );

#endif
