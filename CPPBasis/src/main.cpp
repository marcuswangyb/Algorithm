#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <list>
#include <iomanip>
#include <sstream>
#include <bitset>

using namespace std;

#define ARRAYSIZE 100

void iterdemo()
{
	int iarray[ARRAYSIZE] = {1,23,4,54,32,6,8,2,6};
	int* ip = find(iarray, iarray + ARRAYSIZE, 4);
	if (ip == iarray + ARRAYSIZE)
		cout << "50 not found in array" << endl;
	else
		cout << *ip << " found in array" << endl;
}

void exceptionTest()
{
	vector<int> a(10);

	try{
		a.at(12) = 3;
	}catch(const std::out_of_range& oor){
		std::cerr<<"range error\n";
	}
}

void pairTest()
{
	pair<int,float> ap(2,2.3);
}

void swapTest()
{
	int a = 10;
	int b = 3;
	std::swap(a,b);
	cout<<a<<","<<b<<endl;
}

void iostreamTest()
{
    int a = 123;
    float b = 24.2;
    stringstream ss;
    cout<<a<<std::setw(4)<<setfill('0')<<endl;
    cout<<std::showpos<<b<<endl;
    cout<<std::hex<<a<<endl;
    cout<<std::oct<<a<<endl;
    cout<<std::showbase<<a<<endl;
}

void sstreamTest()
{
    stringstream ss;
    ss<<"dec:"<<15<<" "<<hex<<"hex:"<<15<<endl;
    cout<<ss.str()<<endl;
    ss.str("abc");

    bitset<15> b(42348);
    ss<<"float:"<<4.57<<" "<<"bitset:"<<b<<endl;
    cout<<ss.str();
    ss.seekp(0);
    ss<<"oct:"<<oct<<15;
    cout<<ss.str()<<endl;

    ss.str("aaa");
    cout<<ss.str()<<endl;
}

struct JDBook
{
    string bookName;
    vector<string> authors;
    int pageNum;
    float price;
};

std::ostream& operator<< (std::ostream& os,const JDBook& book)
{
    os<<book.bookName<<",";
    os<<"[";
    for(auto it = book.authors.begin();it != book.authors.end();it ++)
    {
        if(it != book.authors.begin())
            os<<",";
        os<<*it;
    }
    os<<"],";
    os<<book.pageNum<<","<<book.price;

    return os;
}

class TBBook
{
public:
    TBBook(string book_name,const vector<string> authors,int page_num,int price){
        book_name_ = book_name;
        authors_ = authors;
        page_num_ = page_num;
        price_ = price;
    }
    friend std::ostream& operator<< (std::ostream& os,const TBBook& book);
private:
    string book_name_;
    vector<string> authors_;
    int page_num_;
    float price_;
};

std::ostream& operator<< (std::ostream& os,const TBBook& book)
{
    os<<book.book_name_<<",";
    os<<"[";
    for(auto it = book.authors_.begin();it != book.authors_.end();it ++)
    {
        if(it != book.authors_.begin())
            os<<",";
        os<<*it;
    }
    os<<"],";
    os<<book.page_num_<<","<<book.price_;

    return os;
}

void OperatorTest()
{
    // 结构体重载
    JDBook b;
    b.bookName = "no one tell the truth";
    b.authors.push_back("marcus");
    b.authors.push_back("sam");
    b.authors.push_back("mary");
    b.pageNum = 432;
    b.price = 23.0;

    cout<<b<<endl;

    // 类友元重载
    vector<string> authors;
    authors.push_back("mayun");
    authors.push_back("mahuateng");
    authors.push_back("gates");

    TBBook t("how to become Mayun",authors,100,14.3);
    cout<<t<<endl;
}


class AMBOOK
{
public:
    AMBOOK(string book_name,const vector<string> authors,int page_num,int price){
        book_name_ = book_name;
        authors_ = authors;
        page_num_ = page_num;
        price_ = price;
    }
    string GetBookName() { book_name_ += "2"; return book_name_; }
private:
    string book_name_;
    vector<string> authors_;
    int page_num_;
    float price_;
};

// const function test
void ConstFunctionTest()
{
    vector<string> authors;
    authors.push_back("mayun");
    authors.push_back("mahuateng");
    authors.push_back("gates");

    AMBOOK a("how to become Mayun",authors,100,14.3);
    cout<<a.GetBookName()<<endl;
}

int main(int argc,char** argv)
{
	//ctypeTest()
	//iterdemo();
    //exceptionTest();
	//pairTest();
    //iostreamTest();
    //OperatorTest();
    ConstFunctionTest();

	printf("success!\n");
}