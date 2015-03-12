#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class xstring{
public:
    xstring(){
        data_ = new char[1];
        data_[0] = '\n';
    };

    xstring(const char* str){
        data_ = new char[strlen(str)+1];
        strcpy(data_,str);
    };

    xstring(const xstring& str){
        data_ = new char[str.size()+1];
        strcpy(data_,str.c_str());
    };

    ~xstring(){
        delete data_;
    }

    xstring& operator=(xstring str){
        swap(str);
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& os,const xstring& str);

    const char *c_str() const{
        return data_;
    }

    size_t size() const{
        return strlen(data_);
    }

    void swap(xstring& rhs)
    {
        std::swap(data_, rhs.data_);
    }

private:
    char *data_;
};

std::ostream& operator<< (std::ostream& os,const xstring& str)
{
    os<<str.c_str();
    return os;
}

void foo(xstring x)
{
}
 
void bar(const xstring& x)
{
}
 
xstring baz()
{
    xstring ret("world");
    return ret;
}
 
int main()
{
    xstring s0;
    xstring s1("hello");
    xstring s2(s0);
    xstring s3 = s1;
    s2 = s1;
 
    cout<<s2<<endl;
    cout<<s3<<endl;

    foo(s1);
    bar(s1);
    foo("temporary");
    bar("temporary");
    xstring s4 = baz();
 
    std::vector<xstring> svec;
    svec.push_back(s0);
    svec.push_back(s1);
    svec.push_back(baz());
    svec.push_back("good job");

     cout<<svec[2]<<endl;
}