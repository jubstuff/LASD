#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "../helpers/gestione_citta.h"

int main(void)
{
	NODE *Head;
   	OPERATIONS Op;
	int ReturnStatus;
    PERSONA P1;
	PERSONA P2;
	PERSONA P3;
    char nome1[] = "Giustino";
	char cognome1[] = "Borzacchiello";
	char citta1[] = "Amalfi";

	char nome2[] = "Valeria";
	char cognome2[] = "Marolda";
	char citta2[] = "Pozzuoli";

	char nome3[] = "Viviana";
	char cognome3[] = "Marolda";
	char citta3[] = "Pozzuoli";

	Head = NULL;
	ReturnStatus = 0;

	P1.Nome = nome1;
	P1.Cognome = cognome1;
	P1.Citta = citta1;

	P2.Nome = nome2;
	P2.Cognome = cognome2;
	P2.Citta = citta2;

	P3.Nome = nome3;
	P3.Cognome = cognome3;
	P3.Citta = citta3;

   	Op.Compare = ConfrontaNodoCitta;
   	Op.InitNode = InizializzaNodoCitta;
	Op.DeleteNode = EliminaNodoCitta;
   	Op.Print = StampaListaCitta;
    Op.ManageDuplicate = DuplicatoCitta; 

   	Head = List_RecursiveOrderedInsert( &P1, Head, &ReturnStatus, &Op );
	Head = List_RecursiveOrderedInsert( &P2, Head, &ReturnStatus, &Op );
	Head = List_RecursiveOrderedInsert( &P3, Head, &ReturnStatus, &Op );
	List_RecursivePrint( Head, &Op );
	return 0;
}
