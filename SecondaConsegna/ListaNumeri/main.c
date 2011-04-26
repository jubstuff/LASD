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
#include "../../List/src/lista.h"
#include "operazioni_numeri.h"
#include <string.h>
#include <time.h>


int main(void) {
	NODE *Head;        /**< Testa della lista */
	OPERATIONS Op;      /**< Elenco delle operazioni che operano sui nodi */
	int  MenuChoice;   /**< Operazione scelta nel menu */
	int  Value;        /**< Variabile temporanea per la lettura da stdin */
	int  Success;      /**< Flag per valori di ritorno delle funzioni */
	int  i;            /**< Indice per cicli */
	int  ReturnStatus; /**< Stato delle funzioni che agiscono sulla lista */
	int  RandomNum;    /**< Numero casuale temporaneo */
	
	Success = 0;
	//inizializza la lista
	Head = NULL;
	//Inizializzo la struct con le operazioni
   	Op.Compare = NumCmp;
   	Op.InitNode = InizializzaNodoInt;
	Op.DeleteNode = DeallocaInt;
   	Op.Print = StampaNodoInt;
    Op.ManageDuplicate = DuplicatoInt; 
	//Inizializza il seme per la generazione di numeri casuali
	srand( time(NULL) );
	
	do 
	{
		//Mostra il menu con le scelte possibili
		MenuChoice = Menu();
		switch(MenuChoice)
		{
			case '1': //inserimento di un nodo
			    Head = GestisciInserimentoNumero( Head, &Op );
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
						Head = List_RecursiveDelete(&Value, Head, &ReturnStatus, &Op);
						//Trovato un nodo con il valore dato
						if ( ReturnStatus == I_REMOVED)
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
					Head = List_RecursiveDestroy( Head, &Op );
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
						RandomNum = rand() % 101;
						Head = List_RecursiveOrderedInsert( &RandomNum, Head, &ReturnStatus, &Op);
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
					List_RecursivePrint( Head, &Op );
					printf("\n\n=================================================\n\n");
				}
				else
				{
					printf("\n\nLa lista e' vuota.\n\n");
				}
				
				break;
			case '0': //uscita
				//Elimino la lista all'uscita
				Head = List_RecursiveDestroy( Head, &Op );
				break;

			default: //scelta non valida
				printf("\n\nScelta non valida.\n\n");
				
				break;
		}
	} while( MenuChoice != '0' );
	
	return 0;
}


