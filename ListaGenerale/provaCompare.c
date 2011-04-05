#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//( int (*)(void *, void *) )
//       ^
//       |___Accanto a questo * ci dovrebbe essere il nome della funzione: è anonimo perché mi serve solo per il cast

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

void MiaFunzione( void *A, void *B, int (*Comp)(void *, void *) )
{
	printf("%s|%s: %d\n", A, B, (*Comp)((void *)A,(void *)B));
}

int main( int argc, char **argv )
{
    int a = atoi(argv[1]);
	int b = atoi(argv[2]);

    //MiaFunzione(a, b, (int (*)(int,int))(NumComp) );
    MiaFunzione(argv[1], argv[2], (int (*)(void *, void *)) strcmp );
	return 0;
}
