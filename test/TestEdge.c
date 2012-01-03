#include "mem.h"
#include "unity.h"
#include "errors.h"
#include <string.h>
#include "lista.h"
#include <stdlib.h>
#include "jvertex.h"
#include "jedge.h"

J_STATUS ReturnStatus;
J_EDGE *E;


void setUp(void)
{
    ReturnStatus = JEdge_New( &E );
}

void tearDown(void)
{
    JEdge_Destroy( E );
}


void test_NewEdge(void)
{
    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);
    TEST_ASSERT_NULL( E->DestVertex );
    TEST_ASSERT_EQUAL( 0, E->Weight );
}

void test_SetEdgeWeight(void)
{
    JEdge_SetWeight( 5, E );
    TEST_ASSERT_EQUAL( 5, E->Weight );
}

void test_SetEdgeDestination(void)
{
    J_VERTEX *V;
    JVertex_New( &V );
    JVertex_SetLabel( "Vertice", V );

    JEdge_SetDestVertex( V, E );
    TEST_ASSERT_EQUAL_HEX( V, E->DestVertex );

    JVertex_Destroy( V );
}
