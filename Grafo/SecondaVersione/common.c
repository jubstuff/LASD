/*=============================================================================
 *
 * Nome File: common.c
 *
 * Scopo: 
 *
 * Data Creazione: 14-05-2011
 *
 * Ultima Modifica: sab 14 mag 2011 10:49:14 CEST
 *
 * Autore: 
 *
 *
 =============================================================================*/
#include "common.h"
#include <stdio.h>
/**
 * Legge una stringa da standard input, di lunghezza massima <LenMax>.
 * NOTE 
 *  - Tutti i caratteri di controllo e, in generale, non alfanumerici vengono 
 *    ignorati.
 *  - La stringa viene restituita senza '\n' finale.
 *
 * @param Buf    Stringa digitata dall'utente.
 * @param LenMax Lunghezza massima consentita alla stringa in input.
 */
void LeggiStringa( char *Buf, int LenMax)
{
	fgets(Buf, LenMax, stdin);

	while ( *Buf < 0 || *Buf > 31) //ignora tutti i caratteri non alfanumerici
	{
		Buf++;
	}
	*Buf = '\0';
}
