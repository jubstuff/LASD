#include "mem.h"
#include "unity.h"
#include "errors.h"
#include <string.h>
#include "lista.h"
#include <stdlib.h>
#include "jvset.h"
#include "jeset.h"

J_STATUS ReturnStatus;
J_ESET *ESet;
J_VSET *VSet;
int HintNumVertices = 4;

void setUp(void)
{

    JVset_Init(HintNumVertices, &VSet);
    JEset_New( HintNumVertices, &ESet );
}

void tearDown(void)
{
    JEset_Destroy(ESet);
    JVset_Destroy( VSet );
}


void test_Test(void)
{
}
