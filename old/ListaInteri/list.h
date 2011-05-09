/**
 * list.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 04/02/11
 * @package ListaInteri
 *
 * Realizza alcune semplici funzioni per una lista, quali:
 *  - inserimento di un nodo
 *  - cancellazione di un nodo
 *  - stampa della lista
 *  - cancellazione di tutti i nodi della lista
 * 
 * La lista è di tipo a singola concatenazione.
 * Il nodo è composto da un singolo campo intero. 
 */

#ifndef _LISTA_H_
#define _LISTA_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <errno.h>      //ERANGE

#define LENMAX      100 //Lunghezza massima input
#define E_MALLOC    1   //Errore nella chiamata a malloc
#define W_DUPLICATE 2   //Warning nell'inserimento di un nodo duplicato
#define I_FOUND     3   //Info di nodo rimosso correttamente

/*=============================================================================*
 * Definizioni strutture
 =============================================================================*/

typedef struct node {
	struct node *Next; /**< puntatore al nodo successivo */
	int Info;          /**< campo intero del nodo */
} NODO;

/*=============================================================================*
 * Funzioni per la gestione della lista
 *============================================================================*/

/**
 * Inserisce un nodo all'interno della lista
 *
 * Questa funzione utilizza un approccio ricorsivo per inserire un nodo
 * con campo <Value> all'interno della lista con testa <Current>.
 * 
 * NOTA Se un nodo con campo pari a <Value> è già esistente, la lista
 * non viene modificata
 * 
 */ 
NODO *ListInsert(int Value, NODO *Current, int *ReturnStatus);

/**
 * Rimuove un nodo dalla lista
 *
 * Questa funzione utilizza un approccio ricorsivo per rimuovere un nodo
 * con campo <Value> dalla lista con testa <Current>.
 * 
 * NOTA Se un nodo con campo pari a <Value> non esiste, la lista
 * non viene modificata
 * 
 */
NODO *ListRemove(int Value, NODO *Current, int *ReturnStatus);

/**
 * Stampa i campi della lista, in ordine
 *
 */
void ListPrint(NODO *Current);

/**
 * Dealloca tutti i nodi della lista
 *
 */
NODO *ListDeallocate(NODO *Current);

/*==============================================================================
 * Funzioni di utilità
 *============================================================================*/

/**
 * Legge un intero da standard input, salvandolo nel parametro <Value>.
 * Il formato riconosciuto dalla stringa in ingresso è il seguente:
 * [spazi] [{+ | –}] [0 [{ x | X }]] [numeri]
 *
 * In caso di input non conforme al modello, verrà tentato un parsing fino al 
 * primo carattere non numerico, ovvero:
 *  123abc => 123
 *
 */
int LeggiIntero(int *Value);

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
