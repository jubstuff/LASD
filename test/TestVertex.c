#include "mem.h"
#include "unity.h"
#include "errors.h"
#include "jvertex.h"

J_STATUS ReturnStatus;
J_VERTEX *V;

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * TEST
 * */

void test_VertexNewShouldAllocateNewVertexWithNullLabel(void)
{
    char *str;
    int Len;

    ReturnStatus = JVertex_New( &V );
    TEST_ASSERT_EQUAL( SUCCESS, ReturnStatus );

    /* In questo passaggio voglio recuperare l'etichetta del vertice V.
     * Per prima cosa recupero la lunghezza dell'etichetta e, nel caso sia
     * maggiore di zero, alloco una stringa sufficientemente grande da contenere
     * l'etichetta.
     * */
    ReturnStatus = JVertex_GetLengthLabel( &Len, V );
    TEST_ASSERT_EQUAL( ERROR, ReturnStatus );
    if( Len > 0 )
    {
        ReturnStatus = MemAlloc( Len + 1, (void **)&str );
        TEST_ASSERT_EQUAL( SUCCESS, ReturnStatus );
    }
    JVertex_GetLabel(&str , V);

    TEST_ASSERT_NULL( str );

    MemFree( (void **)&str );
    MemFree( (void **)&V );



}
