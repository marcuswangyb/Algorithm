#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string>
#include <iostream>

#include <map>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        if(s.length() == 0 || s.length() == 1 || s == "")
            return true;

        int start = 0;
        int end = s.length() - 1;
        bool res = true;
        while(start < end){
            while(start < end &&!isAlphanumeric(s[start]))
                start ++;
            while(start < end  &&!isAlphanumeric(s[end]))
                end --;
            if(start >= end)
                break;
            if(lowerCase(s[start]) != lowerCase(s[end]))
            {
                res = false;
                break;
            }
            start ++;
            end --;
        }
        return res;
    }
private:
    inline bool isAlphanumeric(char c){
        /*
        if (('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') || 
            ('0' <= c && c <= '9'))
            return true;
        else
            return false;*/
        return isalnum(c);
    }

    inline char lowerCase(char c){
        /*
        if('A' <= c && c <= 'Z')
            return c-'A'+'a';
        else 
            return c;
            */
        return tolower(c);
    }
};

int main(int argc,char** argv)
{
    Solution so;

    vector<string> cases;
    cases.push_back("1234gdf");
    cases.push_back("");
    cases.push_back(",. _n");
    cases.push_back(". (.)");
    cases.push_back("A man, a plan, a canal: Panama");
    cases.push_back("race a car");
    cases.push_back("AdssSDa");
    cases.push_back("AdsKkSDa");
    cases.push_back("2");
    cases.push_back("aA");
    cases.push_back("2A");
    cases.push_back(",. _   () ");
    
    for(int i = 0;i < cases.size(); i ++)
    {
        printf("case \"%s\":%d\n",cases[i].c_str(),so.isPalindrome(cases[i]));
    }


    printf("success!\n");
}
