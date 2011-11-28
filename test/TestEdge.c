#include "mem.h"
#include "unity.h"
#include "errors.h"
#include <string.h>
#include "lista.h"
#include <stdlib.h>
#include "jvset.h"
#include "jeset.h"

J_STATUS ReturnStatus;
J_ESET *Set;

void setUp(void)
{

    JEset_New( 4, &Set );
}

void tearDown(void)
{
    JEset_Destroy(Set);
}


void test_Test(void)
{
}
