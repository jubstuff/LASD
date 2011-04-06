#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//( int (*)(void *, void *) )
//       ^
//       |___Accanto a questo * ci dovrebbe essere il nome della funzione: è anonimo perché mi serve solo per il cast

int NumComp(int Num1, int Num2);
void function1( int );
void function2( int );
void function3( int );

void MiaFunzione( void *A, void *B, int (*Comp)(void *, void *) )
{
	printf("%s|%s: %d\n", A, B, (*Comp)((void *)A,(void *)B));
}

int main( int argc, char **argv )
{
    //int a = atoi(argv[1]);
	//int b = atoi(argv[2]);
    void (*f[ 3 ])( int ) = { function1, function2, function3 };
	int choice;

	printf("Immettere un numero tra 0 e 2, 3 per terminare\n");
	scanf("%d", &choice);

	while( choice >= 0 && choice < 3 )
	{
		(*f[choice])( choice );
		printf("\nImmettere un numero tra 0 e 2, 3 per terminare\n");
		scanf("%d", &choice);
	}
    //MiaFunzione(a, b, (int (*)(int,int))(NumComp) );
    //MiaFunzione(argv[1], argv[2], (int (*)(void *, void *)) strcmp );
	return 0;
}

int NumComp(int Num1, int Num2) 
{
	int ReturnValue; /**< Valore di ritorno della funzione */

	if( Num1 < Num2 )
	{
		ReturnValue = -1;
	}
	else if ( Num1 == Num2 )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue; 
}

void function1( int a )
{
	printf("Hai immesso %d percio' è stata chiamata function1", a+1);
}

void function2( int b )
{
	printf("Hai immesso %d percio' è stata chiamata function2", b+1);
}

void function3( int c )
{
	printf("Hai immesso %d percio' è stata chiamata function3", c+1);
}
