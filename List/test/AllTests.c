

/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"


extern void TestInitializedListIsEmpty(CuTest*);
extern void TestInsertOneNodeInFrontOfList(CuTest*);
extern void TestInsertIsDoneInOrder(CuTest*);
extern void TestInsertDuplicateDoesNotInsertNewNode(CuTest*);
extern void TestInsertNotDoneWhenMallocFails(CuTest*);


void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();


    SUITE_ADD_TEST(suite, TestInitializedListIsEmpty);
    SUITE_ADD_TEST(suite, TestInsertOneNodeInFrontOfList);
    SUITE_ADD_TEST(suite, TestInsertIsDoneInOrder);
    SUITE_ADD_TEST(suite, TestInsertDuplicateDoesNotInsertNewNode);
    SUITE_ADD_TEST(suite, TestInsertNotDoneWhenMallocFails);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void)
{
    RunAllTests();
    return 0;
}

