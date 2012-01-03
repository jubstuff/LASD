/**
 * Definizione interfaccia per l'insieme dei vertici per un grafo
 *
 * vset sta per "vertices set"
 *
 *
 * Data: 28/10/11
 *
 * Autore: Giustino Borzacchiello
 *
 *
 * */

#ifndef JVSET_H
#define JVSET_H

#include "errors.h"
#include "lista.h"
#include "jvertex.h"

typedef struct jvset_tag
{
    J_VERTEX **Vertices;   /**< Array contenente i vertici */
    int NumActiveVertices; /**< Numero di vertici inseriti nell'insieme */
    int Size;              /**< Numero totale di vertici */
    J_LIST *FreeList;      /**< Lista delle locazioni libere */
} J_VSET;

/**
 * Inizializza l'insieme
 * */
J_STATUS JVset_Init( int HintNumVertices, J_VSET **Set );

/**
 * Aggiunge un vertice con etichetta Label e dati associati all'insieme
 * */
J_STATUS JVset_AddVertex( char *Label, void *Data, J_VSET *Set );

/**
 * Rimuove un vertice dall'insieme
 * */
J_STATUS JVset_RemoveVertex( char *Label, J_VSET *Set );

/**
 * Dealloca l'insieme di vertici
 * */
void JVset_Destroy( J_VSET *Set );

/**
 * Recupera l'informazione associata al vertice
 * */
J_STATUS JVset_GetVertexData( char *Label, void *Data, J_VSET *Set );
/**
 * Recupera un vertice dall'insieme, data l'etichetta
 * */
J_STATUS JVset_FindVertexByLabel( char *Label, J_VERTEX **OutVertex, J_VSET *Set );
/**
 * Stampa le etichette dell'insieme dei vertici
 * */
void JVset_IterateOnSet( void (*action)(J_VERTEX *), J_VSET *Set );


#endif
