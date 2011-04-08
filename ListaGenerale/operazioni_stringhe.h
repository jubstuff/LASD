/**
 * operazioni_stringhe.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 07/04/11
 * @package ListaGenerale
 *
 * Realizza alcune semplici funzioni per gestire una lista con nodi contenenti
 * un singolo campo di tipo char*
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _OPERAZIONI_STRINGHE_H_
#define _OPERAZIONI_STRINGHE_H_
 /*==============================================================================
 * Definizione di funzioni per la lista di stringhe
 *============================================================================*/
char *InizializzaNodoStringa( char * );
void StampaNodoStringa( char * );
void DeallocaStringa( char * );
#endif
