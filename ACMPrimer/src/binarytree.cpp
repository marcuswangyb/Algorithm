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

/* ================================================================== */

vector<string> StringSplit(string srcStr,string sepChar);

struct TreeNode
{
    int val;
    TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

void PreOrderTraversal2(TreeNode * root){
	stack<TreeNode*> s;
    TreeNode *p=root;
    while(p!=NULL||!s.empty())
    {
        while(p!=NULL)
        {
			cout<<p->val<<" ";
            s.push(p);
			p=p->left;
        }
        if(!s.empty())
        {
            p=s.top();
            s.pop();
			p=p->right;
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
    /*int input[] = {2,4,5,1,8,4};
    int len = 6;
    MakeBinaryTree(input,len,&tree);*/
	/*
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

	InOrderTraversal(root2);
	cout<<endl;
	PreOrderTraversal(root2);
	cout<<endl;
	*/

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
	
	for(int i = 0;i < cases.size(); i ++)
	{
		TreeNode *tree = NULL;
		bool ret = MakeBinaryTree(cases[i],tree);
		printf("case \"%s\":%d\n",cases[i].c_str(),ret);
		if(ret){
			PreOrderTraversal(tree);
			cout<<endl;
			PreOrderTraversal2(tree);
			cout<<endl;
			//InOrderTraversal(tree);
			//cout<<endl;
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
