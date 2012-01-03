/**
 * jvertex.h
 *
 * Definizioni tipo di dato e funzioni per i vertici del grafo
 *
 * Autore: Giustino Borzacchiello matr. 566/3291 - giustinob@gmail.com
 * */
#ifndef JVERTEX_H
#define JVERTEX_H

#include "errors.h"
#include "lista.h"

/**
 * DEFINIZIONE TIPI DI DATO
 * */

typedef struct jvertex_tag
{
    int Id;        /**< ID univoco */
	char *Label;   /**< Vertex's Label */
	void *Data;    /**< Dati associati al vertice */
	int  AdjIndex; /**< Puntatore alle informazioni di adiacenza */
} J_VERTEX;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Operazioni sui vertici

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

J_STATUS JVertex_New( J_VERTEX **V );

void JVertex_Destroy( J_VERTEX *V );

void JVertex_CopyLabel( char **Dest, J_VERTEX *V ); 

char *JVertex_GetLabel( J_VERTEX *V );

J_STATUS JVertex_GetLengthLabel( int *Length, J_VERTEX *V );

J_STATUS JVertex_SetLabel( char *, J_VERTEX *);

int VertexCmp( const void *Vertex1, const void *Vertex2 );

void JVertex_SetAdjIndex( int AdjIndex, J_VERTEX *V);
#endif
