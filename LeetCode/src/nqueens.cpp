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
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string>> res;
        if(n <= 0) return res;

        // solve
        vector<vector<int>> iRes;
        vector<int> path;
        NQueensRecursively(n,0,path,iRes);

        // wrap
        string defaultline = "";
        for(int i = 0;i < n; i++)
            defaultline += '.';
        for(int i = 0;i < iRes.size();i ++){
            vector<string> newSolve;
            // convert solve
            for(int j = 0;j < iRes[i].size();j ++){
                string newline = defaultline;
                newline[iRes[i][j]] = 'Q';
                newSolve.push_back(newline);
            }
            res.push_back(newSolve);
        }
        return res;
    }
private:
    bool hasConflict(int newnum,const vector<int> &path){
        int newrow = path.size();
        for(int i = 0;i < path.size();i ++){
            if(path[i] == newnum || abs(path[i]-newnum) == abs(i-newrow))
                return true;
        }
        return false;
    }
    void NQueensRecursively(const int n,int row,vector<int> &path, vector<vector<int>> &res){
        for(int i = 0;i < n;i ++){
            if(!hasConflict(i,path)){
                path.push_back(i);
                if(row == n-1)
                    res.push_back(path);
                else
                    NQueensRecursively(n,row+1,path,res);
                path.pop_back();
            }
        }
    }
};

int main(int argc,char** argv)
{
    Solution so;

    int n = 0;
    vector<vector<string> >  res = so.solveNQueens(n);

    printf("Num of %d Queens Solves:%d\n",n,res.size());
    for(int i = 0;i < res.size(); i ++)
    {
        printf("Solve %d:\n",i);
        for(int j = 0;j < res[i].size(); j ++)
        {
            printf("%s:\n",res[i][j].c_str());
        }
        printf("\n");
    }


    printf("success!\n");
}
