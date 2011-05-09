/**
 * gestione_citta.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/04/11
 * @package ListaCitta
 *
 * Definizioni costanti e intestazioni delle funzioni per la gestione di una
 * lista di persone, ordinate per città
 * 
 */
#include "../lib/lista.h"

#ifndef _GESTIONE_CITTA_H_
#define _GESTIONE_CITTA_H_

#define LENMAX 100
/**
 *
 * gestione_citta.c
 *
 * Definizioni dei tipi di dato per la gestione di un elenco di persone,
 * con le relative città.
 * 
 * */

/**
 * Struct che contiene nome e cognome di una persona, e la città di residenza
 *
 * */
typedef struct persona_t 
{
	char *Nome;
	char *Cognome;
	char *Citta;
} PERSONA; 

/*============================================================================*
 * OPERAZIONI LISTA ESTERNA - ORDINATA PER CITTA'
 *===========================================================================*/
int ConfrontaNodoCitta( const void *Nodo1, const void *Persona );

void *InizializzaNodoCitta( void *Value );

void DuplicatoCitta( void *Persona, NODE *HeadContainer );

void StampaListaCitta( const void *Head );

void EliminaNodoCitta(void *Persona, void *NodeInfo);

void EliminaListaCitta(void *Persona, void *NodeInfo);

/*============================================================================*
 * OPERAZIONI LISTA INTERNA - ORDINATA PER PERSONA
 *===========================================================================*/
OPERATIONS *InizializzaOperazioniListaPersone( void );

int ConfrontaPersona( const void *Pers1, const void *Pers2 );

void *InizializzaPersona( void *InputPers );

void CancellaPersona( void *Value, void *NodeInfo );

void StampaPersona( const void *Value );

void DuplicatoPersona( void *Value, NODE *CurrentNode );

/*==============================================================================
 * Funzioni di utilità
 *============================================================================*/
void LeggiStringa( char *Buf, int LenMax);
char Menu();
#endif /* _GESTIONE_CITTA_H_ */
