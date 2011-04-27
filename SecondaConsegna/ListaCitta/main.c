#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../List/src/lista.h"
#include "gestione_citta.h"

int main(void)
{
	NODE *Head;              /**< Testa della lista */
	OPERATIONS Op;
	char MenuChoice;         /**< Operazione scelta nel menu */
	char NomeTemp[LENMAX]; /**< Buffer temporaneo per la lettura da stdin */
	char CognomeTemp[LENMAX]; /**< Buffer temporaneo per la lettura da stdin */
	char CittaTemp[LENMAX]; /**< Buffer temporaneo per la lettura da stdin */
	int ReturnStatus;        /**< Stato delle funzioni che agiscono sulla lista */
	PERSONA PersTemp;

	//inizializza la lista
	Head = NULL;

	Op.Compare = ConfrontaNodoCitta;
	Op.InitNode = InizializzaNodoCitta;
	//Op.DeleteNode = EliminaNodoCitta;
	Op.Print = StampaListaCitta;
	Op.ManageDuplicate = DuplicatoCitta; 
	do 
	{
		//Mostra il menu con le scelte possibili
		MenuChoice = Menu();

		switch( MenuChoice )
		{
			case '1': //Inserire un nodo nella lista

				printf("\nInserire il nome [massimo %d caratteri]\n", LENMAX);
				printf("?>");
				LeggiStringa(NomeTemp, LENMAX);

				printf("\nInserire il cognome [massimo %d caratteri]\n", LENMAX);
				printf("?>");
				LeggiStringa(CognomeTemp, LENMAX);

				printf("\nInserire la citta' [massimo %d caratteri]\n", LENMAX);
				printf("?>");
				LeggiStringa(CittaTemp, LENMAX);

				PersTemp.Nome = NomeTemp;
				PersTemp.Cognome = CognomeTemp;
				PersTemp.Citta = CittaTemp;
				Head = List_RecursiveOrderedInsert( (void *)&PersTemp, Head, &ReturnStatus, &Op);

				//Verifica se c'è stato un errore
				if( ReturnStatus > 0 )
				{
					perror("C'e' stato un errore nell'inserimento");
				}
				//Ok, valore inserito
				else
				{
					printf("\nValore inserito\n\n");
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
				//Head = List_RecursiveDestroy( Head, &Op ); //TODO rimuovere commento dopo aver implementato cancellazione
				break;

			default: //Operazione scelta non valida
				printf("\n\nScelta non valida.\n\n");

				break;
		}
	} while( MenuChoice != '0' );

	return 0;
}
