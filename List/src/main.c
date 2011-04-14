#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

char *InizializzaNodoStringa( char *Value )
{
	char *str= (char *) malloc( (strlen(Value) + 1) * sizeof(char) );
	strcpy(str, Value);
	return str;
}

void StampaNodoStringa(char *Value)
{
	printf("%s\t", Value);
}

void DeallocaStringa( char *Value )
{
	free(Value);
}

int main(void)
{
	LIST L;
   	OPERATIONS Op;
	int Status; 

   	Op.Compare = (COMPARATOR)strcasecmp;
   	Op.InitNode = (INITIALIZER)InizializzaNodoStringa;
	Op.DeleteNode = (DELETER)DeallocaStringa;
   	Op.Print = (PRINTER)StampaNodoStringa;

    List_Init(&L, &Op);
	Status = List_Insert("B", &L);
	Status = List_Insert("A", &L);
	Status = List_Insert("D", &L);
	Status = List_Insert("C", &L);
	Status = List_Insert("F", &L);
	Status = List_Insert("E", &L);
    printf("Stampo lista prima di cancellare F\n");
	List_Print( &L );
	Status = List_Delete("F", &L);
    printf("Stampo lista dopo aver cancellato F\n");
	List_Print( &L );
	List_RecursiveDeleteRange(L.Head, (void *)"B", (void *)"D", L.Op);
    printf("Stampo lista dopo aver cancellato da B a D\n");
	List_Print( &L );

	L.Head = List_RecursiveDeleteRange(L.Head, (void *)"E", (void *)"A", L.Op);
	List_Print( &L );

	L.Head = List_RecursiveDestroy( L.Head, L.Op );
    printf("Stampo lista vuota\n");
	List_Print( &L );
	return 0;
}
