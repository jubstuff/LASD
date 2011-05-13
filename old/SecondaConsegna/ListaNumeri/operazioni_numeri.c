/**
 * operazioni_numeri.c
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 27/04/11
 * @package ListaNumeri
 *
 * Implementazioni delle funzioni per la gestione di una lista di interi
 * 
 */
#include "operazioni_numeri.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/**
 * Alloca un nuovo intero e lo inizializza
 *
 * @param Value Riferimento al valore con cui inizializzare il numero
 *
 * @return Riferimento all'intero allocato
 *
 * */
void *InizializzaNodoInt( void *Value )
{
	int *Num = (int *) malloc( sizeof(int) );
	printf("Inizializzo il numero....\n");
	*Num = *( (int *)Value );
	return (void *)Num;
}
/**
 * Stampa a video un intero
 * 
 * @param Value Riferimento al numero da visualizzare
 *
 * */
void StampaNodoInt( const void *Value )
{
	printf("%d\n", *( (int *)Value) );
}
/**
 * Dealloca un intero
 *
 * @param InputValue Valore da eliminare passato in ingresso
 * @param NodeInfo   Riferimento al valore da deallocare
 *
 * */
void DeallocaInt( void *InputValue, void *NodeInfo )
{
	free( NodeInfo );
}
/**
 * Confronta due interi
 *
 * @param Num1 Riferimento al primo numero da confrontare
 * @param Num2 Riferimento al secondo numero da confrontare
 *
 * @return -1, 0, 1 se Num1 [>,==,<] Num2 rispettivamente
 * */
