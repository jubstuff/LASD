#include "atom.h"
#include "../mem/mem.h"

int main(void)
{
	Atom_new("prova", sizeof("prova"));
	Atom_new("prova", sizeof("prova"));

	return 0;
}
