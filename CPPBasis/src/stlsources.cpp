#include <time.h>

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <bitset>
#include <iterator>

using namespace std;

void placementNewTest()
{
    char *a = (char*)malloc(sizeof(char) * 10);
    memset(a,10,'\0');
    int b = 1000;
    new((void*) a) int(b);
   
    cout<<*(char* )a<<endl;
    //((int *)a)[0] = 1;
    //((int *)a)[1] = 2;

    //copy(a,a+2,ostream_iterator<int>(cout,","));
    //cout<<endl;
}

int main(int argc,char** argv)
{
    placementNewTest();
    printf("success!\n");
}
