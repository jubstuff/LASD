#include "mem.h"
#include "unity.h"
#include "errors.h"

void setUp(void)
{
}

void tearDown(void)
{

}

void test_AllocatingOneByteIsSuccess(void)
{
	char *Ptr;
	J_STATUS status = MemAlloc(1, (void *)&Ptr);
	TEST_ASSERT_EQUAL(SUCCESS, status);
}

void test_AllocatingTooMuchMemoryIsError(void)
{
#define MEGABYTE 1024*1024
	char *Ptr;
	J_STATUS Status;
	int i;

	/* Tento di allocare 10 Gigabyte */
	for(i = 0; i < 10000; i++)
	{
		Status = MemAlloc(MEGABYTE, (void *)&Ptr);
	}
	TEST_ASSERT_EQUAL(ERROR, Status);
	TEST_ASSERT_NULL(Ptr);
#undef MEGABYTE
}
