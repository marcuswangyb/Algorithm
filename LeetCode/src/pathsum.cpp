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
    bool hasPathSum(TreeNode *root, int sum) {
        
    }
};

void inorderTraversal(TreeNode * root){
	if(root == NULL)
		return;

	
	inorderTraversal(root->left);
	
	inorderTraversal(root->right);
	printf("%d,",root->val);
}

int main(int argc,char** argv)
{
	Solution so;

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
	inorderTraversal(root2);
}
