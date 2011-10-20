#include "mem.h"
#include "unity.h"
#include "errors.h"

#define MEGABYTE 1024*1024

void setUp(void)
{
}

void tearDown(void)
{

}

void test_MemAllocAllocatingOneByteIsSuccess(void)
{
	void *Ptr;
	J_STATUS Status;

	Status = MemAlloc(1, &Ptr);
	TEST_ASSERT_EQUAL(SUCCESS, Status);
}

void test_MemAllocAllocatingTooMuchMemoryIsError(void)
{
	void *Ptr;
	J_STATUS Status;
	int i;

	/* Tento di allocare 10 Gigabyte */
	for(i = 0; i < 10000; i++)
	{
		Status = MemAlloc(MEGABYTE, &Ptr);
	}
	TEST_ASSERT_EQUAL(ERROR, Status);
	TEST_ASSERT_NULL(Ptr);
}

void test_MemCallocAllocatingOneByteIsSuccess(void)
{
	void *Ptr;
	J_STATUS Status;

	Status = MemCalloc(1, 1, &Ptr);
	TEST_ASSERT_EQUAL(SUCCESS, Status);
}

void test_MemCallocAllocatingTooMuchMemoryIsError(void)
{
	void *Ptr;
	J_STATUS Status;
	int i;

	/* Tento di allocare 10 Gigabyte */
	for(i = 0; i < 10000; i++)
	{
		Status = MemCalloc(1, MEGABYTE, &Ptr);
	}
	TEST_ASSERT_EQUAL(ERROR, Status);
	TEST_ASSERT_NULL(Ptr);
}

#undef MEGABYTE
