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
 * La lista � di tipo a singola concatenazione.
 * 
 */

#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

#define LENMAX      100 //Lunghezza massima input
#define E_MALLOC    1   //Errore nella chiamata a malloc
#define W_DUPLICATE 2   //Warning nell'inserimento di un nodo duplicato
#define I_FOUND     3   //Info di nodo rimosso correttamente
#define E_FOPEN     4   //Errore nella chiamata a fopen
#define E_FCLOSE    5   //Errore nella chiamata a fclose


/*=============================================================================*
 * Definizioni strutture
 =============================================================================*/

typedef struct node {
	struct node *Next; /**< Puntatore al nodo successivo */
	void *Info;        /**< Campo del nodo */
} NODO;

typedef struct operations_tag
{
	int (*Compare)(void *, void *);
	void *(*Initialize)( void * );
	void (*Print)(void *);
	void (*Destroy)(void *);
} OPERATIONS;

typedef struct list_tag
{
	NODO *Head;
	int  NumElements;
	OPERATIONS *Op;
} LIST;


/*==============================================================================
 * Funzioni per la gestione della lista
 *============================================================================*/

int ListIsEmpty(LIST *);

/**
 * Alloca memoria per un nuovo nodo e lo inizializza con il valore passato
 * dall'utente
 */
NODO *ListCreateNewNode(void *Value, OPERATIONS *Op);

/**
 * Crea un nuovo nodo e lo inserisce dopo Current
 **/
NODO *ListInsertBefore( void *Value, NODO *Current, OPERATIONS *Op );
/**
 * Inserisce un nodo all'interno della lista
 *
 * Questa funzione utilizza un approccio ricorsivo per inserire un nodo
 * con campo <Value> all'interno della lista <Current>.
 * 
 * NOTE Se un nodo con campo pari a <Value> � gi� esistente, la lista
 * non viene modificata
 * 
 */ 
NODO *ListRecursiveOrderedInsert ( void *Value, NODO *Current, int *ReturnStatus, OPERATIONS *Op );

void ListOrderedInsert( void *Value, LIST *L, OPERATIONS *Op);

/**
 * Libera la memoria del nodo e del suo campo info
 **/
NODO *ListFreeNode( NODO *Current, OPERATIONS *Op );
/**
 * Rimuove un nodo dalla lista
 *
 * Questa funzione utilizza un approccio ricorsivo per rimuovere un nodo
 * con campo <Value> dalla lista <Current>.
 * 
 * NOTE Se un nodo con campo pari a <Value> non esiste, la lista
 * non viene modificata
 * 
 */
NODO *ListRemove(void *Value, NODO *Current, int *ReturnStatus, OPERATIONS *Op);

/**
 * Dealloca tutti i nodi della lista
 *
 */
NODO * ListDeallocate(NODO *, OPERATIONS *);

/**
 * Stampa i campi della lista, in ordine
 *
 */
void ListPrint( NODO *Current, OPERATIONS *Op );

/*==============================================================================
 * Funzioni di File I/O per la lista
 *============================================================================*/
 
/**
 * Scrive la lista di stringhe su file.
 *
 * Il file generato � in formato testuale per garantirne la portabilit� ed � 
 * formattato in questo modo:
 * 
 * StringaNodo1
 * StringaNodo2
 * StringaNodo3
 *
 */
void ScriviSuFileDiTesto( char *NomeFile, NODO *Head, int *ReturnStatus );

/**
 * Legge una serie di stringhe da un file, salvandole in una lista concatenata.
 * 
 * Legge un file nel formato:
 * 
 * Stringa1
 * Stringa2
 * Stringa3
 *
 * creando un nodo per ogni stringa, e restituendo la testa della lista creata.
 *
 */
NODO *CaricaListaDaFile( char *NomeFile, int LenMax, int *ReturnStatus );

/*==============================================================================
 * Funzioni di utilit�
 *============================================================================*/
 
/**
 * Legge una stringa da standard input, di lunghezza massima <LenMax>.
 * NOTE 
 *  - Tutti i caratteri di controllo e, in generale, non alfanumerici vengono 
 *    ignorati.
 *  - La stringa viene restituita senza '\n' finale.
 *
 */
void LeggiStringa( char *Buf, int LenMax, FILE *InputStream);

/**
 * Visualizza un menu per la scelta delle operazioni da effettuare
 *
 */
char Menu();

/**
 * Mette il programma in attesa di un singolo input utente
 *
 */
void Pause();

#endif
