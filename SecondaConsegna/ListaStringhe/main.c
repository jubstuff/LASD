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
#include "../lib/lista.h"
#include "operazioni_stringhe.h"

int main(void)
{
	NODE *Head;      /**< Testa della lista */
	OPERATIONS Op;   /**< Elenco delle operazioni che operano sui nodi */
	char MenuChoice; /**< Operazione scelta nel menu */

	//inizializza la lista
	Head = NULL;
	//inizializza la struct con le operazioni
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
			    Head = GestisciCaricamentoDaFile( Head, &Op );
				break;
			case '9': //Stampare la lista a video
				
				GestisciStampaStringhe( Head, &Op );
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

