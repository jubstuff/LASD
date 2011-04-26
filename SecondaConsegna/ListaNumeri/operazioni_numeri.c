#include "operazioni_numeri.h"
#include <stdlib.h>
#include <errno.h>


void *InizializzaNodoInt( void *Value )
{
	int *Num = (int *) malloc( sizeof(int) );
	printf("Inizializzo il numero....\n");
	*Num = *( (int *)Value );
	return (void *)Num;
}

void StampaNodoInt( const void *Value )
{
	printf("%d\n", *( (int *)Value) );
}

void DeallocaInt( void *Value )
{
	free(Value);
}


int NumCmp( const void *FirstArg, const void *SecondArg )
{
	int ReturnValue;
	int First = *( (int *)FirstArg );
	int Second = *( (int *)SecondArg );

	if ( First < Second )
	{
		ReturnValue = -1;
	}
	else if ( First == Second )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;

}

void DuplicatoInt( void *Value, NODE *Nodo )
{
	int Num = *( (int *)Value );
	printf("Stai cercando di inserire un nodo duplicato\n");
	printf("Il valore che stavi cercando di inserire è %d\n", Num);
}

/*==============================================================================
 * Funzioni di utilità
 *============================================================================*/

/**
 * Legge un intero da standard input, salvandolo nel parametro <Value>.
 * Il formato riconosciuto dalla stringa in ingresso è il seguente:
 * [spazi] [{+ | }] [0 [{ x | X }]] [numeri]
 *
 * In caso di input non conforme al modello, verrà tentato un parsing fino al 
 * primo carattere non numerico, ovvero:
 *  123abc => 123
 *
 * @param Value [out] Numero digitato dall'utente.
 *
 * @return L'esito della lettura da standard input. Può assumere valore: 
 *		   - 1 se l'operazione ha avuto successo, 
 *		   - 0 se l'operazione non ha avuto successo.
 *
 */
int LeggiIntero(int *Value)
{
	char TempBuffer[13]; /**< 32 bit con segno, più '\n' e '\0' */
	char *EndPtr;		 /**< Buffer per caratteri non consentiti */
	int  Success;		 /**< Flag con valore 0 in caso di errore, 1 altrimenti*/
	
	Success = 1;
	errno = 0;
	fgets(TempBuffer, sizeof(TempBuffer), stdin);
	
	/* strtol expects nptr to point to a string of the following form:
	 * [whitespace] [{+ | }] [0 [{ x | X }]] [digits]
	 * http://msdn.microsoft.com/en-us/library/w4z2wdyc%28v=vs.71%29.aspx 
	 */
	*Value = strtol(TempBuffer, &EndPtr, 10);
	
	//Valore non valido: troppo grande, troppo piccolo oppure stringa
	if( (EndPtr == TempBuffer) || (errno == ERANGE) )
	{
		Success = 0;
	}
	return Success;
}

/**
 * Visualizza un menu per la scelta delle operazioni da effettuare
 *
 * @return L'identificativo dell'operazione da effettuare
 *
 */
char Menu()
{
    char TempBuffer[10];

	printf("=================================================\n");
	puts("Lista di interi - Menu");
	printf("=================================================\n");
	puts("1 - Inserire un numero nella lista.");
	puts("2 - Eliminare un numero dalla lista.");
	puts("3 - Eliminare tutti i numeri dalla lista.");
	puts("4 - Inserire dei numeri casuali.");
	puts("9 - Stampa la lista a video.");
	puts("0 - Esci");
	puts("Operazione da effettuare? ");
	printf("?>");

	fgets(TempBuffer, sizeof(TempBuffer), stdin);
	
	return TempBuffer[0];
}

/**
 * Mette il programma in attesa di un singolo input utente
 *
 */
void Pause()
{
	puts("\n\nPremere un tasto per continuare...");
	fgetc(stdin);
}


