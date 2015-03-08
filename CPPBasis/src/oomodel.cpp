#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <list>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <typeinfo>

#include <Windows.h>

using namespace std;

typedef void(*OOModelFunc)(void);

/* ================================================================== */
/*                      c struct model                                */
/* ================================================================== */

struct tagPhone  
{  
    char   A;  
    int    B;  
    short  C; 
    long   D;
}Phone;

struct tagPhone2  
{  
    int    B; 
    long   D;
    char   A;  
    int    C; 
}Phone2;

struct tagPhone3
{
    double X;
    char A;
    tagPhone2 P2;
}Phone3;

void StructSizeTest()
{
    cout<<sizeof(Phone)<<endl;
    cout<<sizeof(Phone2)<<endl;
    cout<<sizeof(Phone3)<<endl;

    tagPhone3 tp3;
    tp3.A = 'X';
    tp3.X = 12.3;
    tp3.P2.A = 'Y';
    tp3.P2.B = 4;
    tp3.P2.C = 5;
    tp3.P2.D = 12345;
    tagPhone3 *addr = &tp3;
    cout<<sizeof(Phone3)<<endl;
}


/* ================================================================== */
/*               Chen Hao's blog - virtual function                   */
/* ================================================================== */

class Base {
public:
    virtual void init() { cout << "Base::init" << endl; }
    virtual void process() { cout << "Base::process" << endl; }
    virtual void destroy() { cout << "Base::destroy" << endl; }
};

class Derive:public Base {
public:
    virtual void init() { cout << "Derive::init" << endl; }
    virtual void process2() { cout << "Derive::process" << endl; }
    virtual void destroy2() { cout << "Derive::destroy" << endl; }
};

class Base1 {
public:
    virtual void init() { cout << "Base1::init" << endl; }
    virtual void process() { cout << "Base1::process" << endl; }
    virtual void destroy() { cout << "Base1::destroy" << endl; }
};
  
class Base2 {
public:
    virtual void init() { cout << "Base2::init" << endl; }
    virtual void process() { cout << "Base2::process" << endl; }
    virtual void destroy() { cout << "Base2::destroy" << endl; }
};
  
class Base3 {
public:
    virtual void init() { cout << "Base3::init" << endl; }
    virtual void process() { cout << "Base3::process" << endl; }
    virtual void destroy() { cout << "Base3::destroy" << endl; }
};

class DeriveM:public Base1,public Base2, public Base3 {
public:
    virtual void init() { cout << "DeriveM::init" << endl; }
    virtual void process2() { cout << "DeriveM::process" << endl; }
    virtual void destroy2() { cout << "DeriveM::destroy" << endl; }
};

// 虚函数表查看
void BaseTest(){
    Base b;
  
    OOModelFunc pFun = NULL;
  
    cout << "虚函数表地址：" << (int*)(&b) << endl;
    cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
    cout << "虚函数表 — 第二个函数地址：" << (int*)*(int*)(&b)+1 << endl;
    cout << "虚函数表 — 第三个函数地址：" << (int*)*(int*)(&b)+2 << endl;
  
    // Invoke the first virtual function 
    pFun = (OOModelFunc)*((int*)*(int*)(&b));
    pFun();

    pFun = (OOModelFunc)*((int*)*(int*)(&b)+1);
    pFun();

    pFun = (OOModelFunc)*((int*)*(int*)(&b)+2);
    pFun();
}

// 一般继承
void DeriveTest(){
    Base* dp = new Derive();
    OOModelFunc pFun = NULL;
    for(int i = 0; i < 5;i++){
        cout << "虚函数表 — 第"<<i+1<<"一个函数地址：" << (int*)*(int*)(dp)+i << endl;

        pFun = (OOModelFunc)*((int*)*(int*)(dp)+i);
        pFun();
    }
}

// 多重继承
void MultiDeriveTest(){
    OOModelFunc pFun = NULL;
    DeriveM d;
    Base1* b1 = &d;
    Base2* b2 = &d;
    Base3* b3 = &d;
    cout << "base1虚函数表地址：" << (int*)(&d) << endl;
    cout << "base2虚函数表地址：" << (int*)(&d) + 1 << endl;
    cout << "base3虚函数表地址：" << (int*)(&d) + 2 << endl;

    for(int i = 0; i < 3;i++){
        cout << "base1虚函数表 — 第"<<i+1<<"一个函数地址：" << (int*)*(int*)(&d)+i << endl;
        pFun = (OOModelFunc)*((int*)*(int*)(&d)+i);
        pFun();
    }

    for(int i = 0; i < 3;i++){
        cout << "base2虚函数表 — 第"<<i+1<<"一个函数地址：" << (int*)*((int*)(&d)+1)+i << endl;
        pFun = (OOModelFunc)*((int*)*(int*)(&d)+i);
        pFun();
    }

    for(int i = 0; i < 3;i++){
        cout << "base3虚函数表 — 第"<<i+1<<"一个函数地址：" << (int*)*((int*)(&d)+2)+i << endl;
        pFun = (OOModelFunc)*((int*)*(int*)(&d)+i);
        pFun();
    }

    cout << "DeriveM类的大小：" << sizeof(d) << endl;
}

