#include "mem.h"
#include "unity.h"
#include "errors.h"
#include "jvset.h"

J_STATUS ReturnStatus;
J_VSET *Vertices;

void setUp(void)
{
    JVset_Init(10, &Vertices);
}

void tearDown(void)
{
    JVset_Destroy( Vertices );
}

/**
 * TEST
 * */

void test_VertexNewShouldAllocateNewVertexWithNullLabel(void)
{

}
