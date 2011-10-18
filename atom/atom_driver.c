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
//	char str[] = "prova";
//	Atom_new(str, strlen(str));
//	VisitAtoms();
//	Atom_free(str);
//	VisitAtoms();

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

	Atom_reset();

	return 0;
}
