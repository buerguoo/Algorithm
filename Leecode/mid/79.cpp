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
const int MAXN = 10010;
const int MAXM = 100010;
class Solution {
    int m, n;
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if (dfs(board, word, i, j, 0))  return true;
        return false;
    }
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int index) {
        if(i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[index])    return false;
        if(index == word.size() - 1)    return true;    //找到单词
        board[i][j] = '\0';         //标记为走过
        bool flag = dfs(board, word, i + 1, j, index + 1) || dfs(board, word, i, j + 1, index + 1) || 
                    dfs(board, word, i - 1, j, index + 1) || dfs(board, word, i, j - 1, index + 1);
        board[i][j] = word[index];  //复原
        return flag;
    }
};