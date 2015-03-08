#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if(n <= 0)
            return "";

        string srcstr = "1";
        while(n -- > 1)
        {
            srcstr = getNextString(srcstr);
        }

        return srcstr;
    }
private:
    string getNextString(string str){
        stringstream ss;
        int precount = 1;
        int i = 0;
        char prenum = str[i];
        for(i = 1;i < str.length(); i++){
            if(str[i] == prenum)
                precount ++;
            else{
                int pren = prenum - '0';
                ss<<precount<<pren;
                precount = 1;
                prenum = str[i];
            }
        }
        int pren = prenum - '0';
        ss<<precount<<pren;
        return ss.str();
    }

    inline int getNumPos(int n,int pos){
        int lower = 1;
        while(pos-- > 1)
            lower *= 10;
        return (n/lower)%10;
    }
};

int main(int argc,char** argv)
{
    Solution so;

    vector<int> cases;
    cases.push_back(0);
    cases.push_back(-1);
    cases.push_back(1);
    cases.push_back(2);
    cases.push_back(3);
    cases.push_back(4);
    cases.push_back(5);
    cases.push_back(6);;
    cases.push_back(7);
    cases.push_back(8);
    cases.push_back(9);
    cases.push_back(100);
    
    for(int i = 0;i < cases.size(); i ++)
    {
        printf("case \"%d\":%s\n",cases[i],so.countAndSay(cases[i]).c_str());
    }


    printf("success!\n");
}
