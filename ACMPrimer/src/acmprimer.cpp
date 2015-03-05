#include <stdio.h>
#include <string>
#include <stdlib.h>

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


int main(int argc,char** argv)
{
	//ConstTest();
    //PointTest();
	FloatTest();

	printf("success\n");
}