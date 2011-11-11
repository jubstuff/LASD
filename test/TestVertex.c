#include "mem.h"
#include <stdlib.h>
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

/**
 * TEST
 * */

void test_AddVertexWithLabel(void)
{
    char *str;
    str = malloc(100 * sizeof(char));

    JVset_AddVertex("Amore", NULL, Set);
    J_VERTEX *ptr = JVset_GetVertex(0, Set);
    JVertex_GetLabel(&str, ptr);
    printf("Etichetta: %s\n", str);

    free(str);
}

void test_ReallocFreeList(void)
{
    JVset_AddVertex("Amore1", NULL, Set);
    JVset_AddVertex("Amore2", NULL, Set);
    JVset_AddVertex("Amore3", NULL, Set);
    JVset_AddVertex("Amore4", NULL, Set);
    JVset_AddVertex("Amore5", NULL, Set);

}

void test_FindByLabel(void)
{
    J_VERTEX *V;
    char *str;
    str = malloc(100 * sizeof(char));

    JVset_AddVertex("Vertice A", NULL, Set);
    V = JVset_FindVertexByLabel("Vertice A", Set );
    TEST_ASSERT_NOT_NULL(V);
    JVertex_GetLabel(&str, V);
    printf("Etichetta: %s\n", str);
    free(str);
}

void test_DeleteVertex(void)
{
    J_VERTEX *V;
    JVset_AddVertex("Vertice A", NULL, Set);
    JVset_AddVertex("Vertice B", NULL, Set);
    JVset_AddVertex("Vertice C", NULL, Set);
    JVset_AddVertex("Vertice D", NULL, Set);
    JVset_RemoveVertex("Vertice D", Set);
    JVset_RemoveVertex("Vertice B", Set);
    JVset_AddVertex("Vertice E", NULL, Set);
}
