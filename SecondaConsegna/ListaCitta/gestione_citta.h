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

typedef struct persona_t 
{
	char *Nome;
	char *Cognome;
	char *Citta;
} PERSONA; 

/**
 * Confronta la citta di residenza di due persone,
 * confrontandole in ordine lessicografico
 *
 * @return -1, 0, 1 se Pers1->Citta [>,==,<] Pers2->Citta rispettivamente
 * */
int ConfrontaNodoCitta( const void *Nodo1, const void *Persona );

int ConfrontaPersona( const void *Pers1, const void *Pers2 );

void *InizializzaNodoCitta( void *Value );

void DuplicatoCitta( void *Persona, NODE *HeadContainer );

void StampaListaCitta( const void *Head );

void EliminaNodoCitta(void *Persona, void *NodeInfo);

OPERATIONS *InizializzaOperazioniListaPersone( void );

void *InizializzaPersona( void *InputPers );

void CancellaPersona( void *Value, void *NodeInfo );

void StampaPersona( const void *Value );

void DuplicatoPersona( void *Value, NODE *CurrentNode );

void LeggiStringa( char *Buf, int LenMax);
char Menu();
#endif /* _GESTIONE_CITTA_H_ */
