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

void PostOrderTraversal(TreeNode * root){
    if(root == NULL)
        return;

    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    printf("%d,",root->val);
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
private:
    struct TreeNodeEx{
        TreeNode *node;
        int tag;    // 1-first time,2-second time
        
        TreeNodeEx(TreeNode *in_node,int in_tag){
            node = in_node;
            tag = in_tag;
        }
    };
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        if(root == NULL) return res;
        stack<TreeNodeEx> s;
        TreeNode *p = root;
        while(!s.empty() || p != NULL){
            while(p != NULL){
                s.push(TreeNodeEx(p,1));
                p = p->left;
            }
            if(!s.empty()){
                TreeNodeEx cur = s.top();
                p = cur.node;
                if(cur.tag == 1){
                    s.top().tag = 2;
                    p = p->right;
                }
                else{
                    res.push_back(p->val);
                    s.pop();
                    p = NULL;
                }
            }
        }
        return res;
    }
};

int main(int argc,char** argv)
{
    Solution so;

    vector<string> cases;
    cases.push_back("{11,33}");
    cases.push_back("{1,2,#,#,3,9}");
    cases.push_back("{3,9,20,#,#,15,7}");
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
            PostOrderTraversal(tree);
            cout<<endl;
            vector<int> res;
            res = so.postorderTraversal(tree);

            for(int i = 0;i < res.size();i ++)
                cout<<res[i]<<" ";
            cout<<endl;
        }
        cout<<endl;

        // TODO destroy
    }
}
