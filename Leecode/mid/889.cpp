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
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int N = pre.size();
        return createTree(0, 0, N, pre, post);
    }
    TreeNode* createTree(int i0, int i1, int N, vector<int> &pre, vector<int>& post){
        
        if(N == 0) return NULL;
        TreeNode* root = new TreeNode(pre[i0]);
        if(N == 1) return root;
        int L = 1;
        for(;L < N;++L)
            if(pre[i0+1] == post[i1+L-1])
                break;
        root->left = createTree(i0+1, i1, L, pre, post);
        root->right = createTree(i0+L+1, i1+L, N-L-1, pre, post);

        return root;
    }
};