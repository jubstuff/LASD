/**
 * main.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/04/11
 * @package ListaNumeri
 *
 * Main File per la gestione di una lista di interi.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "../../../lib/lista.h"
#include "operazioni_numeri.h"
#include <string.h>
#include <time.h>


int main(void) {
	NODE *Head;      /**< Testa della lista */
	OPERATIONS Op;   /**< Elenco delle operazioni che operano sui nodi */
	int  MenuChoice; /**< Operazione scelta nel menu */
	
	//inizializza la lista
	Head = NULL;
	//Inizializza la struct con le operazioni
   	Op.Compare = NumCmp;
   	Op.InitNode = InizializzaNodoInt;
	Op.Delete = DeallocaInt;
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
				Head = GestisciCancellazioneNodo( Head, &Op );
				break;
			case '3': //eliminazione lista
				Head = GestisciDistruzioneLista( Head, &Op );
				break;
			case '4': //inserimento numeri casuali
			    Head = GestisciInserimentoNumeriCasuali( Head, &Op );
				break;
			case '5': //eliminazione intervallo
				Head = GestisciCancellazioneIntervallo( Head, &Op );
				break;
			case '9': //stampare la lista a video
			    GestisciStampaNumeri( Head, &Op );
				break;
			case '0': //uscita
				//Assicura la lista sia deallocata prima di uscire
				Head = List_RecursiveDestroy( Head, &Op );
				break;

			default: //scelta non valida
				printf("\n\nScelta non valida.\n\n");
				
				break;
		}
	} while( MenuChoice != '0' );
	
	return 0;
}


