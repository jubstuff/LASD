/**
 * operazioni_stringhe.h
 * 
 * @author Giustino Borzacchiello - matr 566/3291 - giustinob@gmail.com
 *
 * @date 07/04/11
 * @package ListaGenerale
 *
 * Realizza alcune semplici funzioni per gestire una lista con nodi contenenti
 * un singolo campo di tipo char*
 * 
 */
#include "operazioni_stringhe.h"
/*==============================================================================
 * Definizione di funzioni per la lista di stringhe
 *============================================================================*/
void *InizializzaNodoStringa( void *Value )
{
	char *Temp = (char *)Value;
	char *str= (char *) malloc( (strlen(Temp) + 1) * sizeof(char) );
	strcpy(str, Temp);
	return str;
}

void StampaNodoStringa(const void *Value)
{
	printf("%s\n", (char *)Value);
}

void DeallocaStringa( void *Value )
{
	free( (char *)Value );
}

int ConfrontaStringhe( const void *Str1, const void *Str2 )
{
	return strcasecmp( (char *)Str1, (char *)Str2 );
}
/**
 * Scrive la lista di stringhe su file.
 *
 * Il file generato è in formato testuale per garantirne la portabilità ed è 
 * formattato in questo modo:
 * 
 * StringaNodo1
 * StringaNodo2
 * StringaNodo3
 *
 *
 */
void ScriviSuFileDiTesto( const void *Value )
{
	FILE *Fp; /**< Puntatore al file su cui scrivere */
	
	//inizializzazione variabili e parametri
	Fp            = NULL;
	int ReturnStatus = 0;
	
	Fp = fopen( NOME_FILE, "a" );
	if( Fp == NULL )
	{
		ReturnStatus = E_FOPEN; //errore apertura file
	}
	//File aperto, effettua l'operazione di scrittura
	else
	{
		//Finché ci sono nodi, scrivi la stringa sul file
		fprintf( Fp, "%s\n", (char *)Value );
	}
	
	if( fclose(Fp) == EOF )
	{
		ReturnStatus = E_FCLOSE; //errore chiusura del file
	}
}
/**
 * Legge una serie di stringhe da un file, salvandole in una lista concatenata.
 * 
 * Legge un file nel formato:
 * 
 * Stringa1
 * Stringa2
 * Stringa3
 *
 * creando un nodo per ogni stringa, e restituendo la testa della lista creata.
 *
 * @param NomeFile     Nome del file da cui leggere le stringhe.
 * @param Lenmax       Lunghezza massima della riga (in lettura).
 * @param ReturnStatus Esito dell'operazione. Può assumere valore:
 *	                   - 0, in caso di inserimento corretto
 *                     - E_FOPEN, in caso di errore all'apertura del file
 *                     - E_FCLOSE, in caso di errore alla chiusura del file
 *                     - E_MALLOC, in caso di errore nella creazione del nodo
 *
 * @return La testa della lista creata dalla lettura del file
 */
NODE *CaricaListaDaFile ( char *NomeFile, int LenMax, int *ReturnStatus, OPERATIONS *Op )
{
	NODE *TempHead;    /**< Testa della lista temporanea */
	FILE *Fp;          /**< Puntatore al file da cui leggere */
	char *TempBuffer;  /**< Buffer temporaneo per le stringhe */
	
	//inizializzazione variabili e parametri
	Fp            = NULL;
	TempHead      = NULL;
	*ReturnStatus = 0;
	
	//alloca spazio necessario per memorizzare una riga del file
	TempBuffer = (char *) malloc( (LenMax+1) * sizeof(char) );
	if ( TempBuffer == NULL )
	{
		*ReturnStatus = E_MALLOC; //Errore allocazione buffer temporaneo
	}
	else
	{
		Fp = fopen(NomeFile, "r");
		if( Fp == NULL )
		{
			*ReturnStatus = E_FOPEN; //Errore apertura file
		}
		//File aperto: leggi dal file
		else
		{
			//Leggi il file riga per riga, ricostruendo la lista
			//NOTA: se il Fp non è un descrittore valido, fgets ritorna NULL
			while( fgets(TempBuffer, LenMax, Fp) != NULL )
			{
				TempBuffer[strlen(TempBuffer) - 1] = '\0';
				TempHead = List_RecursiveOrderedInsert( TempBuffer, TempHead, ReturnStatus, Op );
			}
			
			if( fclose(Fp) == EOF )
			{
				*ReturnStatus = E_FCLOSE; //errore chiusura file
			}
		}
		//Libera la memoria allocata
		free(TempBuffer);
	}
	
	return TempHead;
}
/*==============================================================================
 * Funzioni di utilità
 *============================================================================*/

/**
 * Legge una stringa da standard input, di lunghezza massima <LenMax>.
 * NOTE 
 *  - Tutti i caratteri di controllo e, in generale, non alfanumerici vengono 
 *    ignorati.
 *  - La stringa viene restituita senza '\n' finale.
 *
 * @param Buf    Stringa digitata dall'utente.
 * @param LenMax Lunghezza massima consentita alla stringa in input.
 */
void LeggiStringa( char *Buf, int LenMax)
{
	fgets(Buf, LenMax, stdin);

	while ( *Buf < 0 || *Buf > 31) //ignora tutti i caratteri non alfanumerici
	{
		Buf++;
	}
	*Buf = '\0';
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
	puts("Lista di Stringhe - Menu");
	printf("=================================================\n");
	puts("1 - Inserisci una stringa nella lista.");
	puts("2 - Eliminare una stringa dalla lista.");
	puts("3 - Eliminare tutti i nodi dalla lista.");
	puts("4 - Salva la lista su file.");
	puts("5 - Caricare la lista da file.");
	puts("9 - Stampa la lista a video.");
	puts("0 - Esci");
	puts("Operazione da effettuare: ");
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
	puts("\n\nBattere un tasto per continuare...");
	getchar();
}