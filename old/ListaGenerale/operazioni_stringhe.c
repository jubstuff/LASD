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
#include "operazioni_stringhe.h"
/*==============================================================================
 * Definizione di funzioni per la lista di stringhe
 *============================================================================*/
char *InizializzaNodoStringa( char *Value )
{
	char *str= (char *) malloc( (strlen(Value) + 1) * sizeof(char) );
	strcpy(str, Value);
	return str;
}

void StampaNodoStringa(char *Value)
{
	printf("%s\n", Value);
}

void DeallocaStringa( char *Value )
{
	free(Value);
}
