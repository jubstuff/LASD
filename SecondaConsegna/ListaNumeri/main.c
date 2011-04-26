/**
 * main.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 04/02/11
 * @package ListaInteri
 *
 * Main File per la gestione di una lista di interi.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <time.h>


int main(void) {
	NODE *Head;        /**< Testa della lista */
	int  MenuChoice;   /**< Operazione scelta nel menu */
	int  Value;        /**< Variabile temporanea per la lettura da stdin */
	int  Success;      /**< Flag per valori di ritorno delle funzioni */
	int  i;            /**< Indice per cicli */
	int  ReturnStatus; /**< Stato delle funzioni che agiscono sulla lista */
	
	Success = 0;
	//inizializza la lista
	Head = NULL;
	//Inizializza il seme per la generazione di numeri casuali
	srand( time(NULL) );
	
	do 
	{
		//Mostra il menu con le scelte possibili
		MenuChoice = Menu();
		switch(MenuChoice)
		{
			case '1': //inserimento di un nodo
			
				printf("\nInserire il numero intero.\n");
				printf("?>");
				
				Success = LeggiIntero(&Value);
				if( Success )
				{
					Head = ListInsert(Value, Head, &ReturnStatus);
					//Se il nodo è già presente nella lista, notifica
					if( ReturnStatus == W_DUPLICATE )
					{
						printf("\nValore gia' presente\n");
					}
					//Verifica se c'è stato un altro tipo di errore 
					else if( ReturnStatus > 0 )
					{
						printf("\nC'e' stato un errore nell'inserimento\n\n");
					}
					//Ok, valore inserito
					else
					{
						printf("\nValore inserito\n\n");
					}
				}
				//valore immesso dall'utente non valido
				else 
				{
					printf("\n\nValore non valido\n\n");
				}
				break;
			case '2': //eliminazione di un nodo
				
				//effettua l'eliminazione solo se la lista è non vuota
				if ( Head != NULL )
				{
					printf("\nInserire il numero\n");
					printf("?>");
					
					Success = LeggiIntero(&Value);
					
					if( Success )
					{
						Head = ListRemove(Value, Head, &ReturnStatus);
						//Trovato un nodo con il valore dato
						if ( ReturnStatus == I_FOUND )
						{
							printf("\nNumero Eliminato\n\n");
						}
						//Nodo con valore dato non trovato
						else
						{
							printf("\nNumero non trovato\n\n");
						}
					}
					//Il valore immesso dall'utente non è valido
					else 
					{
						printf("\n\nValore non valido\n\n");
					}
				}
				//lista vuota
				else
				{
					printf("\n\nLa lista e' gia' vuota.\n\n");
				}
				break;
			case '3': //eliminazione lista
				
				//dealloca la lista solo se non vuota
				if( Head != NULL )
				{
					printf("\n\nCancellazione Lista...\n\n");
					Head = ListDeallocate(Head);
				}
				else
				{
					printf("\n\nLa lista e' gia' vuota.\n\n");
				}
				
				break;
			case '4': //inserimento numeri casuali
			
				printf("\nQuanti numeri casuali inserire?\n");
				printf("?>");
				
				Success = LeggiIntero(&Value);
				if( Success )
				{	
					for( i=0; i < Value; i++)
					{
						Head = ListInsert( rand(), Head, &ReturnStatus);
					}
					printf("\n\nNumeri inseriti correttamente.\n\n");
				}
				else 
				{
					printf("\n\nValore non valido\n\n");
				}
				break;
			case '9': //stampare la lista a video
			
				if( Head != NULL )
				{
					printf("\n\n=================================================\n\n");
					ListPrint(Head);
					printf("\n\n=================================================\n\n");
				}
				else
				{
					printf("\n\nLa lista e' vuota.\n\n");
				}
				
				break;
			case '0': //uscita
				break;

			default: //scelta non valida
				printf("\n\nScelta non valida.\n\n");
				
				break;
		}
	} while( MenuChoice != '0' );
	
	Pause();
	return 0;
}


