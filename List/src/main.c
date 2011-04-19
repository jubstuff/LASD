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
    char nome1[] = "Giustino";
	char cognome1[] = "Borzacchiello";
	char citta1[] = "Amalfi";

	char nome2[] = "Valeria";
	char cognome2[] = "Marolda";
	char citta2[] = "Amalfi";

	Head = NULL;
	ReturnStatus = 0;

	P1.Nome = nome1;
	P1.Cognome = cognome1;
	P1.Citta = citta1;

	P2.Nome = nome2;
	P2.Cognome = cognome2;
	P2.Citta = citta2;

   	Op.Compare = ConfrontaNodoCitta;
   	Op.InitNode = InizializzaNodoCitta;
	Op.DeleteNode = NULL;
   	Op.Print = NULL;
    Op.ManageDuplicate = DuplicatoCitta; 

	Head = List_RecursiveOrderedInsert( &P1, Head, &ReturnStatus, &Op );
	Head = List_RecursiveOrderedInsert( &P2, Head, &ReturnStatus, &Op );
    printf("%s", (char *)( ((PERSONA *) ((NODE *)(Head->Info))->Info)->Nome ) );                                    
    printf("%s", (char *)( ((PERSONA *) ((NODE *)(Head->Info))->Next->Info)->Nome ) );                                    
    //printf("%s", (char *)( ((PERSONA *) ((NODE *)(Head->Next->Info))->Info)->Nome ) ); // Caso inserimento senza duplicato                                   
	return 0;
}
