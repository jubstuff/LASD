#include "mem.h"
#include "unity.h"
#include "errors.h"
#include <string.h>
#include "lista.h"
#include <stdlib.h>

void *InizializzaNodoInt( void *Value );
void StampaNodoInt( const void *Value );
void DeallocaInt( void *InputValue, void *NodeInfo );
int NumCmp( const void *Num1, const void *Num2 );
void DuplicatoInt( void *Value, NODE *Nodo );

static JLIST_METHODS Op;
static NODE *Head;
static int Value;
static J_STATUS ReturnStatus;
J_LIST List;

void setUp(void)
{
	/* inizializza la lista */
    Head = NULL;
	/* Inizializza la struct con le operazioni */
   	Op.Compare = NumCmp;
   	Op.InitNode = InizializzaNodoInt;
	Op.Delete = DeallocaInt;
   	Op.Print = StampaNodoInt;
    Op.ManageDuplicate = DuplicatoInt; 

    JList_Init(&List, &Op);

}

void tearDown(void)
{

}

/**
 * TEST
 * */

void test_ListOrderdedInsertWithListStruct(void)
{
    Value = 10;
    ReturnStatus = JList_OrderedInsert( (void *)&Value, &List );
    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);
}

void test_ListDeleteRemoveNode(void)
{
    Value = 10;
    ReturnStatus = JList_OrderedInsert( (void *)&Value, &List );
    ReturnStatus = JList_DeleteNode( (void *)&Value, &List );

    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);
    TEST_ASSERT_NULL(List.Head);

}

/**
 * DEFINIZIONE TEST HELPERS
 * */
void *InizializzaNodoInt( void *Value )
{
	/* int *Num = (int *) malloc( sizeof(int) ); */
	int *Num = NULL;
	MemAlloc( sizeof(int), (void **)&Num );
	
	printf("Inizializzo il numero....\n");
	*Num = *( (int *)Value );
	return (void *)Num;
}
void StampaNodoInt( const void *Value )
{
	printf("%d\n", *( (int *)Value) );
}
void DeallocaInt( void *InputValue, void *NodeInfo )
{
	free( NodeInfo );
}
int NumCmp( const void *Num1, const void *Num2 )
{
	int ReturnValue;
	int First = *( (int *)Num1 );
	int Second = *( (int *)Num2 );

	if ( First < Second )
	{
		ReturnValue = -1;
	}
	else if ( First == Second )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;

}
void DuplicatoInt( void *Value, NODE *Nodo )
{
	int Num = *( (int *)Value );
	printf("Stai cercando di inserire un nodo duplicato\n");
	printf("Il valore che stavi cercando di inserire è %d\n", Num);
}
