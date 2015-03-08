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

// �麯����鿴
void BaseTest(){
    Base b;
  
    OOModelFunc pFun = NULL;
  
    cout << "�麯�����ַ��" << (int*)(&b) << endl;
    cout << "�麯���� �� ��һ��������ַ��" << (int*)*(int*)(&b) << endl;
    cout << "�麯���� �� �ڶ���������ַ��" << (int*)*(int*)(&b)+1 << endl;
    cout << "�麯���� �� ������������ַ��" << (int*)*(int*)(&b)+2 << endl;
  
    // Invoke the first virtual function 
    pFun = (OOModelFunc)*((int*)*(int*)(&b));
    pFun();

    pFun = (OOModelFunc)*((int*)*(int*)(&b)+1);
    pFun();

    pFun = (OOModelFunc)*((int*)*(int*)(&b)+2);
    pFun();
}

// һ��̳�
void DeriveTest(){
    Base* dp = new Derive();
    OOModelFunc pFun = NULL;
    for(int i = 0; i < 5;i++){
        cout << "�麯���� �� ��"<<i+1<<"һ��������ַ��" << (int*)*(int*)(dp)+i << endl;

        pFun = (OOModelFunc)*((int*)*(int*)(dp)+i);
        pFun();
    }
}

// ���ؼ̳�
void MultiDeriveTest(){
    OOModelFunc pFun = NULL;
    DeriveM d;
    Base1* b1 = &d;
    Base2* b2 = &d;
    Base3* b3 = &d;
    cout << "base1�麯�����ַ��" << (int*)(&d) << endl;
    cout << "base2�麯�����ַ��" << (int*)(&d) + 1 << endl;
    cout << "base3�麯�����ַ��" << (int*)(&d) + 2 << endl;

    for(int i = 0; i < 3;i++){
        cout << "base1�麯���� �� ��"<<i+1<<"һ��������ַ��" << (int*)*(int*)(&d)+i << endl;
        pFun = (OOModelFunc)*((int*)*(int*)(&d)+i);
        pFun();
    }

    for(int i = 0; i < 3;i++){
        cout << "base2�麯���� �� ��"<<i+1<<"һ��������ַ��" << (int*)*((int*)(&d)+1)+i << endl;
        pFun = (OOModelFunc)*((int*)*(int*)(&d)+i);
        pFun();
    }

    for(int i = 0; i < 3;i++){
        cout << "base3�麯���� �� ��"<<i+1<<"һ��������ַ��" << (int*)*((int*)(&d)+2)+i << endl;
        pFun = (OOModelFunc)*((int*)*(int*)(&d)+i);
        pFun();
    }

    cout << "DeriveM��Ĵ�С��" << sizeof(d) << endl;
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
    cout << "����b����ʼ�ڴ��ַ��" << &b << endl;
    cout << endl;
    
    // RTTI��Ϣ
    cout << "��׼type_info��Ϣ��" << typeid(b).name() << endl;
    cout << "type_info��Ϣ��ַ��" << ((int*)*(int*)(&b) - 1) << endl;
    RTTICompleteObjectLocator str=
        *((RTTICompleteObjectLocator*)*((int*)*(int*)(&b) - 1));
    string classname(str.pTypeDescriptor->name);
    classname = classname.substr(4,classname.find("@@")-4);
    cout << classname <<endl;
    cout << endl;
    
    // �麯��
    cout << "�麯�����ַ��\t\t\t" << (int*)(&b) << endl;
    cout << "�麯���� �� ��1��������ַ��\t" << (int*)*(int*)(&b) << "\t������������ַ��" << (int*)*((int*)*(int*)(&b)) << endl;
    cout << "�麯���� �� ��2��������ַ��\t" << ((int*)*(int*)(&b) + 1) << "\t\n";
    typedef void(*Fun)(void);
    Fun pFun = (Fun)*(((int*)*(int*)(&b)) + 1);
    pFun(); // ���ֵ��÷�ʽ���Ҳ�����Ա����
    b.print();
    cout << endl;

    // ���Ǿ�̬�����ݳ�Ա
    cout << "�Ʋ����ݳ�ԱiBase��ַ��\t\t" << ((int*)(&b) +1) << "\tͨ����ַȡֵiBase��ֵ��" << *((int*)(&b) +1) << endl;
    cout << "Base::getIBase(): " << b.getIBase() << endl;
    
    // ��̬����
    b.instanceCount();
    cout << "��̬����instanceCount��ַ�� " << b.instanceCount << endl;

    cout << "WBase��Ĵ�С��" << sizeof(WBase) << endl;
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
