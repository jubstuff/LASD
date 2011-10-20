#include "mem.h"
#include "unity.h"
#include "errors.h"
#include <string.h>

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
	Ptr = (void *)'a';
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

void test_MemFreeDeallocateAllocatedMemoryIsSuccess(void)
{
	void *Ptr;
	J_STATUS Status;

	MemAlloc(1, &Ptr);

	Status = MemFree(&Ptr);
	TEST_ASSERT_EQUAL(SUCCESS, Status);
}

void test_MemFreePointerAlreadyDeallocatedIsError(void)
{
	void *Ptr;
	J_STATUS Status;

	MemAlloc(1, &Ptr);

	Status = MemFree(&Ptr);
	Status = MemFree(&Ptr);

	TEST_ASSERT_EQUAL(ERROR, Status);
	TEST_ASSERT_NULL(Ptr);
}

void test_MemReallocShouldShrinkMemory(void)
{
	//TEST_IGNORE();
	char *Ptr;
	J_STATUS Status;

	MemAlloc(5, (void **)&Ptr);
	strcpy(Ptr, "ciao");
	Status = MemRealloc(3, (void **)&Ptr);
	TEST_ASSERT_EQUAL(SUCCESS, Status);
	TEST_ASSERT_EQUAL_MEMORY("ci", Ptr, 2);
}

void test_MemReallocShouldEnlargeMemory(void)
{
	char *Ptr;
	J_STATUS Status;

	MemAlloc(5, (void **)&Ptr);
	strcpy(Ptr, "ciao");
	Status = MemRealloc(12, (void **)&Ptr);
	TEST_ASSERT_EQUAL(SUCCESS, Status);
	strcat(Ptr, ", mondo");
	TEST_ASSERT_EQUAL_MEMORY("ciao, mondo", Ptr, 11);

}

#undef MEGABYTE
