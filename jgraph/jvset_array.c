#include "jvset.h"
#include "mem.h"
#include <string.h>
#include <stdlib.h>

/**
 * Implementazione dell'interfaccia J_VSET utilizzando un array
 *
 * */
struct jvertex_tag
{
	char *Label; /**< Vertex's Label */
};

struct jvset_tag
{
    J_VERTEX *Vertices; /**< Array contenente i vertici */
    int NumActiveVertices; /**< Numero di vertici inseriti nell'insieme */
    int NextFreeVertex; /**< Indice della prossima locazione libera */
};

/**
 * Inizializza l'insieme
 * */
J_STATUS JVset_Init( int HintNumVertices, J_VSET **Set )
{
   J_STATUS ReturnStatus;
   int i; /**< Contatore per cicli */

   ReturnStatus = SUCCESS;


   /* Alloco la struct che rappresenta l'insieme */
   ReturnStatus = MemAlloc(sizeof(J_VSET), (void **)Set);

   if( ReturnStatus == SUCCESS )
   {
       /* Se l'insieme è stato correttamente allocato */

       /* - inizializzo gli indici */
       (*Set)->NumActiveVertices = 0;
       (*Set)->NextFreeVertex = 0;

       /* - alloco l'array singoli vertici */
       ReturnStatus = MemAlloc( HintNumVertices * sizeof(J_VERTEX), 
               (void **)&( (*Set)->Vertices ) );

       if( ReturnStatus == SUCCESS )
       {
           for( i = 0; i < HintNumVertices; i++ )
           {
               JVertex_Init( &(*Set)->Vertices[i] );
           }
       }
   }

   return ReturnStatus;
}

/**
 * Dealloca l'insieme di vertici
 * */
void JVset_Destroy( J_VSET *Set )
{
    MemFree( (void **)&( Set->Vertices ) );
    MemFree( (void **)&Set );
}

/**
 * Aggiunge un vertice con etichetta Label e dati associati all'insieme
 * */
J_STATUS JVset_AddVertex( char *Label, void *Data, J_VSET *Set )
{
    int FreeLoc; /**< Locazione libera in cui inserire */
    J_STATUS ReturnStatus; /**< Valore di ritorno */

    FreeLoc = Set->NextFreeVertex;
    /* Impostare l'etichetta del nuovo vertice */
    ReturnStatus = JVertex_SetLabel(Label, &(Set->Vertices[FreeLoc]) );
    if( ReturnStatus == SUCCESS )
    {
        /* Aggiornare il numero di vertici inseriti */
        Set->NumActiveVertices += 1;
        /* Aggiornare il prossimo vertice libero */
        Set->NextFreeVertex += 1;
    }

    return ReturnStatus;
}

#ifdef ASD

/**
 * Rimuove un vertice dall'insieme
 * */
J_STATUS JVset_RemoveVertex( char *Label, J_VSET *Set )
{
}

/**
 * Recupera l'informazione associata al vertice
 * */
J_STATUS JVset_GetVertexData( char *Label, void *Data, J_VSET *Set )
{
}

#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * METODI PER VERTICI
 *
 * */

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
