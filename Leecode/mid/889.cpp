#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
//根据前序遍历和后序遍历构造二叉树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int sz;
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        sz = pre.size();
        createTree(1, pre);
        
    }
    TreeNode* createTree(int rt, vector<int> pre){
        
        if(rt > sz) return NULL; 
        TreeNode* root = new TreeNode(pre[rt-1]);
        root->left = createTree(rt<<1, pre);
        root->right = createTree(rt<<1|1, pre);
        return root;
    }
};