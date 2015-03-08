#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "gtest/gtest.h"

using namespace std;

int partition(int a[],int start,int end)
{
    int pivot  = a[start];
    int j = end + 1;
    int i;
    int temp;
    for(i = end;i > start;i --)
    {
        if(a[i] > pivot)
        {
            j --;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    j --;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;

    return j;
}

void quicksort_(int a[],int start,int end)
{
    if(start < end)
    {
        int mid = partition(a,start,end);
        quicksort_(a,start,mid-1);
        quicksort_(a,mid+1,end);
    }
}

inline void quicksort(int a[],int len)
{
    quicksort_(a,0,len-1);
}

void printArray(int a[],int len)
{
    for(int i = 0;i < len;i ++)
    {
        printf("%d",a[i]);
        if(i != len-1)
            printf(",");
    }
    printf("%\n");
}

string printArrayToString(int a[],int len)
{
    string res = "";
    for(int i = 0;i < len; i ++)
    {
        char tmp[64];
        if(i != len - 1)
            sprintf(tmp,"%d,",a[i]);
        else
            sprintf(tmp,"%d",a[i]);
        res += tmp;
    }
    return res;
}

/* ================================================================== */
/*                           Unit test                                */
/* ================================================================== */

class Quicksort_Test:public testing::Test
{
protected:
    void SetUp(){};
    void TearDown(){};
};

TEST_F(Quicksort_Test,Common1)
{
    int a[] = {4,5,1,6,2};
    int len = 5;
    quicksort(a,len);
    EXPECT_STREQ("1,2,4,5,6", printArrayToString(a,len).c_str());
}

TEST_F(Quicksort_Test,Common2)
{
    int a[] = {9,8,7,6,5,4,3,2,1};
    int len = 9;
    quicksort(a,len);
    EXPECT_STREQ("1,2,3,4,5,6,7,8,9", printArrayToString(a,len).c_str());
}

TEST_F(Quicksort_Test,Common3)
{
    int a[] = {-3,5,221,-89,0};
    int len = 5;
    quicksort(a,len);
    EXPECT_STREQ("-89,-3,0,5,221", printArrayToString(a,len).c_str());
}

TEST_F(Quicksort_Test,Boundary1)
{
    int a[] = {4};
    int len = 1;
    quicksort(a,len);
    EXPECT_STREQ("4", printArrayToString(a,len).c_str());
}

TEST_F(Quicksort_Test,Boundary2)
{
    int a[] = {33,12};
    int len = 2;
    quicksort(a,len);
    EXPECT_STREQ("12,33", printArrayToString(a,len).c_str());
}

TEST_F(Quicksort_Test,Boundary3)
{
    int a[] = {-1};
    int len = 1;
    quicksort(a,len);
    EXPECT_STREQ("-1", printArrayToString(a,len).c_str());
}

TEST_F(Quicksort_Test,Boundary4)
{
    int a[] = {4,2,4,2,4,2};
    int len = 6;
    quicksort(a,len);
    EXPECT_STREQ("2,2,2,4,4,4", printArrayToString(a,len).c_str());
}

int main(int argc,char** argv)
{
    testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();

    printf("success\n");
}