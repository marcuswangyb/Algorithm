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
 
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if(root == NULL)
            return res;
        int levelNum = 0;
        queue<TreeNode *> queue1,queue2;

        // 交替插入不同队列，以保证每个vector<int>中保存树的同一lever结点
        queue1.push(root);
        while(!queue1.empty() || !queue2.empty()){
            while(!queue1.empty()){
                TreeNode *cur = queue1.front();
                queue1.pop();
                if(res.size() < levelNum + 1){
                    vector<int> levelVec;
                    res.push_back(levelVec);
                }
                res[levelNum].push_back(cur->val);

                if(cur->left != NULL)
                    queue2.push(cur->left);
                if(cur->right != NULL)
                    queue2.push(cur->right);
            }
            levelNum ++;
            while(!queue2.empty()){
                TreeNode *cur = queue2.front();
                queue2.pop();
                if(res.size() < levelNum + 1){
                    vector<int> levelVec;
                    res.push_back(levelVec);
                }
                res[levelNum].push_back(cur->val);

                if(cur->left != NULL)
                    queue1.push(cur->left);
                if(cur->right != NULL)
                    queue1.push(cur->right);
            }
            levelNum ++;
        }

        return res;
    }
};

string VecTreeToJson(const vector<vector<int>> & treeVec)
{
    stringstream stream;
    string res;

    stream << "["; 
    for(int i = 0;i < treeVec.size();i ++)
    {
        stream << "\n  [";
        for(int j = 0;j < treeVec[i].size();j ++)
        {
            stream << treeVec[i][j];
            if(j != treeVec[i].size() - 1)
                stream << ",";
        }
        stream << "]";
        if(i != treeVec.size() - 1)
            stream << ",";
    }
    stream << "\n]";
    res =stream.str();

    return res;
}

int main(int argc,char** argv)
{
    Solution so;

    // VecTreeToJson test
    vector<vector<int>> res0;
    vector<int> a;
    vector<int> b;
    a.push_back(33);
    b.push_back(66);
    b.push_back(3);
    res0.push_back(a);
    res0.push_back(b);
    cout<<VecTreeToJson(res0)<<endl<<endl;
    
    // case 1,null
    vector<vector<int>> res1;
    TreeNode *root1 = NULL;
    res1 = so.levelOrder(root1);
    cout<<VecTreeToJson(res1)<<endl<<endl;


    // case 2,common
    vector<vector<int>> res2;
    TreeNode *root2 = new TreeNode(3);
    TreeNode *node2_1 = new TreeNode(9);
    TreeNode *node2_2 = new TreeNode(20);
    TreeNode *node2_3 = new TreeNode(15);
    TreeNode *node2_4 = new TreeNode(7);
    root2->left = node2_1;
    root2->right = node2_2;
    node2_2->left = node2_3;
    node2_2->right = node2_4;
    res2 = so.levelOrder(root2);
    cout<<VecTreeToJson(res2)<<endl<<endl;

    // case 3,all left
    vector<vector<int>> res3;
    TreeNode *root3 = new TreeNode(1);
    TreeNode *node3_1 = new TreeNode(2);
    TreeNode *node3_2 = new TreeNode(3);
    TreeNode *node3_3 = new TreeNode(4);
    root3->left = node3_1;
    node3_1->left = node3_2;
    node3_2->left = node3_3;
    res3 = so.levelOrder(root3);
    cout<<VecTreeToJson(res3)<<endl<<endl;

    // case 4,only root
    vector<vector<int>> res4;
    TreeNode *root4 = new TreeNode(99);
    res4 = so.levelOrder(root4);
    cout<<VecTreeToJson(res4)<<endl<<endl;
}
