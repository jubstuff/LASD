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
void RecuperaInt( const void *NodeValue, void *OutValue );

static JLIST_METHODS Op;
static int Value;
static J_STATUS ReturnStatus;
J_LIST *List;

void setUp(void)
{

	/* Inizializza la struct con le operazioni */
   	Op.Compare = NumCmp;
   	Op.InitNode = InizializzaNodoInt;
	Op.Delete = DeallocaInt;
   	Op.Print = StampaNodoInt;
    Op.ManageDuplicate = DuplicatoInt; 
    Op.GetNodeValue = RecuperaInt;


    JList_Init(&List, &Op);

}

void tearDown(void)
{
    JList_Destroy( List );
}

/**
 * TEST
 * */

void test_ListOrderdedInsertWithListStruct(void)
{
    TEST_ASSERT_EQUAL(1, JList_isEmpty(List) );
    Value = 10;
    ReturnStatus = JList_OrderedInsert( (void *)&Value, List );
    Value = 1;
    ReturnStatus = JList_OrderedInsert( (void *)&Value, List );
    JList_Print(List);
    TEST_ASSERT_EQUAL(0, JList_isEmpty(List) );
    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);
}

void test_ListDeleteReallyRemovesNode(void)
{
    Value = 10;
    ReturnStatus = JList_OrderedInsert( (void *)&Value, List );
    TEST_ASSERT_EQUAL(0, JList_isEmpty(List));
    ReturnStatus = JList_DeleteNode( (void *)&Value, List );
    TEST_ASSERT_EQUAL(1, JList_isEmpty(List));

    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);

}

void test_HeadInsertInsertInHead(void)
{
    Value = 4;
    printf("Insert 4 in Head\n");
    ReturnStatus = JList_HeadInsert( (void *)&Value, List );
    printf("Insert 1 in Head\n");
    Value = 1;
    ReturnStatus = JList_HeadInsert( (void *)&Value, List );
    printf("Insert 9 in Head\n");
    Value = 9;
    ReturnStatus = JList_HeadInsert( (void *)&Value, List );
    JList_Print(List);
}

void test_HeadDeleteDeleteInHead(void)
{
    int Output;

    Value = 4;
    printf("Insert 4 in Head\n");
    ReturnStatus = JList_HeadInsert( (void *)&Value, List );
    printf("Insert 1 in Head\n");
    Value = 1;
    ReturnStatus = JList_HeadInsert( (void *)&Value, List );
    printf("Insert 9 in Head\n");
    Value = 9;
    ReturnStatus = JList_HeadInsert( (void *)&Value, List );
    JList_Print(List);

    ReturnStatus = JList_HeadDelete( (void *)&Output, List );
    printf("Il nodo rimosso dalla testa è %d\n", Output);
    JList_Print(List);
}

void test_DeleteRange(void)
{
    /* Funziona solo su una lista ordinata */
    int i;
    int Inf = 3;
    int Sup = 6;
    for( i = 0; i < 10; i++ )
    {
        Value = i+1;
        printf("Insert %d in List\n", Value);
        ReturnStatus = JList_OrderedInsert( (void *)&Value, List );
    }
    printf("Delete from %d to %d\n", Inf, Sup);
    JList_DeleteRange( (void *)&Inf, (void *)&Sup, List );
    JList_Print(List);
}

void test_SearchEmptyListFails(void)
{
    Value = 5;
    NODE *ResultNode;
    ReturnStatus = JList_Search( (void *)&Value, List, &ResultNode);
    TEST_ASSERT_NULL(ResultNode);
}

void test_SearchExistingNodeSucceed(void)
{
    Value = 5;
    int Result;
    NODE *ResultNode;

    ReturnStatus = JList_OrderedInsert( (void *)&Value, List );
    ReturnStatus = JList_Search( (void *)&Value, List, &ResultNode);
    
    Result = *((int *)JNode_GetData(ResultNode));
    TEST_ASSERT_EQUAL(SUCCESS, ReturnStatus);
    TEST_ASSERT_EQUAL(5, Result);
}

void test_SeachNotExistingNodeFails(void)
{
    Value = 10;
    NODE *ResultNode;
    ReturnStatus = JList_OrderedInsert( (void *)&Value, List );
    Value = 5;
    ReturnStatus = JList_Search( (void *)&Value, List, &ResultNode);
    TEST_ASSERT_EQUAL(W_LIST_NOTFOUND, ReturnStatus);
}

/**
 * DEFINIZIONE TEST HELPERS
 * */
void *InizializzaNodoInt( void *Value )
{
	/* int *Num = (int *) malloc( sizeof(int) ); */
	int *Num = NULL;
	MemAlloc( sizeof(int), (void **)&Num );
	
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

void RecuperaInt( const void *NodeValue, void *OutValue )
{
    int *NumPtr = (int *)OutValue;
    *NumPtr = *( (int *)NodeValue );
    OutValue = (void *)NumPtr;

}
