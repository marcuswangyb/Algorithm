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
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int>> res;
        if(num.size() < 1) return res;
        if(num.size() == 1){
            vector<int> newline;
            newline.push_back(num[0]);
            res.push_back(newline);
            return res;
        }

        int lastOne = num[num.size()-1];
        num.pop_back();
        vector<vector<int>> resMinus = permute(num);
        for(int i = 0;i < resMinus.size();i ++){
            // insert last one for each position
            for(int j = 0; j <= resMinus[i].size();j ++){
                vector<int> newline = resMinus[i];
                newline.insert(newline.begin()+j,lastOne);
                res.push_back(newline);
            }
        }
        return res;
    }
};

int main(int argc,char** argv)
{
    vector<int> num;
    num.push_back(1);
    num.push_back(6);
    num.push_back(3);
    num.push_back(5);
    num.push_back(7);

    Solution so;
    vector<vector<int>>  res = so.permute(num);

    printf("Num of Permutations:%d\n",res.size());
    for(int i = 0;i < res.size(); i ++)
    {
        printf("Permutation %d: ",i);
        for(int j = 0;j < res[i].size(); j ++)
        {
            if(j != 0) cout<<",";
            cout<<res[i][j];
        }
        cout<<endl;
    }
    

    printf("success!\n");
}
