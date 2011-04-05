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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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
	char *Stringa;     /**< Campo stringa del nodo */
} NODO;

/*==============================================================================
 * Definizione di puntatori a funzioni
 *============================================================================*/
int compare(void *PrimoElemento, void *SecondoElemento);
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
 */ 
NODO *ListInsert(char *Value, NODO *Current, int *ReturnStatus);

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
NODO *ListRemove(char *Value, NODO *Current, int *ReturnStatus);

/**
 * Dealloca tutti i nodi della lista
 *
 */
NODO * ListDeallocate(NODO *Current);

/**
 * Stampa i campi della lista, in ordine
 *
 */
void ListPrint(NODO *Current);

/*==============================================================================
 * Funzioni di File I/O per la lista
 *============================================================================*/
 
/**
 * Scrive la lista di stringhe su file.
 *
 * Il file generato è in formato testuale per garantirne la portabilità ed è 
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
 * Funzioni di utilità
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
