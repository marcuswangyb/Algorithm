#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stack>

#include "gtest/gtest.h"

using namespace std;

/* ================================================================== */
/*                       Basic Data Struct                            */
/* ================================================================== */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* ================================================================== */
/*                        Tool Functions                              */
/* ================================================================== */

vector<string> StringSplit(string srcStr,string sepChar);

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

// make binary tree by array(level traversal array)
bool MakeBinaryTree(string treestr,TreeNode *&root)
{
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
    vector<TreeNode *> treevec;
    root = new TreeNode(atoi(vnode[0].c_str()));
    treevec.push_back(root);
    int curLevelStart = 0;
    int curLevelNum = 1;
    int nextpos = 1;
    while(nextpos < vnode.size() && curLevelNum != 0)
    {
        int nextLevelStart = curLevelStart + curLevelNum;
        int nextLevelNum = 0;
        nextpos = nextLevelStart;
        for(int i = curLevelStart,j = 0;j < curLevelNum;i ++,j++)
        {
            if(nextpos >= vnode.size())
                break;
            if(vnode[i] != "#"){
                if(vnode[nextpos] == "#")
                    treevec.push_back(NULL);
                else{
                    TreeNode *tmp = new TreeNode(atoi(vnode[nextpos].c_str()));
                    treevec.push_back(tmp);
                }
                treevec[i]->left = treevec[nextpos];
                nextpos ++;

                if(nextpos >= vnode.size())
                    break;

                if(vnode[nextpos] == "#")
                    treevec.push_back(NULL);
                else{
                    TreeNode *tmp = new TreeNode(atoi(vnode[nextpos].c_str()));
                    treevec.push_back(tmp);
                }
                treevec[i]->right = treevec[nextpos];
                nextpos ++;

                nextLevelNum += 2;
            }
        }
        
        curLevelStart = nextLevelStart;
        curLevelNum = nextLevelNum;
    }

    return true;
}

string BinaryTreeToString(TreeNode *root)
{
    // TODO
    string res = "";
    return res;
}

void DestroyBinaryTree(TreeNode **root)
{
    // TODO
}

void PreOrderTraversal(TreeNode * root){
    if(root == NULL)
        return;

    printf("%d,",root->val);
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

void InOrderTraversal(TreeNode * root){
    if(root == NULL)
        return;

    InOrderTraversal(root->left);
    printf("%d,",root->val);
    InOrderTraversal(root->right);
}

void PostOrderTraversal(TreeNode *root){
    if(root == NULL) return;
    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    printf("%d,",root->val);
}

void PreOrderTraversal2(TreeNode *root)
{
    if(root == NULL) return;
    stack<TreeNode *> s;
    TreeNode *p = root;
    while(p!= NULL || !s.empty()){
        while(p != NULL){
            cout<<p->val<<" ";
            s.push(p);
            p = p->left;
        }
        while(p == NULL && !s.empty()){
            p = s.top();
            s.pop();
            p = p->right;
            if(p!= NULL) s.push(p);
        }
    }
    cout<<endl;
}

void InOrderTraversal2(TreeNode *root)
{
    if(root == NULL) return;
    stack<TreeNode*> s;
    TreeNode *p = root;
    while(p != NULL|| !s.empty())
    {
        while(p != NULL){
            //cout<<p->val<<" ";
            s.push(p);
            p=p->left;
        }
        if(!s.empty())
        {
            p=s.top();
            cout<<p->val<<" ";
            s.pop();
            p=p->right;
        }
    }
}

void PostOrderTraversal2(TreeNode * root){
    if(root == NULL) return;
    stack<pair<TreeNode*,int>> s;
    TreeNode *p = root;
    while(p != NULL|| !s.empty())
    {
        while(p != NULL){
            s.push(make_pair(p,2));
            p=p->left;
        }
        if(!s.empty())
        {
            pair<TreeNode*,int> cur = s.top();
            p = cur.first;
            if(cur.second == 2){
                s.pop();
                s.push(make_pair(p,1));
                p = p->right;
            }
            else if(cur.second == 1){
                s.pop();
                cout<<p->val<<" ";
                p = NULL;
            }
        }
    }
}



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

/* ================================================================== */
/*                            Dev test                                */
/* ================================================================== */

void DevTest()
{
    vector<string> cases;
    cases.push_back("{a,sd}");
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
    cases.push_back("{1,2,3,6,8,5,#,7,#,#,#,4}");
    
    for(int i = 0;i < cases.size(); i ++)
    {
        TreeNode *tree = NULL;
        bool ret = MakeBinaryTree(cases[i],tree);
        printf("case \"%s\":%d\n",cases[i].c_str(),ret);
        if(ret){
            PostOrderTraversal(tree);
            cout<<endl;
            PostOrderTraversal2(tree);
            cout<<endl;
        }
        cout<<endl;

        // TODO destroy tree
    }
}

/* ================================================================== */
/*                           Unit test                                */
/* ================================================================== */

int main(int argc,char** argv)
{
    DevTest();
    
    //testing::InitGoogleTest(&argc,argv);
    //RUN_ALL_TESTS();
    
    printf("success!\n");
}
