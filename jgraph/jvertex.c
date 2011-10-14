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
		/* Initialize vertex's members */
		Vert->Label = NULL;
		Vert->Data  = NULL;
	}
	else
	{
		/* Error in malloc */
		fprintf(stderr, "Error in malloc\n");
	}
	/* Return pointer to new vertex */
	return Vert;

}   

/**
 *
 * Delete a Vertex
 *
 * @return 0 if all went good
 *
 * */
int JVertex_Delete( J_VERTEX *V )
{
	/* Wipe all data from Vertex and free memory */
	//TODO delete user data
	free( V->Label );
	free( V );
	return 0;
}

char *JVertex_GetLabel( J_VERTEX *This )
{
	return This->Label;
}

char *JVertex_SetLabel( J_VERTEX *This, size_t Len, const char *NewLabel )
{
	if( This->Label == NULL )
	{
		/* First time allocation of Label */
		This->Label = (char *)malloc(Len + 1);
	}
	else if( strlen(This->Label) != Len )
	{
		/* Update of existing Label */
		This->Label = (char *)realloc(This->Label, Len + 1);
	}
	
	if( This->Label )
	{
		/* If memory allocation went good */
		/* Copy the passed string in Vertex->Label */
		strncpy(This->Label, NewLabel, Len);
		This->Label[Len] = '\0';
	}
	else
	{
		/* malloc/realloc failed */
		fprintf(stderr, "Error in malloc\n");
	}
	return This->Label;
}

#ifdef TEST_DRIVER
#include <assert.h>
int main()                     
{
	J_VERTEX *V = NULL;
	const char *str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	const char *str2 = "B";
	size_t Len = strlen(str);
	size_t Len2 = strlen(str2);

	
	V = JVertex_New();
	assert( V->Data == NULL );
	assert( V->Label == NULL );

	JVertex_SetLabel( V, Len, str ); 
	assert( strcmp(V->Label, str) == 0 );
	assert( strlen(V->Label) == Len );

	assert( strcmp(JVertex_GetLabel(V), str) == 0 );

	printf("%s\n", V->Label);

	JVertex_SetLabel(V, Len2, str2);
	assert( strcmp(V->Label, str2) == 0);
	assert( strlen(V->Label) == Len2 );

	assert( strcmp(JVertex_GetLabel(V), str2) == 0 );

	printf("%s\n", V->Label);


    assert( JVertex_Delete( V ) == 0 );

    printf("Test went all fine!\n");

	return 0;

}
#endif
