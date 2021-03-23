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
public:
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        int sz = word.length();
        bool vis[200][200];
        memset(vis, false, sizeof(vis));
        queue<pair<int, int>> Q;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j)
                if(word[0] == board[i][j]){
                    Q.push(make_pair(i*m+j, 1));
                    while(c < sz && !Q.empty()){
                        int tp = Q.front().first;
                        int c = Q.front().second;
                        Q.pop();
                        int x = tp/m, y = tp%m;
                        vis[x][y] = true;
                        int tx, ty;
                        for(int i = 0;i < 4;++i){
                            tx = x + dir[i][0];
                            ty = y + dir[i][1];
                            if(tx >= 0 && tx < n && ty >= 0 && ty < m && !vis[tx][ty]  && board[tx][ty] == word[c]){
                                Q.push(make_pair(tx*m+ty, c+1));
                                printf("%d %d %d\n", tx, ty, c);
                            }
                        }
                    }
                     if(c < sz){
                            memset(vis, false, sizeof(vis));
                        }else return true;
                }
        
        return false;
    }
};