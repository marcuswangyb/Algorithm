#include <time.h>

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <bitset>
#include <iomanip>

using namespace std;

class RuntimeStringCmp{
public:
    enum cmp_mode{normal, nocase};

private:
    const cmp_mode mode;
    
    static bool nocase_compare(char c1,char c2){
        return toupper(c1) < toupper(c2);
    }

public:
    RuntimeStringCmp(cmp_mode m=normal):mode(m){
    }

    bool operator()(const string& s1,const string& s2) const{
        if(mode == normal){
            return s1 < s2;
        }
        else{
            return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(),
                    nocase_compare);
        }
    }
};

typedef map<string, string, RuntimeStringCmp> StringStringMap;

void fillAndPrint(StringStringMap& coll);

int main(int argc,char** argv)
{
    // normal
    StringStringMap coll;
    fillAndPrint(coll);
    
    // nocase
    RuntimeStringCmp ignorecase(RuntimeStringCmp::nocase);
    StringStringMap coll2(ignorecase);
    fillAndPrint(coll2);
     
    printf("success!\n");
}

void fillAndPrint(StringStringMap& coll)
{
    coll["Deutschlan"] = "Germany";
    coll["Haken"] = "snag";
    coll["Hund"] = "dog";
    coll["gehen"] = "go";
    coll["Bestater"] = "undertaker";
    coll["deutsch"] = "German";

    cout.setf(ios::left, ios::adjustfield);
    for(auto it = coll.begin(); it != coll.end(); ++it)
    {
        cout<<setw(15)<<it->first.c_str()<<" "<<it->second.c_str()<<endl;
    }
    cout<<endl;
}