#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "errors.h"
#include "jvset.h"

J_STATUS ReturnStatus;
J_VSET *Set;

void setUp(void)
{
    JVset_Init(4, &Set);
}

void tearDown(void)
{
    JVset_Destroy( Set );
}

void printVertex( J_VERTEX *V )
{
    printf("%s\n", V->Label);
}

/**
 * TEST
 * */

void test_AddVertexWithLabel(void)
{
    char *str;
    str = malloc(100 * sizeof(char));
    J_VERTEX *V = NULL;

    JVset_AddVertex("Vertice A", NULL, Set);
    JVset_FindVertexByLabel("Vertice A", &V, Set );
    JVertex_CopyLabel(&str, V);
    TEST_ASSERT_EQUAL_STRING("Vertice A", str);

    free(str);
}

void test_AddVertexWithSameLabelShouldFail(void)
{
    ReturnStatus = JVset_AddVertex("Vertice A", NULL, Set);
    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);
    ReturnStatus = JVset_AddVertex("Vertice A", NULL, Set);
    TEST_ASSERT_EQUAL(ERROR, ReturnStatus);
}

void test_ReallocFreeList(void)
{
    JVset_AddVertex("Vertice 1", NULL, Set);
    JVset_AddVertex("Vertice 2", NULL, Set);
    JVset_AddVertex("Vertice 3", NULL, Set);
    JVset_AddVertex("Vertice 4", NULL, Set);
    JVset_AddVertex("Vertice 5", NULL, Set);
    /* quali conseguenze porta questo test? */

}

void test_FindByLabel(void)
{
    J_VERTEX *V = NULL;
    char *str;
    str = malloc(100 * sizeof(char));

    JVset_AddVertex("Vertice A", NULL, Set);
    JVset_FindVertexByLabel("Vertice A", &V, Set );
    //TEST_ASSERT_NOT_NULL(V);
    JVertex_CopyLabel(&str, V);
    TEST_ASSERT_EQUAL_STRING("Vertice A", str);
    free(str);
}

void test_DeleteVertex(void)
{
    JVset_AddVertex("Vertice A", NULL, Set);
    JVset_AddVertex("Vertice B", NULL, Set);
    JVset_AddVertex("Vertice C", NULL, Set);
    JVset_AddVertex("Vertice D", NULL, Set);
    JVset_RemoveVertex("Vertice D", Set);
    JVset_RemoveVertex("Vertice B", Set);
    JVset_AddVertex("Vertice E", NULL, Set);
}

void test_StampaEtichette(void)
{
    JVset_AddVertex("Vertice D", NULL, Set);
    JVset_AddVertex("Vertice B", NULL, Set);
    JVset_AddVertex("Vertice A", NULL, Set);
    JVset_AddVertex("Vertice C", NULL, Set);

    JVset_PrintSet(printVertex, Set );
}
