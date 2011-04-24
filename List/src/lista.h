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

typedef struct node {
	struct node *Next; /**< Puntatore al nodo successivo */
	void *Info;        /**< Campo del nodo */
} NODE;

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
 * @param Value Riferimento al valore da copiare nel campo del nodo
 *
 * @return Il riferimento al nuovo valore allocato
 * */
typedef void *(*INITIALIZER)( void *Value );

/**
 * Una funzione che dealloca il valore memorizzato in un nodo
 *
 * @param Value Riferimento al valore da deallocare
 * */
typedef void (*DELETER)(void *Value);

/**
 * Una funzione che stampa a video il valore memorizzato in un nodo
 *
 * @param Value Riferimento al valore da stampare
 * */
typedef void (*PRINTER)(const void *Value);

/**
 * Una funzione che gestisce l'inserimento di nodi duplicati della lista
 *
 * */
typedef void (*DUPLICATE)( void *Value, NODE *CurrentNode );

/*=============================================================================*
 * Definizioni strutture
 =============================================================================*/


typedef struct operations {
	COMPARATOR Compare;
	INITIALIZER InitNode;
	DELETER DeleteNode;
	PRINTER Print;
	DUPLICATE ManageDuplicate;
} OPERATIONS;


/*==============================================================================
 * Funzioni per la gestione della lista
 *============================================================================*/


/**
 * Inserisce un nodo all'interno della lista
 *
 * Questa funzione utilizza un approccio ricorsivo per inserire un nodo
 * con campo <Value> all'interno della lista <Current>.
 * 
 * NOTE Se un nodo con campo pari a <Value> è già esistente, la lista
 * non viene modificata
 * 
 * @param Value        Valore da inserire nel nodo.
 * @param Current      Testa della lista in cui inserire il nodo.
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *	                   - 0, in caso di inserimento corretto
 *                     - E_MALLOC, in caso di errore nella creazione del nodo
 *                     - W_DUPLICATE, in caso di valore già presente in lista
 * @param Op           Riferimento al record contenente le operazioni di manipolazione
 *                     dei nodi.
 *
 * @return Il puntatore alla testa della lista eventualmente modificato
 */ 
NODE *List_RecursiveOrderedInsert ( void *Value, NODE *Current, int *ReturnStatus, OPERATIONS *Op );

/**
 * Alloca un nuovo nodo, con relativo campo
 *
 * @param Value Valore da inserire nel nodo
 * @param Op    Riferimento al record contenente le operazioni di manipolazione
 *              dei nodi.
 *
 * @return Il riferimento al nuovo nodo creato.
 * */ 
NODE *ListCreateNewNode(void *Value, OPERATIONS *Op);


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
 * Stampa a video tutti i nodi della lista con testa Current
 * */
void List_RecursivePrint( NODE *Current, OPERATIONS *Op );

#endif /* _LISTA_H_ */
