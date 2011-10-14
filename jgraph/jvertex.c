#include "jvertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jvertex_tag
{
	char *Label; /**< Vertex's Label */
	int  *Data;  /**< Vertex's Data */ //TODO questo deve essere generico, non un int
};

/**
 * Allocate a new Vertex and initialize its attributes
 *
 * @return Pointer to new vertex created
 * 		   NULL on error
 *
 * */
J_VERTEX *JVertex_New()
{
	J_VERTEX *Vert = NULL; /**< Temporary vertex */

	/* Create new vertex */
	Vert = (J_VERTEX *)malloc(sizeof(struct jvertex_tag));
	if( Vert )
	{
		/* Initialize vertex 
		 *
		 * This call uses a technique named shredding[1]
		 * In this way, when debugging, I can realize wheter I'm working with
		 * uninitialized structs. 
		 *
		 * [1] "Writing solid code" - Steve Maguire
		 * */
		memset(Vert, 0xda, sizeof(J_VERTEX));
	}
	else
	{
		/* Error in malloc */
		fprintf(stderr, "Error in malloc\n");
	}
	/* Return pointer to new vertex */
	return Vert;

}   


#ifdef TEST_DRIVER
#include <assert.h>
int main()                     
{
	J_VERTEX *V = NULL;

	
	V = JVertex_New();
	assert( V->Data == 0xdadadada );
	assert( V->Label == 0xdadadada );

	return 0;

}
#endif
