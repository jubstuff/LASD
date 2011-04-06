/**
 * main.c
 * 
 * @author Giustino Borzacchiello - giustinob@gmail.com
 *
 * @date 06/04/11
 *
 * Prova per l'inserimento di puntatori a funzione all'interno di struct
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Funzione per il confronto di due interi.
 * NOTA La funzione si aspetta che i due parametri siano i valori e non gli indirizzi
 * Restituisce
 *   -1 se FirstArg < SecondArg
 *   0  se FirstArg == SecondArg
 *   1  se FirstArg > SecondArg
 **/
int NumCmp( void *FirstArg, void *SecondArg );

/**
 * Struct contenente le operazioni che si possono effettuare sui [futuri] nodi
 *
 * Operazioni consentite:
 *  * Compare => Permette di confrontare i campi chiave dei nodi
 *
 */
typedef struct operations_tag
{
	int (*Compare)(void *, void *);
} OPERATIONS; 

int main(void)
{
	//Definisco due struct: una contenente le operazioni per i numeri, l'altra quella per le stringhe
    OPERATIONS ListaNumeri;
	OPERATIONS ListaStringhe;
    //Inizializzo la struct per i numeri con la funzione di confronto tra interi
	ListaNumeri.Compare = NumCmp;
	//Inizializzo anche il campo Compare per le operazioni sulle stringhe alla funzione strcasecmp
	//Dato che quest'ultima ha una signature diversa da quella specificata nella struct, effettuo
	//un casting al tipo puntatore a funzione che restituisce int e ha due void* come parametri
	ListaStringhe.Compare = (int (*)(void *, void *))strcasecmp;

    printf("Programma di prova per puntatori a funzione memorizzati in una struct\n");
	printf("Verranno confrontati i numeri 3 e 4\n");
	printf("E poi le stringhe Abba e Babbo\n");
	printf("Entrambi i confronti dovrebbero restituire -1\n");
	int result = ListaNumeri.Compare( (void *)3, (void *)4);
	printf("3 e' effettivamente minore di 4: %d\n", result);
    
	result = ListaStringhe.Compare( (void *)("Abba"), (void *)("Babbo"));
	printf("E Abba viene prima di Babbo: %d\n", result); 
	return 0;
}

int NumCmp( void *FirstArg, void *SecondArg )
{
	int ReturnValue;
	int First = (int)FirstArg;
	int Second = (int)SecondArg;

	if ( First < Second )
	{
		ReturnValue = -1;
	}
	else if ( First == Second )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;
}
