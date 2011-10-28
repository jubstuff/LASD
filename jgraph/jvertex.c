#include "jvertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jvertex_tag
{
	char *Label; /**< Vertex's Label */
	void *Data;  /**< Vertex's Data */
};

J_VERTEX *JVertex_New()
{
}   

int JVertex_Delete( J_VERTEX *V )
{
}

char *JVertex_GetLabel( J_VERTEX *This )
{
}

char *JVertex_SetLabel( J_VERTEX *This, size_t Len, const char *NewLabel )
{
}

void JVertex_SetData( void *Data, J_VERTEX *V)
{
}
