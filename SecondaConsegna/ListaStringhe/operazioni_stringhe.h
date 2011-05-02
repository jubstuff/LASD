/**
 * operazioni_stringhe.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/04/11
 * @package ListaStringhe
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
#define NOME_FILE   "lista_stringhe.txt" /**< Nome del file in cui memorizzare/leggere */
 /*==============================================================================
 * Definizione di funzioni per la lista di stringhe
 *============================================================================*/
void *InizializzaNodoStringa( void *Value );

void StampaNodoStringa(const void *Value);

void ScriviSuFileDiTesto( const void *Value );

void DeallocaStringa( void *InputValue, void *NodeInfo );

int ConfrontaStringhe( const void *Str1, const void *Str2 );

void LeggiStringa( char *Buf, int LenMax);

void DuplicatoStringa( void *Value, NODE *CurrentNode );


/*==============================================================================
 * Funzioni relative alle voci del menu
 *============================================================================*/
NODE *GestisciInserimentoStringa( NODE *Head, OPERATIONS *Op );

NODE *GestisciCancellazioneNodo( NODE *Head, OPERATIONS *Op );
NODE *GestisciDistruzioneLista( NODE *Head, OPERATIONS *Op );
char Menu();

void Pause();

NODE *CaricaListaDaFile ( char *NomeFile, int LenMax, int *ReturnStatus, OPERATIONS *Op );

#endif //_OPERAZIONI_STRINGHE_H_

