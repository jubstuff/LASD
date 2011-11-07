/**
 * lista.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 05/04/11
 *
 * Realizza alcune semplici funzioni per una lista, quali:
 *  - inserimento di un nodo
 *  - cancellazione di un nodo
 *  - stampa della lista
 *  - cancellazione di tutti i nodi della lista
 *  - cancellazione di nodi compresi in un intervallo
 * 
 * La lista è di tipo a singola concatenazione.
 * 
 */

#ifndef _LISTA_H_
#define _LISTA_H_
#include "errors.h"

/*=============================================================================*
 * Definizioni struttura nodo
 =============================================================================*/
typedef struct node_tag NODE;

typedef struct list_op_tag JLIST_METHODS;

typedef struct list_tag J_LIST;


/*=============================================================================*
 * Definizioni tipi puntatori a funzione
 =============================================================================*/

/**
 * Una funzione che confronta due elementi
 *
 * @param Arg1 Riferimento al primo elemento da confrontare
 * @param Arg2 Riferimento al secondo elemento da confrontare
 *
 * @return {< 0, 0, > 0} se (Arg1 < Arg2), (Arg1 == Arg2), (Arg1 > Arg2), rispettivamente
 *
 * NOTE
 * È responsabilità della funzione gestire eventuali valori NULL
 * */
typedef int (*COMPARATOR)(const void *Arg1, const void *Arg2); 

/**
 * Una funzione che inizializza il campo del nodo
 *
 * @param Value Riferimento al valore da copiare o associare al campo del nodo
 *
 * @return Il riferimento al nuovo valore allocato
 * */
typedef void *(*INITIALIZER)( void *Value );

/**                                
 * Una funzione che dealloca il valore memorizzato nel campo di un nodo
 *
 * NOTA
 * In linea generale questa funzione è speculare ad INITIALIZER
 *
 * @param Value Riferimento al valore da deallocare
 * */
typedef void (*DELETER)(void *InputValue, void *NodeInfo );
/**
 * Una funzione che stampa a video il valore memorizzato nel campo di un nodo
 *
 * @param Value Riferimento al valore da stampare
 * */
typedef void (*PRINTER)(const void *Value);

/**
 * Una funzione che gestisce l'occorrenza di nodi duplicati della lista all'atto
 * dell'inserimento
 *
 * @param Value Riferimento al valore passato in input
 * @param CurrentNode Riferimento al nodo in cui è stato trovato il duplicato
 *
 * TODO Ci puo stare NODE come tipo qui? No, perché in ogni caso l'utente non 
 * saprebbe come gestirlo. Quindi si dovrebbe rimuovere. O bisognerebbe creare
 * dei metodi per gestire il nodo a cui l'utente può avere accesso.
 * */
typedef void (*DUPLICATE)( void *Value, NODE *CurrentNode );

/**
 * Una funzione che copia il valore della chiave del nodo passato in input
 *
 * */
typdef void (*GETTER)( const void *NodeValue, void **OutputValue );

/*=============================================================================*
 * Definizioni struttura operazioni di gestione dei nodi
 =============================================================================*/

/**
 * Questa struct contiene tutte le operazioni che permettono la gestione del 
 * particolare tipo di nodo associato ad una lista.
 *
 * La libreria si aspetta che queste funzioni seguano le linee guida presentate
 * nella descrizione di ogni tipo di puntatore a funzione.
 *
 * */
struct list_op_tag {
	COMPARATOR Compare;        /**< Confronta due nodi */
	INITIALIZER InitNode;      /**< Inizializza un nodo */
	DELETER Delete;            /**< Elimina un nodo */
	PRINTER Print;             /**< Stampa un nodo */
	DUPLICATE ManageDuplicate; /**< Gestisce nodi duplicati */
	GETTER GetNodeValue;       /**< Recupera la chiave del nodo */
};


/*==============================================================================
 * Funzioni per la gestione della lista
 *============================================================================*/

int      JList_isEmpty( J_LIST *L );

J_STATUS JList_Init( J_LIST **L, JLIST_METHODS *Op );

J_STATUS JList_OrderedInsert( void *Value, J_LIST *L );

J_STATUS JList_HeadInsert( void *Value, J_LIST *L );

J_STATUS JList_DeleteNode( void *Value, J_LIST *L );

J_STATUS JList_Search( void *Value, J_LIST *L, NODE **NodeFound );

void     JList_DeleteRange( void *Inf, void  *Sup, J_LIST *L );

void     JList_Destroy( J_LIST *L );

void     JList_Print( J_LIST *L );

/*==============================================================================
 * Funzioni per la gestione dei nodi
 *============================================================================*/

void *JNode_GetData( NODE *N );


#endif /* _LISTA_H_ */
