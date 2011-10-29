#include "jvertex.h"
#include "errors.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct jvertex_tag
{
	char *Label; /**< Vertex's Label */
};

J_STATUS JVertex_New( J_VERTEX **V )
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    ReturnStatus = MemAlloc( sizeof(J_VERTEX), (void **)V );
    if( ReturnStatus == SUCCESS )
    {
        JVertex_Init( *V );
    }

    return ReturnStatus;
}

/**
 * Inizializza un vertice
 *
 * Inizializza tutti i valori di un vertice in uno stato consistente.
 *
 * */
void JVertex_Init( J_VERTEX *V )
{
    V->Label = NULL;
}

void JVertex_Delete( J_VERTEX *V )
{
}

/* 
 * Recupera l'etichetta del vertice V.
 *
 * Se l'etichetta è impostata, la copia nella stringa Dest (che deve essere
 * allocata e sufficientemente grande).
 * Altrimenti imposta Dest a NULL
 *
 * */
void JVertex_GetLabel( char **Dest, J_VERTEX *V )
{
    if( V->Label != NULL )
    {
        strcpy( *Dest, V->Label );
    }
    else
    {
        *Dest = NULL;
    }
}

/**
 * Recupera la lunghezza dell'etichetta del vertice V
 *
 * Se l'etichetta è impostata, ne copia la lunghezza in Length.
 * Altrimenti imposta Length a 0 e restituisce ERROR.
 *
 * */
J_STATUS JVertex_GetLengthLabel( int *Length, J_VERTEX *V )
{
    J_STATUS ReturnStatus; /**< stato di ritorno */

    ReturnStatus = SUCCESS;

    if( V->Label )
    { 
        /* Se l'etichetta è impostata, ne restituisce la lunghezza */
        *Length = strlen(V->Label);
    }
    else
    {
        /* Altrimenti la imposta a zero, e restituisce ERROR */
        *Length = 0;
        ReturnStatus = ERROR;
    }

    return ReturnStatus;
}

J_STATUS JVertex_SetLabel( char *Label, J_VERTEX *V)
{
    int LabelLen;
    J_STATUS ReturnStatus;

    LabelLen = strlen(Label);

    ReturnStatus = MemAlloc( LabelLen + 1, (void **)&(V->Label) );
    if( ReturnStatus == SUCCESS )
    {
        strcpy(V->Label, Label);
    }

    return ReturnStatus;
}

J_STATUS JVertex_CreateArray(int HintNumVertices, J_VERTEX **V)
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    return ReturnStatus;
}
