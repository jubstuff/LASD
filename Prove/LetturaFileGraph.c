/*=============================================================================
 *
 * Nome File: LetturaFileGraph.c
 *
 * Scopo: Prova per lettura del file rappresentante un grafo
 *
 * Data Creazione: 16-05-2011
 *
 * Ultima Modifica: lun 16 mag 2011 23:42:28 CEST
 *
 * Autore: Giustino Borzacchiello - giustinob@gmail.com
 *
 *
 =============================================================================*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *tempStr;
	FILE *Fp;
	char Delim[] = ";";
	long BufSize;
	char *Buffer;
	size_t LenFile;
	int NumVertici;

	//char GraphTxt[] = "(4) A -> C; B -> C D; C -> A B D; D -> B C;.";
	//char GraphTxt[] = "(4) A -> (1)C; B -> (2)C (3)D; C -> (1)A (2)B (4)D; D -> (3)B (4)C;.";
	//tempStr = strtok( GraphTxt, "()" );
	//int NumVertici = atoi(tempStr);
	//printf("Ci sono %d vertici\n", NumVertici );
	//while( tempStr )
	//{
	//	printf( "%s\n", tempStr );
	//	tempStr = strtok( NULL, Delim );
	//}
	
	//Apro il file
	Fp = fopen("grafo.txt", "r");
	if( Fp != NULL )
	{
		//Mi posiziono alla fine del file
		if( fseek(Fp, 0L, SEEK_END ) == 0 )
		{
			//Recupero il valore del file position indicator
			BufSize = ftell(Fp);
			if( BufSize == -1 )
			{
				//error
			}
			//Alloco lo spazio necessario per contenere tutto il file
			Buffer = (char *)malloc( (BufSize + 1) * sizeof(char) );

			//Riposiziono l'indicatore all'inizio del file
			if( fseek( Fp, 0L, SEEK_SET ) == 0 ) 
			{
				//Error
			}
            //Leggo tutto il file in memoria
			LenFile = fread( Buffer, sizeof(char), BufSize, Fp );
			if( LenFile == 0 )
			{
				fputs("Error reading file",stderr);
			}
			else
			{
				//Per sicurezza imposto il termine stringa
				Buffer[++LenFile] = '\0';
			}
		}
		fclose(Fp);
	}


	//Recupero il numero di vertici, tra parentesi
	tempStr = strtok( Buffer, "()" );
	NumVertici = atoi(tempStr);
	printf("Ci sono %d vertici\n", NumVertici );
	while( tempStr )
	{
		printf( "%s\n", tempStr );
		tempStr = strtok( NULL, Delim );
	}
    free( Buffer );
	return 0;
}
