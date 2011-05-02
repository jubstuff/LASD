/**
 * main.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/04/11
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
	int ReturnStatus;        /**< Stato delle funzioni che agiscono sulla lista */

	//inizializza la lista
	Head = NULL;
	
	Op.Compare = ConfrontaStringhe;
	Op.InitNode = InizializzaNodoStringa;
	Op.Print = StampaNodoStringa;
	Op.DeleteNode = DeallocaStringa;
	Op.ManageDuplicate = DuplicatoStringa; 
	do 
	{
		//Mostra il menu con le scelte possibili
		MenuChoice = Menu();
		
		switch( MenuChoice )
		{
			case '1': //Inserire un nodo nella lista
			    Head = GestisciInserimentoStringa( Head, &Op );
				break;
			case '2': //Eliminare un nodo dalla lista
				Head = GestisciCancellazioneNodo( Head, &Op );
				break;
			case '3': //Cancellare tutta la lista
				Head = GestisciDistruzioneLista( Head, &Op );
				break;
			case '4': //Salvare la lista su file
				//Modifico la funzione di stampa utilizzando quella per file
				Op.Print = ScriviSuFileDiTesto;
				//Azzero il contenuto del file, aprendolo in scrittura
				fopen( NOME_FILE, "w");

                //Stampo la lista su file
				List_RecursivePrint( Head, &Op );
				//Reimposto la funzione di stampa su stdout
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
							NOME_FILE);
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
				//dealloco la lista prima dell'uscita
				Head = List_RecursiveDestroy( Head, &Op );
				break;

			default: //Operazione scelta non valida
				printf("\n\nScelta non valida.\n\n");
				
				break;
		}
	} while( MenuChoice != '0' );
	
    return 0;
}
