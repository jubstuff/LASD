/**
 * operazioni_numeri.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 07/04/11
 * @package ListaGenerale
 *
 * Realizza alcune semplici funzioni per gestire una lista con nodi contenenti
 * un singolo campo di tipo int
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef _OPERAZIONI_NUMERI_H_ 
#define _OPERAZIONI_NUMERI_H_

void *InizializzaNodoInt( void *Value );
void StampaNodoInt( const void *Value );
void DeallocaInt( void *Value );
int NumCmp( const void *FirstArg, const void *SecondArg );
void Duplicato( void *Value );

#endif
