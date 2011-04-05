/**
 * main.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 04/02/11
 * @package ListaStringhe
 *
 * Main File per la gestione di una lista di stringhe.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "listaChar.h"

int main(void)
{
	NODO *Head;              /**< Testa della lista */
	char MenuChoice;         /**< Operazione scelta nel menu */
    char TempBuffer[LENMAX]; /**< Buffer temporaneo per la lettura da stdin */
	int ReturnStatus;        /**< Stato delle funzioni che agiscono sulla lista */

	//inizializza la lista
	Head = NULL;
	
	do 
	{
		//Mostra il menu con le scelte possibili
		MenuChoice = Menu();
		
		switch( MenuChoice )
		{
			case '1': //Inserire un nodo nella lista
			
				printf("\nInserire la stringa [massimo %d caratteri]\n", LENMAX);
				printf("?>");
				LeggiStringa(TempBuffer, LENMAX, stdin);
				
				Head = ListInsert(TempBuffer, Head, &ReturnStatus);
				
				//Se il nodo è già presente nella lista, notifica
				if( ReturnStatus == W_DUPLICATE )
				{
					printf("\nValore gia' presente\n");
				}
				//Verifica se c'è stato un altro tipo di errore 
				else if( ReturnStatus > 0 )
				{
					perror("C'e' stato un errore nell'inserimento");
				}
				//Ok, valore inserito
				else
				{
					printf("\nValore inserito\n\n");
				}
				
				break;
			case '2': //Eliminare un nodo dalla lista
			
				//Se la lista non è vuota, cerca il nodo indicato
				if ( Head != NULL )
				{
					printf("\nInserire la stringa da eliminare [massimo %d caratteri]\n", 
						LENMAX);
					
					LeggiStringa(TempBuffer, LENMAX, stdin);
					
					Head = ListRemove(TempBuffer, Head, &ReturnStatus);
					
					//Trovato un nodo con il valore dato
					if ( ReturnStatus == I_FOUND )
					{
						printf("\nStringa eliminata\n\n");
					}
					//Nodo con valore dato non trovato
					else
					{
						printf("\nStringa non trovata\n\n");
					}
				}
				//lista vuota
				else
				{
					printf("\n\nLa lista e' gia' vuota.\n\n");
				}
				
				
				break;
			case '3': //Cancellare tutta la lista
				
				// Se la lista è non vuota, cancella tutti i nodi
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
			case '4': //Salvare la lista su file
			
				printf("\nInserire il nome del file [massimo %d caratteri]\n", 
					LENMAX);
				
				LeggiStringa(TempBuffer, LENMAX, stdin);
				ScriviSuFileDiTesto(TempBuffer, Head, &ReturnStatus);
				
				//Se ci sono stati errori nel salvataggio
				if( ReturnStatus > 0 )
				{
					printf("\n");
					// visualizza un messaggio dipendente da errno
					perror("Errore nel salvataggio del file");
					printf("\n");
				}
				//OK, lista salvata
				else
				{
					printf("\nLista salvata correttamente nel file %s\n\n",
						TempBuffer);
				}
				
				
				
				
				break;
			case '5': //Caricare la lista da file
			
				printf("\nInserire il nome del file da cui caricare la lista [massimo %d caratteri]\n", 
					LENMAX);
				
				//visualizza un messaggio di avvertimento: cancellazione lista
				//attuale
				if ( Head != NULL )
				{
					printf("ATTENZIONE: La lista attuale verra' eliminata!\n");
				}
				printf("[Stringa vuota per annullare]\n");
				
				LeggiStringa(TempBuffer, LENMAX, stdin);
				
				/* Se è stato inserito il nome del file, cancella la lista
				 * attuale e carica quella nel file */
				if( strlen(TempBuffer) )
				{
					//Elimina la lista attuale
					Head = ListDeallocate(Head);
					Head = CaricaListaDaFile(TempBuffer, LENMAX, &ReturnStatus);
					
					//Se ci sono stati errori al caricamento
					if( ReturnStatus > 0 )
					{
						printf("\n");
						// visualizza un messaggio dipendente da errno
						perror("Errore nel caricamento del file");
						printf("\n");
					}
					//OK, lista caricata dal file
					else
					{
						printf("\nLista caricata correttamente dal file %s\n\n",
							TempBuffer);
					}
				}
				break;
			case '9': //Stampare la lista a video
				
				//Se la lista è non vuota, stampa i suoi elementi
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
			case '0': //Uscita
				break;

			default: //Operazione scelta non valida
				printf("\n\nScelta non valida.\n\n");
				
				break;
		}
	} while( MenuChoice != '0' );
	
	Pause();
    return 0;
}
