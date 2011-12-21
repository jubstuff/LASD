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
int HintNumVertices = 10;

void setUp(void)
{

    JVset_Init(HintNumVertices, &VSet);
    JEset_New( HintNumVertices, &ESet );

    /* Aggiungo i vertici all'insieme */
    JVset_AddVertex("Vertice A", NULL, VSet);
    JVset_AddVertex("Vertice B", NULL, VSet);
    JVset_AddVertex("Vertice C", NULL, VSet);
    JVset_AddVertex("Vertice D", NULL, VSet);
    JVset_AddVertex("Vertice E", NULL, VSet);
    JVset_AddVertex("Vertice F", NULL, VSet);
    JVset_AddVertex("Vertice G", NULL, VSet);


}

void tearDown(void)
{
    JEset_Destroy(ESet);
    JVset_Destroy( VSet );
}


void test_AddEdge(void)
{
    JEset_AddEdge("Vertice A", "Vertice B", 0, VSet, ESet);
}
