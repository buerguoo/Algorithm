#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
#include <list>
using namespace std;
class Solution {
public:
    private:
    static const int MAXN = 110;
    bool vis[MAXN][MAXN];
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int movingCount(int m, int n, int k) {
        int init = min(min(m, n), k/2);
        if(init > 0) init--;
        memset(vis, false, sizeof(vis));
        for(int i = 0;i <= init;++i)
            for(int j = 0;j <= init;++j)
                vis[i][j] = true;
        int res = (init+1)*(init+1);
        queue<int> Q;
        for(int i = 0;i <= init;++i){
            Q.push(init*n+i);
            Q.push(i*n+init);
        }
        while(!Q.empty()){
            int tmp = Q.front();
            Q.pop();
            int x = tmp/n, y = tmp%n;
            int tx = x, ty = y;
            for(int i = 0;i < 4;++i){
                tx += dir[i][0];
                ty += dir[i][1];
                if(tx < m && ty < n && chai(tx)+chai(ty) <= k && !vis[tx][ty]){
                    Q.push(tx*n+ty);
                    vis[tx][ty] = true;
                    res++;
                }
            }
        }
        return res;
    }
    int chai(int x){
        int res = 0;
        while(x){
            res += x % 10;
            x /= 10;
        }
        return res;
    }
};