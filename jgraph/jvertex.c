/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* Nome File : jvertex.c

* Scopo : Implementazione funzioni per il tipo di dato vertice

* Data di creazione : 03-01-2012

* Ultima modifica : 03-01-2012

* Autore : Giustino Borzacchiello - matr. 566/3291 - giustinob@gmail.com

_._._._._._._._._._._._._._._._._._._._._.*/

#include "lista.h"
#include "mem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "jvertex.h"

/*=======================DEFINIZIONE METODI PRIVATI==============================*/


/*==================FINE DEFINIZIONE METODI PRIVATI==============================*/

/**
 * JVertex_New
 *
 * Alloca un nuovo vertice e lo inizializza
 * */
J_STATUS JVertex_New( J_VERTEX **V )
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    /* Alloco un nuovo vertice */
    ReturnStatus = MemAlloc( sizeof(J_VERTEX), (void **)V );
    if( ReturnStatus == SUCCESS )
    {
        /* Se il vertice è stato correttamente allocato, inizializzalo */
        (*V)->Label = NULL;
        (*V)->Data = NULL;
        (*V)->Id = 0;
        (*V)->AdjIndex = -1;
    }

    return ReturnStatus;
}

/**
 * Dealloca un vertice e i dati associati
 *
 * */
void JVertex_Destroy( J_VERTEX *V )
{
    if( V != NULL )
    {
        /* Se il vertice esiste, dealloca tutte le info ad esso associate */
        MemFree( (void **)&V->Label );
        /* TODO deallocare dati associati al vertice */
        MemFree( (void **)&V );
    }
}

/* 
 * Copia l'etichetta del vertice.
 *
 * Se l'etichetta è impostata, la copia nella stringa Dest (che deve essere
 * allocata e sufficientemente grande).
 * Altrimenti imposta Dest a NULL
 *
 * */
void JVertex_CopyLabel( char **Dest, J_VERTEX *V )
{
    if( V && V->Label )
    {
        /* Se il vertice esiste e l'etichetta è definita,
         * copiala nel vettore passato in input
         * */
        strcpy( *Dest, V->Label );
    }
    else
    {
        *Dest = NULL;
    }
}

char *JVertex_GetLabel( J_VERTEX *V )
{
    return V->Label;
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

    if( V && V->Label )
    { 
        /* Se l'etichetta è impostata, ne restituisce la lunghezza */
        *Length = strlen(V->Label);
    }
    else
    {
        /* Altrimenti imposta la lunghezza a zero, e restituisce ERROR */
        *Length = 0;
        ReturnStatus = ERROR;
    }

    return ReturnStatus;
}

/**
 * Imposta l'etichetta ad un vertice
 *
 * Alloca un vettore di caratteri dinamicamente e lo utilizza per memorizzare l'etichetta del vertice 
 * */
J_STATUS JVertex_SetLabel( char *Label, J_VERTEX *V)
{
    int LabelLen;
    J_STATUS ReturnStatus;

    /* Recupero la lunghezza dell'etichetta passata in input */
    LabelLen = strlen(Label);

    /* Alloco un vettore di caratteri atto a contenere la stringa */
    ReturnStatus = MemAlloc( LabelLen + 1, (void **)&(V->Label) );
    if( ReturnStatus == SUCCESS )
    {
        /* Se è stato allocato correttamente, vi copio la stringa in input */
        strcpy(V->Label, Label);
    }

    return ReturnStatus;
}
/**
 * Imposta l'indice di adiacenza di un vettore
 *
 * */
void JVertex_SetAdjIndex( int AdjIndex, J_VERTEX *V)
{
    V->AdjIndex = AdjIndex;
}

/**
 * Confronta due vertici per ID
 *
 * */
int VertexCmp( const void *Vertex1, const void *Vertex2 )
{
	int ReturnValue;
	J_VERTEX *First = (J_VERTEX *)Vertex1;
	J_VERTEX *Second = (J_VERTEX *)Vertex2;

	if ( First->Id < Second->Id )
	{
		ReturnValue = -1;
	}
	else if ( First->Id == Second->Id )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;
}

