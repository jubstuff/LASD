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
#include "../../List/src/lista.h"

#ifndef _OPERAZIONI_STRINGHE_H_
#define _OPERAZIONI_STRINGHE_H_

#define LENMAX      100 //Lunghezza massima input
#define E_FOPEN     2
#define E_FCLOSE    3
#define NOME_FILE   "lista_stringhe.txt"
 /*==============================================================================
 * Definizione di funzioni per la lista di stringhe
 *============================================================================*/
void *InizializzaNodoStringa( void *Value );
void StampaNodoStringa(const void *Value);
void DeallocaStringa( void *Value );
int ConfrontaStringhe( const void *Str1, const void *Str2 );
void LeggiStringa( char *Buf, int LenMax);
char Menu();
void Pause();
void ScriviSuFileDiTesto( const void *Value );
NODE *CaricaListaDaFile ( char *NomeFile, int LenMax, int *ReturnStatus, OPERATIONS *Op );
#endif
