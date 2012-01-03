/**
 * Definizione interfaccia per l'insieme degli archi di un grafo
 *
 * eset sta per "edges set"
 *
 *
 * Data: 11/11/11
 *
 * Autore: Giustino Borzacchiello
 *
 *
 * */
#ifndef JESET_H
#define JESET_H

#include "errors.h"
#include "jvset.h"

/**
 * DEFINIZIONE TIPI DI DATO
 * */

typedef struct jeset_tag J_ESET;

/**
 * Inizializza l'insieme degli archi
 * */
J_STATUS JEset_New( int HintNumVertices, J_ESET **Set );

/**
 * Aggiunge un arco all'insieme
 * */
J_STATUS JEset_AddEdge( char *LabelSource, char *LabelDest, double Weight, J_VSET *VSet, J_ESET *ESet );

/**
 * Recupera il peso di un dato arco
 * */
J_STATUS JEset_GetEdgeWeight( char *LabelSource, char *LabelDest, double *Weight, J_ESET *Set);

/**
 * Rimuove un arco dall'insieme
 * */
J_STATUS JEset_RemoveEdge( char *LabelSource, char *LabelDest, J_ESET *Set );

/**
 * Dealloca l'insieme degli archi
 * */
void JEset_Destroy( J_ESET *Set );
/**
 * Associa un vertice ad una lista di adiacenza
 *
 * */
J_STATUS JEset_LinkAdjListAndVertex(J_VERTEX *Vertex, J_ESET *EdgeSet);

#endif
