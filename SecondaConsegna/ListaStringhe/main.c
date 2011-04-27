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
#include "../../List/src/lista.h"
#include "operazioni_stringhe.h"

int main(void)
{
	NODE *Head;              /**< Testa della lista */
	OPERATIONS Op;
	char MenuChoice;         /**< Operazione scelta nel menu */
    char TempBuffer[LENMAX]; /**< Buffer temporaneo per la lettura da stdin */
	int ReturnStatus;        /**< Stato delle funzioni che agiscono sulla lista */

	//inizializza la lista
	Head = NULL;
	
	Op.Compare = ConfrontaStringhe;
	Op.InitNode = InizializzaNodoStringa;
	Op.Print = StampaNodoStringa;
	Op.DeleteNode = DeallocaStringa;
//	Op.ManageDuplicate = ; //TODO inserire funzione duplicati
	do 
	{
		//Mostra il menu con le scelte possibili
		MenuChoice = Menu();
		
		switch( MenuChoice )
		{
			case '1': //Inserire un nodo nella lista
			
				printf("\nInserire la stringa [massimo %d caratteri]\n", LENMAX);
				printf("?>");
				LeggiStringa(TempBuffer, LENMAX);
				
				Head = List_RecursiveOrderedInsert(TempBuffer, Head, &ReturnStatus, &Op);
				
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
					
					LeggiStringa(TempBuffer, LENMAX);
					
					Head = List_RecursiveDelete(TempBuffer, Head, &ReturnStatus, &Op);
					
					//Trovato un nodo con il valore dato
					if ( ReturnStatus == I_REMOVED )
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
					Head = List_RecursiveDestroy( Head, &Op );
				}
				else
				{
					printf("\n\nLa lista e' gia' vuota.\n\n");
				}
				
				break;
			case '4': //Salvare la lista su file
				Op.Print = ScriviSuFileDiTesto;
				fopen( NOME_FILE, "w");
				List_RecursivePrint( Head, &Op );
				Op.Print = StampaNodoStringa;
				break;
			case '5': //Caricare la lista da file
			
				//visualizza un messaggio di avvertimento: cancellazione lista
				//attuale
				if ( Head != NULL )
				{
					printf("ATTENZIONE: La lista attuale verra' eliminata!\n");
				}
				//Elimina la lista attuale
				Head = List_RecursiveDestroy( Head, &Op );
				Head = CaricaListaDaFile( NOME_FILE, LENMAX, &ReturnStatus, &Op);

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
				break;
			case '9': //Stampare la lista a video
				
				//Se la lista è non vuota, stampa i suoi elementi
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
			case '0': //Uscita
				Head = List_RecursiveDestroy( Head, &Op );
				break;

			default: //Operazione scelta non valida
				printf("\n\nScelta non valida.\n\n");
				
				break;
		}
	} while( MenuChoice != '0' );
	
    return 0;
}
