#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stack_;
        bool res = true;
        int l = s.length();
        for(int i = 0;i < l;i ++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{')
                stack_.push(s[i]);
            else if(s[i] == ')' || s[i] == ']' || s[i] == '}'){
                if(stack_.empty())
                {
                    res = false;
                    break;
                }
                char top = stack_.top(); 
                stack_.pop();
                if((top == '(' && s[i] == ')') ||
                    (top == '[' && s[i] == ']') || 
                    (top == '{' && s[i] == '}'))
                    ;
                else{
                    res = false;
                    break;
                }
            }
            else{
                res = false;
                break;
            }
        }

        if(!stack_.empty())
            res = false;
        return res;
    }
};

int main(int argc,char** argv)
{
    Solution so;

    vector<string> cases;
    cases.push_back("");
    cases.push_back(")");
    cases.push_back("[]}");
    cases.push_back("asd[sdf]");
    cases.push_back("[]{}()");
    cases.push_back("[[[(())]]]");
    cases.push_back("[[[(({}))]]]");
    cases.push_back("[[[(}{)]]]");
    cases.push_back("[{]}");
    cases.push_back("(()[)]");
    
    for(int i = 0;i < cases.size(); i ++)
    {
        printf("case \"%s\":%d\n",cases[i].c_str(),so.isValid(cases[i]));
    }


    printf("success!\n");
}
