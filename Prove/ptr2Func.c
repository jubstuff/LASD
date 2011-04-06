/*
 * ptr2Fun.c
 *
 * File per testare e provare i puntatori a funzione
 *
 * Autore: Giustino Borzacchiello - giustinob@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Una funzione che restituisce un intero e prende un intero */
int MyFunc( int a );

int main(void)
{
	/* Una variabile, puntatore a funzione che prende un int e 
	 * restituisce un int */
	int (*PtrUno)(int);

	/* idem come sopra */
	int (*PtrDue)(int);


	/* Assegno al primo puntatore l'indirizzo della funzione */
	PtrUno = &MyFunc;                                          
	/* Assegno il valore del primo puntatore al secondo */
	PtrDue = PtrUno;
	/* Richiamo la funzione utilizzando il secondo puntatore */
	printf("%d\n", (*PtrDue)(3));
	return 0;
}

int MyFunc( int a )
{
	return a;
}
