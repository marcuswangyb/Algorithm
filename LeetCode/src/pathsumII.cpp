#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* ================================================================== */
/*                        Tool Functions                              */
/* ================================================================== */

vector<string> StringSplit(string srcStr,string sepChar)
{
    vector<string> dstStr;
    int nextIndex = -1;
    string restStr = srcStr;

    while(1)
    {
        nextIndex = restStr.find_first_of(sepChar);
        
        if(nextIndex == -1)
        {
            if(restStr != "")
                dstStr.push_back(restStr);
            break;
        }

        string newStr = restStr.substr(0,nextIndex);
        dstStr.push_back(newStr);

        if(nextIndex == restStr.length()-1)
        {
            break;
        }
        restStr = restStr.substr(nextIndex+1); 
        
    }

    return dstStr;
}

bool IsDigitOrSharp(string str)
{
    if(str.size() <= 0)
        return false;
    
    if(str.size() == 1){
        if(str[0] == '#' || isdigit(str[0]))
            return true;
        else
            return false;
    }
    else{
        if(!isdigit(str[0]) && str[0] != '-')
            return false;
        for(size_t i = 1;i < str.size();i ++){
            if(!isdigit(str[i]))
                return false;
        }
        return true;
    }
}

// make binary tree by array(preorder traversal array)
void MakeBinaryTreePre_(const vector<string>& vnode,int& index,TreeNode *&root){
    index++;
    if(vnode.size() <= index || vnode[index] == "#")
        root = NULL;
    else{
        root = new TreeNode(atoi(vnode[index].c_str()));
        if(root == NULL) 
            exit(OVERFLOW);
        MakeBinaryTreePre_(vnode,index,root->left);
        MakeBinaryTreePre_(vnode,index,root->right);
    }
}

bool MakeBinaryTreePre(string treestr,TreeNode *&root){
    // check ilegal
    if(treestr.size() <= 2 || treestr[0] != '{' || treestr[treestr.size()-1] != '}')
        return false;
    string realstr = treestr.substr(1,treestr.size()-2);
    vector<string> vnode = StringSplit(realstr,",");
    for(size_t i = 0;i < vnode.size();i ++)
    {
        if(!IsDigitOrSharp(vnode[i]))
            return false;
    }

    // make tree
    int index = 0;
    if(vnode[index] == "#")
        root = NULL;
    else{
        root = new TreeNode(atoi(vnode[index].c_str()));
        if(root == NULL)
            exit(OVERFLOW);
        MakeBinaryTreePre_(vnode,index,root->left);
        MakeBinaryTreePre_(vnode,index,root->right);
    }
    return true;
}

void PreOrderTraversal(TreeNode * root){
    if(root == NULL)
        return;

    printf("%d,",root->val);
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> res;
        if(root == NULL) return res;
        vector<int> path;
        path.push_back(root->val);
        pathSumRecursively(root,sum,root->val,path,res);
        return res;
    }
private:
    void pathSumRecursively(TreeNode *root,const int expectSum,int curSum,vector<int>& path,vector<vector<int>>& res){
        if(root == NULL) return ;
        TreeNode *p = root;
        if(p->left == NULL && p->right == NULL){
            if(expectSum == curSum){
                res.push_back(path);
            }
        }

        if(p->left != NULL){
            path.push_back(p->left->val);
            pathSumRecursively(p->left,expectSum,curSum + p->left->val,path,res);
            path.pop_back();
        }
        if(p->right != NULL){
            path.push_back(p->right->val);
            pathSumRecursively(p->right,expectSum,curSum + p->right->val,path,res);
            path.pop_back();
        }
    }
};

int main(int argc,char** argv)
{
    Solution so;

    vector<string> cases;

    /*cases.push_back("{a,sd}");
    cases.push_back("xx");
    cases.push_back("{#,33}");
    cases.push_back("{#,33,}");
    cases.push_back("{#,3.3,}");
    cases.push_back("{#,-1,}");
    cases.push_back("{3,9,20,#,##,15,7}");
    cases.push_back("{11,33}");
    cases.push_back("{1,2,#,#,3,9}");
    cases.push_back("{3,9,20,#,#,15,7}");
    cases.push_back("{1,2,3,#,#,4,#,#,5}");
    cases.push_back("{1,2,3,6,8,5,#,7,#,#,#,4}");*/
    cases.push_back("{5,4,11,7,#,#,#,#,8,8,#,1,#,#,4,#,1,#,#}");
    cases.push_back("{5,4,11,7,#,#,2,#,#,#,8,13,#,#,4,5,#,#,1,#,#}");
    cases.push_back("{#}");
    cases.push_back("{22}");

    for(int i = 0;i < cases.size(); i ++)
    {
        TreeNode *tree = NULL;
        // 先根序列构造
        bool ret = MakeBinaryTreePre(cases[i],tree);
        printf("case \"%s\":%d\n",cases[i].c_str(),ret);
        if(ret){
            //PreOrderTraversal(tree);
            cout<<endl;
            vector<vector<int>> res;
            res = so.pathSum(tree,22);

            for(int i = 0;i < res.size();i ++)
            {
                for(int j = 0;j < res[i].size(); j++)
                {
                    if(j != 0) cout<<"-"; 
                    cout<<res[i][j];
                }
                cout<<endl;
            }
        }
        cout<<endl;

        // TODO destroy
    }
}