/* ================================================================== */
/*                Wu Qin(Tyler)'s blog - object model                 */
/* ================================================================== */

class WBase
{
public:
    WBase(int i){ iBase = i;cout<<"WBase construct"<<endl; }
    virtual ~WBase(void){ cout<<"WBase destroyed"<<endl; }
 
    int getIBase() const{ cout<<"getIBase()"<<endl; return iBase; }
    static int instanceCount(){ return count; }
    virtual void print() const{ cout<<"iBase is :"<<iBase<<endl; }
 
protected:
 
    int iBase;
    static int count;
};
int WBase::count = 0;

struct TypeDescriptor  
{  
    DWORD ptrToVTable;  
    DWORD spare;  
    char name[8];  
};  
  
struct PMD  
{  
    int mdisp;  //member displacement  
    int pdisp;  //vbtable displacement  
    int vdisp;  //displacement inside vbtable  
};  
  
struct RTTIBaseClassDescriptor  
{  
    struct TypeDescriptor* pTypeDescriptor; //type descriptor of the class  
    DWORD numContainedBases; //number of nested classes following in the Base Class Array  
    struct PMD where;        //pointer-to-member displacement info  
    DWORD attributes;        //flags, usually 0  
};  
  
struct RTTIClassHierarchyDescriptor  
{  
    DWORD signature;      //always zero?  
    DWORD attributes;     //bit 0 set = multiple inheritance, bit 1 set = virtual inheritance  
    DWORD numBaseClasses; //number of classes in pBaseClassArray  
    struct RTTIBaseClassArray* pBaseClassArray;  
}; 

struct RTTICompleteObjectLocator  
{     
    DWORD signature; //always zero ?  
    DWORD offset;    //offset of this vtable in the complete class  
    DWORD cdOffset;  //constructor displacement offset  
    struct TypeDescriptor* pTypeDescriptor; //TypeDescriptor of the complete class  
    struct RTTIClassHierarchyDescriptor* pClassDescriptor; //describes inheritance hierarchy  
};

void TestBaseModel()
{
    WBase b(1000);
    cout << "对象b的起始内存地址：" << &b << endl;
    cout << endl;
    
    // RTTI信息
    cout << "标准type_info信息：" << typeid(b).name() << endl;
    cout << "type_info信息地址：" << ((int*)*(int*)(&b) - 1) << endl;
    RTTICompleteObjectLocator str=
        *((RTTICompleteObjectLocator*)*((int*)*(int*)(&b) - 1));
    string classname(str.pTypeDescriptor->name);
    classname = classname.substr(4,classname.find("@@")-4);
    cout << classname <<endl;
    cout << endl;
    
    // 虚函数
    cout << "虚函数表地址：\t\t\t" << (int*)(&b) << endl;
    cout << "虚函数表 — 第1个函数地址：\t" << (int*)*(int*)(&b) << "\t即析构函数地址：" << (int*)*((int*)*(int*)(&b)) << endl;
    cout << "虚函数表 — 第2个函数地址：\t" << ((int*)*(int*)(&b) + 1) << "\t\n";
    typedef void(*Fun)(void);
    Fun pFun = (Fun)*(((int*)*(int*)(&b)) + 1);
    pFun(); // 此种调用方式会找不到成员变量
    b.print();
    cout << endl;

    // （非静态）数据成员
    cout << "推测数据成员iBase地址：\t\t" << ((int*)(&b) +1) << "\t通过地址取值iBase的值：" << *((int*)(&b) +1) << endl;
    cout << "Base::getIBase(): " << b.getIBase() << endl;
    
    // 静态函数
    b.instanceCount();
    cout << "静态函数instanceCount地址： " << b.instanceCount << endl;

    cout << "WBase类的大小：" << sizeof(WBase) << endl;
}

class Empty
{
public:
    Empty(){}
    ~Empty(){}
};

void ClassSizeTest()
{
    Empty p;
    cout<<sizeof(p)<<endl;
    cout<<sizeof(NULL)<<endl;
}

    
int main(int argc,char** argv)
{
    //StructSizeTest();
    
    //MultiDeriveTest();
    //DeriveTest();
    
    //TestBaseModel();
    ClassSizeTest();
}