int NumCmp( const void *Num1, const void *Num2 )
{
	int ReturnValue;
	int First = *( (int *)Num1 );
	int Second = *( (int *)Num2 );

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
/**
 * Informa l'utente che ha cercato di inserire un numero già presente
 * 
 * @param Value Riferimento al valore passato in ingresso
 * @param Nodo  Riferimento al nodo in cui è presente il duplicato
 * */
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
 * [spazi] [{+ | -}] [0 [{ x | X }]] [numeri]
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
	 * [whitespace] [{+ | -}] [0 [{ x | X }]] [digits]
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
	puts("5 - Cancellare i numeri in un intervallo.");
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

/*==============================================================================
 * Funzioni relative alle voci del menu
 *============================================================================*/

/**
 * Gestisce l'inserimento di un elemento nella lista
 *
 * Chiede all'utente di immettere un numero, effettuandone l'inserimento nella
 * lista e notificando l'esito dell'operazione
 * */
NODE *GestisciInserimentoNumero( NODE *Head, OPERATIONS *Op)
{
	int  Value;        /**< Variabile temporanea per la lettura da stdin */
	int  Success;      /**< Flag per valori di ritorno delle funzioni */
	int  ReturnStatus; /**< Stato delle funzioni che agiscono sulla lista */

	printf("\nInserire il numero intero.\n");
	printf("?>");
	Success = LeggiIntero(&Value);

	if( Success )
	{
		//Effettua l'inserimento
		Head = List_Insert( (void *)&Value, Head, &ReturnStatus, Op);

		//Verifica se c'è stato un errore nell'inserimento
		if( ReturnStatus > 0 )
		{
			printf("\nC'e' stato un errore nell'inserimento\n\n");
		}
		//Ok, valore inserito
		else
		{
			printf("\nValore inserito\n\n");
		}
	}
	//valore immesso dall'utente non valido: non è un intero
	else 
	{
		printf("\n\nValore non valido\n\n");
	}

	return Head;
}

/**
 * Gestisce la cancellazione di un elemento dalla lista
 *
 * Chiede all'utente di immettere un numero, effettuandone la cancellazione dalla
 * lista e notificando l'esito dell'operazione
 * */
NODE *GestisciCancellazioneNodo( NODE *Head, OPERATIONS *Op )
{
	int  Value;        /**< Variabile temporanea per la lettura da stdin */
	int  Success;      /**< Flag per valori di ritorno delle funzioni */
	int  ReturnStatus; /**< Stato delle funzioni che agiscono sulla lista */

	//effettua l'eliminazione solo se la lista è non vuota
	if ( Head != NULL )
	{
		printf("\nInserire il numero da eliminare\n");
		printf("?>");
		Success = LeggiIntero(&Value);

		if( Success )
		{
			//Effettua la cancellazione
			Head = List_RecursiveDelete(&Value, Head, &ReturnStatus, Op);

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
		//Il valore immesso dall'utente non è valido: non è un intero
		else 
		{
			printf("\n\nValore non valido\n\n");
		}
	}
	else //lista vuota
	{
		printf("\n\nLa lista e' gia' vuota.\n\n");
	}

	return Head;
}

/**
 * Gestisce la cancellazione della lista
 *
 * Dealloca tutti i nodi della lista, notificando l'esito dell'operazione
 * */
NODE *GestisciDistruzioneLista( NODE *Head, OPERATIONS *Op )
{
	//dealloca la lista solo se non vuota
	if( Head != NULL )
	{
		printf("\n\nCancellazione Lista...\n\n");
		Head = List_RecursiveDestroy( Head, Op );
	}
	else
	{
		printf("\n\nLa lista e' gia' vuota.\n\n");
	}

	return Head;
}

/**
 * Gestisce l'inserimento di numeri casuali all'interno della lista
 *
 * Chiede all'utente di immettere la quantità di numeri casuali da
 * inserire nella lista e li inserisce.
 * I numeri sono compresi tra 0 e MAX_RAND_NUM
 * NOTA
 * Se un numero è già presente in lista, non verrà inserito. Quindi
 * il quantitativo di numeri effettivamente inserito potrebbe essere
 * minore 
 * */
NODE *GestisciInserimentoNumeriCasuali( NODE *Head, OPERATIONS *Op )
{
	int  Value;        /**< Variabile temporanea per la lettura da stdin */
	int  Success;      /**< Flag per valori di ritorno delle funzioni */
	int  ReturnStatus; /**< Stato delle funzioni che agiscono sulla lista */
    int  RandomNum;    /**< Variabile temporanea per memorizzare numeri random*/
	int  i;            /**< Indice per cicli */

	printf("\nQuanti numeri casuali inserire?\n");
	printf("?>");
	Success = LeggiIntero(&Value);

	if( Success )
	{	
		for( i=0; i < Value; i++)
		{
			//Genera un numero compreso tra 0 e MAX_RAND_NUM-1
			RandomNum = rand() % MAX_RAND_NUM; 
			Head = List_RecursiveOrderedInsert( &RandomNum, Head, &ReturnStatus, Op);
		}
		printf("\n\nNumeri inseriti correttamente.\n\n");
	}
	else //Il valore immesso non è un intero
	{
		printf("\n\nValore non valido\n\n");
	}

	return Head;
}
/**
 * Gestisce la stampa della lista, notificando l'utente dell'esito dell'operazione
 *
 * */
void GestisciStampaNumeri( NODE *Head, OPERATIONS *Op )
{
	if( Head != NULL )
	{
		printf("\n\n=================================================\n\n");
		List_RecursivePrint( Head, Op );
		printf("\n\n=================================================\n\n");
	}
	else
	{
		printf("\n\nLa lista e' vuota.\n\n");
	}
}
/**
 * Gestisce la cancellazione di un intervallo di interi
 *
 * Chiede all'utente di immettere i limiti inferiore e superiore dell'intervallo,
 * eliminando tutti i numeri compresi, e notificando l'esito dell'operazione
 *
 * */
NODE *GestisciCancellazioneIntervallo( NODE *Head, OPERATIONS *Op )
{
	int  Inf;     /**< Limite inferiore dell'intervallo da eliminare */
	int  Sup;     /**< Limite superiore dell'intervallo da eliminare */
	int  Success; /**< Flag per valori di ritorno delle funzioni */

	//effettua l'eliminazione solo se la lista è non vuota
	if ( Head != NULL )
	{
		printf("\nInserire il limite inferiore dell'intervallo\n");
		printf("?>"); 
		Success = LeggiIntero(&Inf);

		printf("\nInserire il limite superiore dell'intervallo\n");
		printf("?>"); 
		Success = LeggiIntero(&Sup);

		if( Success )
		{
			Head = List_RecursiveDeleteRange(Head, &Inf, &Sup, Op);
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

	return Head;
}
