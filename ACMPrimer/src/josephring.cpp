#include <stdio.h>
#include <string>
#include <stdlib.h>

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

/* ================================================================== */
/*            Joseph Circle Problem - circle list solution            */
/* ================================================================== */

class CircleList
{
public:
    CircleList(const list<int>& inlist){
        list_ = inlist;
        cur_ = list_.begin();
    }
    virtual ~CircleList(){}
    
    void movenext(int step){
        if(empty()) return;

        while(step-- > 0){
            ++ cur_;
            if(cur_ == list_.end())
                cur_ = list_.begin();
        }
    }

    void removecur(){
        cur_ = list_.erase(cur_) ;
        if(cur_ == list_.end())
            cur_ = list_.begin();
    }

    inline bool empty(){ return list_.empty(); }

    inline size_t size(){ return list_.size(); }
    
    inline list<int>::const_iterator cur(){ return cur_; }
    
private:
    list<int> list_; 
    list<int>::iterator cur_;
};

int JosephCircle(int a[],int len,int k,int m)
{
    if(a == NULL || len == 0)
        return -1;
    if(k < 0 || m <= 0)
        return -1;

    list<int> src_list;
    copy(a,a+len,back_inserter(src_list));

    CircleList clist(src_list);

    clist.movenext(k);
    while(clist.size() > 1)
    {
        clist.movenext(m-1);

        cout << "remove "<< *(clist.cur())<< endl;
        clist.removecur();
    }
    return *(clist.cur());
}

/* ================================================================== */
/*        Joseph Circle Problem - math solution 1 O(N2)               */
/* ================================================================== */

int JosephCircleMath(int a[],int len,int k,int m)
{
    if(a == NULL || len == 0)
        return -1;
    if(k < 0 || m <= 0)
        return -1;
    if(len == 1)
        return a[0];

    for(int i = 0;i < len;i ++)
    {
        int nextpos = i - k;
        int round = len;
        while(round > 1)
        {
            nextpos = ((nextpos-m)+round)%round;
            if(nextpos == round - 1)
                break;
            round --;
        }
        if(nextpos == 0)
            return a[i];
    }

    return -1;
}

/* ================================================================== */
/*         Joseph Circle Problem - math solution 2 O(logN)            */
/* ================================================================== */

int JosephCircleMath2(int a[],int len,int k,int m)
{
    if(a == NULL || len == 0)
        return -1;
    if(k < 0 || m <= 0)
        return -1;
    if(len == 1)
        return a[0];

    int pos = 0;
    for(int i = 2;i < len;i ++)
    {
        pos = (pos + m)%i;
    }
    pos = (pos + m + k)%len;

    return a[pos];
}

/* ================================================================== */
/*                           Dev test                                 */
/* ================================================================== */

void DevTest()
{
    int a0[] = {0,1,2,3};
    cout<<JosephCircle(a0,4,0,2)<<endl;
    cout<<JosephCircleMath(a0,4,0,2)<<endl;
    cout<<JosephCircleMath2(a0,4,0,2)<<endl;
    cout<<endl;

    int a1[] = {0,1,2,3,4};
    cout<<JosephCircle(a1,5,0,2)<<endl;
    cout<<JosephCircleMath(a1,5,0,2)<<endl;
    cout<<JosephCircleMath2(a1,5,0,2)<<endl;
    cout<<endl;

    int a2[] = {1,2,3,4,5,6,7,8,9};
    cout<<JosephCircle(a2,9,4,3)<<endl;
    cout<<JosephCircleMath(a2,9,4,3)<<endl;
    cout<<JosephCircleMath2(a2,9,4,3)<<endl;
    cout<<endl;

    int a3[] = {1};
    cout<<JosephCircle(a3,1,3,2)<<endl;
    cout<<JosephCircleMath(a3,1,3,2)<<endl;
    cout<<JosephCircleMath2(a3,1,3,2)<<endl;
    cout<<endl;

    int a4[] = {1};
    cout<<JosephCircle(NULL,1,3,2)<<endl;
    cout<<JosephCircleMath(NULL,1,3,2)<<endl;
    cout<<JosephCircleMath2(NULL,1,3,2)<<endl;
    cout<<endl;

    int a5[] = {1,2};
    cout<<JosephCircle(a5,2,1,10)<<endl;
    cout<<JosephCircleMath(a5,2,1,10)<<endl;
    cout<<JosephCircleMath2(a5,2,1,10)<<endl;
    cout<<endl;
}

int main(int argc,char** argv)
{
    DevTest();
    
    printf("success!\n");
}
