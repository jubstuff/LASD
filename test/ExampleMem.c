/* ExampleMem.c
 *
 * File di esempio di utilizzo della libreria Mem
 *
 * Compile: gcc -Wall -pedantic -I../src ExampleMem.c ../src/mem.c -o ExampleMem.out
 *
 * */
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int *Numero;
    char *Stringa;
    J_STATUS Status;

    Status = MemAlloc(sizeof(int), (void **)&Numero);
    if( Status != SUCCESS )
    {
        fprintf(stderr, "Errore Malloc\n");
        exit(1);
    }
    Status = MemAlloc(10*sizeof(char), (void **)&Stringa);
    if( Status != SUCCESS )
    {
        fprintf(stderr, "Errore Malloc\n");
        exit(1);
    }

    *Numero = 50;
    printf("Un coniglio di solito fa %d figli\n", *Numero);

    strcpy(Stringa, "Ciao Just");
    printf("Il pc dice: %s\n", Stringa);



    MemFree((void **)&Stringa);
    MemFree((void **)&Numero);

    return 0;
}
