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

void setTest()
{
	set<int> sa;
	sa.insert(23);
	sa.insert(1);
	sa.insert(42);
	sa.insert(3);
	sa.insert(42);
	 
	for(set<int>::iterator it = sa.begin();it != sa.end(); it++)
	{
		cout<<*it<<",";
	}
	cout<<endl;

	multiset<int> sa2;
	sa2.insert(23);
	sa2.insert(1);
	sa2.insert(42);
	sa2.insert(3);
	sa2.insert(42);

	for(multiset<int>::iterator it = sa2.begin();it != sa2.end(); it++)
	{
		cout<<*it<<",";
	}
	cout<<endl;
}

void bitsetTest()
{
	enum Color{red, yellow, green, blue, white, black, numColors};

	bitset<numColors> usedColors;
	usedColors.set(red);
	usedColors.set(blue);
	cout << "bitfield of used colors:" << usedColors << endl;
	cout << "number of used colors:" << usedColors.count() << endl;
	cout << "bitfield of unused colors:" << ~usedColors << endl;


	cout << "267 as binary short:" << bitset<numeric_limits<unsigned short>::digits>(267) << endl;
	cout << "267 as binary long:" << bitset<numeric_limits<unsigned long>::digits>(267) << endl;
	cout << "10,000,000 with 24 bis:" << bitset<24>(10000000) << endl;
	cout << "1001011001:" << bitset<100>(string("1001011001")).to_ulong() << endl;
}

void lambdaTest()
{
    srand(time(0));
    vector<int> v;
    for(int i = 0;i < 10;i ++)
    {
        v.push_back(i + rand()%100);
    }

    // lambda print
    bool firstFlag = true;
    for_each(v.begin(),v.end(),
        [&firstFlag](int val){
            if(firstFlag)
                firstFlag = false;
            else
                cout<<",";
            cout<<val;
        });
    cout<<endl;

    // lambda threshold and print
    firstFlag = true;
    int th = 55;
    for_each(v.begin(),v.end(),
        [th,&firstFlag](int val){
            if(val > th){
                if(firstFlag)
                    firstFlag = false;
                else
                    cout<<",";
                cout<<val;
            }
        });
    cout<<endl;

    // stream adapter print
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));
    cout<<endl;

    // normal print
    for(auto it = v.begin();it != v.end();++it)
    {
        if(it != v.begin()) cout<<",";
        cout<<*it;
    }
    cout<<endl;
}

void inserterTest()
{
    srand(time(0));
    vector<int> v;
    for(int i = 0;i < 10;i ++)
        v.push_back(i + rand()%100);
    
    list<int> col1;
    copy(v.begin(),v.end(),front_inserter(col1));

    bool firstFlag = true;
    for_each(v.begin(),v.end(),
        [&firstFlag](int val){
            if(firstFlag)
                firstFlag = false;
            else
                cout<<",";
            cout<<val;
        });
    cout<<endl;

    firstFlag = true;
    for_each(col1.begin(),col1.end(),
        [&firstFlag](int val){
            if(firstFlag)
                firstFlag = false;
            else
                cout<<",";
            cout<<val;
        });
    cout<<endl;
}

void streamItTest()
{
    vector<string> coll;

    copy(istream_iterator<string>(cin),istream_iterator<string>(),back_inserter(coll));

    sort(coll.begin(),coll.end());

    copy(coll.begin(),coll.end(),ostream_iterator<string>(cout,","));
}

void countifTest()
{
    srand(time(0));
    vector<int> v;
    for(int i = 0;i < 5;i ++)
        v.push_back(i + rand()%100);

    int num = count_if(v.begin(),v.end(),[](int item)->bool{ return item%2 == 0; });

    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));
    cout<<endl;

    cout<<"num:"<<num<<endl;
}

void heapTest()
{
    int ia[9] = {0,1,2,3,4,8,9,3,5};
    vector<int> v(ia,ia + 9);

    make_heap(v.begin(),v.end());
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));
    cout<<endl;
    cout<<"initial max heap:"<<v.front()<<endl;

    v.push_back(7);
    push_heap(v.begin(),v.end());
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));
    cout<<endl;

    pop_heap(v.begin(),v.end());
    v.pop_back();
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));
    cout<<endl;
    
    sort_heap(v.begin(),v.end());
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));
    cout<<endl;
}

int main(int argc,char** argv)
{
    //bitsetTest();
	//setTest();
    //lambdaTest();
    //inserterTest();
    //streamItTest();

    //bitsetTest();
    heapTest();
	printf("success!\n");
}