#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "gtest/gtest.h"

using namespace std;

int bin_search(int a[],int len,int item){
	if(a == NULL || len == 0)
		return -1;
	int p = 0;
	int q = len - 1;
	while(p <= q){
		int k = (p+q)/2;
		if(item == a[k])
			return k;
		else if(item > a[k])
			p = k+1;
		else
			q = k-1;
	}

	return -1;
}

/* ================================================================== */
/*                           Unit test                                */
/* ================================================================== */

class Binsearch_Test:public testing::Test
{
protected:
	void SetUp(){};
	void TearDown(){};
};

TEST_F(Binsearch_Test,Common1)
{
	int a[] = {1,2,3,5,6};
	int len = 5;
	int pos = bin_search(a,len,4);
	EXPECT_EQ(-1, pos);
}

TEST_F(Binsearch_Test,Common2)
{
	int a[] = {1,3,5,6,7,8};
	int len = 6;
	int pos = bin_search(a,len,6);
	EXPECT_EQ(3, pos);
}

TEST_F(Binsearch_Test,Common3)
{
	int a[] = {-3,0,1,6,9,11,13,17,18};
	int len = 9;
	int pos = bin_search(a,len,18);
	EXPECT_EQ(8, pos);
}

TEST_F(Binsearch_Test,Boundary1)
{
	int len = 0;
	int pos = bin_search(NULL,len,18);
	EXPECT_EQ(-1, pos);
}

TEST_F(Binsearch_Test,Boundary2)
{
	int a[] = {33};
	int len = 1;
	int pos = bin_search(a,len,33);
	EXPECT_EQ(0, pos);
}

TEST_F(Binsearch_Test,Boundary3)
{
	int a[] = {-1};
	int len = 1;
	int pos = bin_search(a,len,2);
	EXPECT_EQ(-1, pos);
}

TEST_F(Binsearch_Test,Boundary4)
{
	int a[] = {2,4};
	int len = 2;
	int pos = bin_search(a,len,2);
	EXPECT_EQ(0, pos);
}

TEST_F(Binsearch_Test,Boundary5)
{
	int a[] = {2,4};
	int len = 2;
	int pos = bin_search(a,len,5);
	EXPECT_EQ(-1, pos);
}

int main(int argc,char** argv)
{
	testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();

	printf("success\n");
}