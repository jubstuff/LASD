#include "jvertex.h"
#include "errors.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jvertex_tag
{
	char *Label; /**< Vertex's Label */
	void *Data;  /**< Vertex's Data */
};

void JVertex_Delete( J_VERTEX *V )
{
}

void JVertex_GetLabel( J_VERTEX *This )
{
}

J_STATUS JVertex_SetLabel( char *Label, J_VERTEX *V)
{
    int LabelLen;
    J_STATUS ReturnStatus;

    LabelLen = strlen(Label);

    ReturnStatus = MemAlloc( LabelLen + 1, (void **)&(V->Label) );
    if( ReturnStatus == SUCCESS )
    {
        strcpy(V->Label, Label);
    }

    return ReturnStatus;
}

void JVertex_SetData( void *Data, J_VERTEX *V)
{
    V->Data = Data;
}

J_STATUS JVertex_CreateArray(int HintNumVertices, J_VERTEX **V)
{
    J_STATUS ReturnStatus;

    ReturnStatus = SUCCESS;

    return ReturnStatus;
}
