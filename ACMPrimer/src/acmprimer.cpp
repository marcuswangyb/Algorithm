#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>

using namespace std;

void PointConst1(int const * pnum,int *pnum2)
{
    //*num = 6;
    int x = 10;
    pnum = pnum2;
    printf("%d,%d\n",pnum,pnum2);
}

void PointTest()
{
    int num = 0;
    int num2 = 10;
    printf("%d,%d\n",&num,&num2);
    PointConst1(&num,&num2);
    int *p1 = &num;
    int *p2 = &num2;
    p1 = p2;
    printf("%d,%d\n",num,num2);
    printf("%d,%d\n",&num,&num2);
}

void ConstString(const string &name)
{
    //name = "213";
    printf("%s\n",name.c_str());
}

void ConstTest()
{
    string name = "wyb";
    ConstString(name);
}

void FloatTest()
{
    float x = 0.0;
    if(abs(x-0.0) > 1e-6)
        printf("yes\n");
    else
        printf("no\n");
}

inline bool getBit(int num,int i){
    return num&(1<<i);
}

inline int clearBits(int num,int i){
    int mask = (1<<i)-1;
    return mask&num;
}

void BitTest(){
    //for(int i = 8-1;i >= 0;i --)
        cout<<getBit(8,-1)<<" ";
}

int main(int argc,char** argv)
{
    //ConstTest();
    //PointTest();
    //FloatTest();
    BitTest();

    printf("success\n");
}