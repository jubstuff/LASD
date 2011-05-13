/**
 * operazioni_numeri.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/04/11
 * @package ListaNumeri
 *
 * Definizioni costanti e intestazioni delle funzioni per la gestione di una
 * lista di interi
 * 
 */
#include "../../../lib/lista.h"

#ifndef _OPERAZIONI_NUMERI_H_ 
#define _OPERAZIONI_NUMERI_H_

#define E_RANGE        1
#define MAX_RAND_NUM 101

void *InizializzaNodoInt( void *Value );

void StampaNodoInt( const void *Value );

void DeallocaInt( void *InputValue, void *NodeInfo );

int NumCmp( const void *Num1, const void *Num2 );

void DuplicatoInt ( void *Value, NODE *Nodo );

int LeggiIntero(int *Value);

char Menu();

void Pause();

NODE *GestisciInserimentoNumero( NODE *Head, OPERATIONS *Op);

NODE *GestisciCancellazioneNodo( NODE *Head, OPERATIONS *Op );

NODE *GestisciDistruzioneLista( NODE *Head, OPERATIONS *Op );

NODE *GestisciInserimentoNumeriCasuali( NODE *Head, OPERATIONS *Op );

void GestisciStampaNumeri( NODE *Head, OPERATIONS *Op );

NODE *GestisciCancellazioneIntervallo( NODE *Head, OPERATIONS *Op );

#endif
