/**
 * lista.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 05/04/11
 * @package ListaGenerale
 *
 * Realizza alcune semplici funzioni per una lista, quali:
 *  - inserimento di un nodo
 *  - cancellazione di un nodo
 *  - stampa della lista
 *  - cancellazione di tutti i nodi della lista
 * 
 * La lista è di tipo a singola concatenazione.
 * 
 */
#ifndef _LISTA_H_
#define _LISTA_H_


#define E_MALLOC    1   //Errore nella chiamata a malloc
#define W_DUPLICATE 2   //Warning nell'inserimento di un nodo duplicato
#define I_REMOVED   3   //Notifica che il nodo è stato rimosso correttamente

/*=============================================================================*
 * Definizioni tipi puntatori a funzione
 =============================================================================*/
typedef int (*COMPARATOR)(const void *Arg1, const void *Arg2); 

typedef void *(*INITIALIZER)( void *Value );

typedef void (*DELETER)(void *Value);

typedef void (*PRINTER)(void *Value);
/*=============================================================================*
 * Definizioni strutture
 =============================================================================*/

typedef struct node {
	struct node *Next; /**< Puntatore al nodo successivo */
	void *Info;        /**< Campo del nodo */
} NODE;

typedef struct operations {
	COMPARATOR Compare;
	INITIALIZER InitNode;
	DELETER DeleteNode;
	PRINTER Print;
} OPERATIONS;

typedef struct list_tag
{
	NODE *Head; /**< Testa della lista */
	OPERATIONS *Op; /**< Operazioni dipendenti dal tipo di dato associato alla lista */

} LIST;

/*==============================================================================
 * Funzioni per la gestione della lista
 *============================================================================*/
/**
 * Inizializza la lista
 *
 * @param L Lista da inizializzare, deve puntare ad un'area di memoria allocata
 * @param Op Operazioni sul tipo di dato che verrà memorizzato nella lista
 *
 * @return 0 se l'operazione è andata a buon fine, -1 altrimenti.
 *
 * */
void List_Init(LIST *L, OPERATIONS *Op);

/**
 * Ispeziona la lista, controllando se è vuota
 *
 * @param L Lista da controllare
 * 
 * @return 1 se la lista è vuota, 0 altrimenti
 *
 * */
int List_IsEmpty(LIST *L);

/**
 * Inserisce un nodo nella lista
 *
 * Inserisce un nodo con campo pari a <Value> nella lista <L>
 * */
int List_Insert( void *Value, LIST *L );

NODE *List_RecursiveOrderedInsert ( void *Value, NODE *Current, int *ReturnStatus, OPERATIONS *Op );

NODE *ListCreateNewNode(void *Value, OPERATIONS *Op);

/**
 * Cancella un nodo con campo pari a <Value> dalla Lista <L>
 * */
int List_Delete( void *Value, LIST *L );
/**
 * Utilizza un approccio ricorsivo per cancellare il nodo con campo
 * pari a <Value> dalla lista con testa <Current>
 * */
NODE *List_RecursiveDelete(void *Value, NODE *Current, int *ReturnStatus, OPERATIONS *Op) ;
/**
 * Permette di cancellare tutti i nodi i cui campi sono compresi tra Inf e Sup,
 * estremi compresi
 * */
NODE *List_RecursiveDeleteRange( NODE *Current, void *Inf, void *Sup, OPERATIONS *Op );

/**
 * Dealloca tutti i nodi della lista
 *
 */
NODE *List_RecursiveDestroy(NODE *Current, OPERATIONS *Op);

/**
 * Stampa a video tutti i nodi della lista L
 * */
int List_Print( LIST *L );
/**
 * Stampa a video tutti i nodi della lista con testa Current
 * */
void List_RecursivePrint( NODE *Current, OPERATIONS *Op );
#endif /* _LISTA_H_ */
