#include <stdio.h>
#include <string>
#include <stdlib.h>

#include "gtest/gtest.h"
using namespace std;

/* ================================================================== */
/*                Delete one item from linked list                    */
/* ================================================================== */

struct ListNode
{
    int value;
    ListNode *pNext;
};

bool DeleteOneFromList(ListNode *&list,ListNode *toDelete)
{
    if(list == NULL || toDelete == NULL)
        return false;

    if(toDelete->pNext == NULL)
    {
        // from start scan
        ListNode *pScan = list;
        while(pScan->pNext != toDelete && pScan->pNext != NULL)
        {
            pScan = pScan->pNext;
        }

        if(list == toDelete)
		{
			delete toDelete;
			list = toDelete = NULL;
		}
		else if(pScan->pNext == toDelete)
		{
            pScan->pNext = NULL;
			delete toDelete;
			toDelete = NULL;
		}
		else if(pScan->pNext == NULL)
			return false;
    }
    else
    {
		ListNode *pNext = toDelete->pNext;
		toDelete->value = pNext->value;
		toDelete->pNext = pNext->pNext;

		delete pNext;
		pNext = NULL;
    }

    return true;
}

/* ================================================================== */
/*                           Dev test                                 */
/* ================================================================== */

void MakeLinkedList(int *input,int input_len,ListNode *output)
{
    ListNode *cur;
    cur = output;
	for(int i = 0;i < input_len;i++)
	{
        cur->value = input[i];
		if(i != input_len - 1)
			cur->pNext = new ListNode();
		else
			cur->pNext = NULL;
		cur = cur->pNext;
    }
}

void PrintLinkedList(ListNode *output)
{
    ListNode *cur = output;
    while(cur != NULL)
    {
        printf("%d",cur->value);
		if(cur->pNext != NULL)
			printf("-");
        cur = cur->pNext;
    }
    printf("\n");
}

string LinkedListToString(ListNode *output)
{
	string res = "";
    ListNode *cur = output;
    while(cur != NULL)
    {
		char tmp[64];
		if(cur->pNext != NULL)
			sprintf(tmp,"%d-",cur->value);
		else
			sprintf(tmp,"%d",cur->value);
        cur = cur->pNext;
		res += tmp;
    }

	return res;
}

void DestroyLinkedList(ListNode *&list)
{
	if(list == NULL)
		return;

	ListNode *cur = list;
	ListNode *next;
	while(cur != NULL)
	{
		next = cur->pNext;
		delete cur;
		cur = next;
	}
}

void DevTest()
{
	ListNode *list = new ListNode();
    int input[] = {2,4,5,1,8,4};
    int len = 6;
    MakeLinkedList(input,len,list);

	ListNode *toDelete = list->pNext->pNext;
	DeleteOneFromList(list,toDelete);

    PrintLinkedList(list);
}

/* ================================================================== */
/*                           Unit test                                */
/* ================================================================== */

class LinkedList_Test:public testing::Test
{
protected:
    void SetUp()
    {
        list = new ListNode();
    }
    void TearDown()
    {
        DestroyLinkedList(list);
    }

	ListNode *list;
};

TEST_F(LinkedList_Test, Common1)
{
	int input[] = {2,4,5,1,8,4};
	MakeLinkedList(input,6,list);

	ListNode *toDelete = list->pNext->pNext;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("2-4-1-8-4", strList.c_str());
}

TEST_F(LinkedList_Test, Common2)
{
	int input[] = {4,5,3,12,8};
	MakeLinkedList(input,5,list);

	ListNode *toDelete = list;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("5-3-12-8", strList.c_str());
}

TEST_F(LinkedList_Test, Common3)
{
	int input[] = {4,5,3,12,8};
	MakeLinkedList(input,5,list);

	ListNode *toDelete = list->pNext->pNext->pNext->pNext;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("4-5-3-12", strList.c_str());
}

TEST_F(LinkedList_Test, Boundary1)
{
	int input[] = {4};
	MakeLinkedList(input,1,list);

	ListNode *toDelete = list;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("", strList.c_str());
}

TEST_F(LinkedList_Test, Boundary2)
{
	int input[] = {4,5};
	MakeLinkedList(input,2,list);

	ListNode *toDelete = list;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("5", strList.c_str());
}

TEST_F(LinkedList_Test, Boundary3)
{
	int input[] = {4,5};
	MakeLinkedList(input,2,list);

	ListNode *toDelete = list->pNext;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("4", strList.c_str());
}

TEST_F(LinkedList_Test, Error)
{
	list = NULL;
	ListNode *toDelete = NULL;
	DeleteOneFromList(list,toDelete);

    string strList = LinkedListToString(list);

	EXPECT_STREQ("", strList.c_str());
}

int main(int argc,char** argv)
{
	//DevTest();
	testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
    
    printf("success!\n");
}
