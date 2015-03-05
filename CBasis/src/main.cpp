#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef int (*CompareFunc)(const void * a, const void * b);
int compareints (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void qsortTest()
{
	int values[] = {4,2,546,6,11,33};
	CompareFunc func = compareints;
	qsort(values, 6, sizeof(int),func);
	for(int x = 0; x < 6; x++) 
		printf("%d\n", values[x]); 
}

void bsearchTest()
{
	int values[] = {4,2,546,6,11,33};
	CompareFunc func = compareints;
	qsort(values, 6, sizeof(int),func);

	int* pItem;
	int key = 33;
	pItem = (int*) bsearch (&key, values, 6, sizeof (int), compareints);
	if (pItem!=NULL)
		printf ("%d is in the array.\n",*pItem);
	else
		printf ("%d is not in the array.\n",key);
}

void atoiTest()
{
	char a[256] = "";
	int num = atoi(NULL);
	printf("%d\n",num);
}

void ctypeTest()
{
	char a = 'Z';
	printf("%d\n",isalnum(a));
}

void mathTest()
{
	printf("%lf\n",fmod(double(62.2),double(3.3)));
	printf("%lf\n",ceil(double(62.3)));
	printf("%lf\n",floor(double(62.6)));
}

void absTest()
{
	int n = abs(11);
	float s = abs(22.22);
	printf("%d,%f\n",n,s);
	printf("%d\n",RAND_MAX);
}

void memmoveTest()
{
	char str[] = "memmove can be very useful......";
    memmove(str+20,str+15,11);
	printf("%s\n",str);
}

int main(int argc,char** argv)
{
	//ctypeTest();
	//mathTest();
	//atoiTest();
	//qsortTest();
	//bsearchTest();
	//absTest();
	memmoveTest();

	printf("success!\n");
}