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
