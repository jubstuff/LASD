#include "atom.h"
#include "../mem/mem.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

char *GenRandom(char *S, int Len)
{
	int i;
	static const char Alphanum[] = 
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	for( i = 0; i < Len; ++i )
	{
		S[i] = Alphanum[rand() % sizeof(Alphanum) - 1];
	}
	S[Len] = '\0';
	return S;
}


int main(void)
{
	Atom_new("prova", sizeof("prova"));
	Atom_new("prova", sizeof("prova"));
#ifdef TEST
	char str[10];
	struct timeval t1;
	gettimeofday(&t1, NULL);
	int i;

	srand(t1.tv_usec * t1.tv_sec);

	for( i = 0; i < 10000; i++)
	{
		Atom_new(GenRandom(str, sizeof str), 10);
	}

	VisitAtoms();
#endif


	return 0;
}
