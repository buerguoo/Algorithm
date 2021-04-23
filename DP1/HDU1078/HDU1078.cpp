/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:78ms
memory:1816kB

Data:2021-04-24 00:13:22
*/
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
const int MAXN = 105;
int a[MAXN][MAXN];
int dp[MAXN][MAXN];
int k, n;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int dfs(int x, int y)
{
    int tx, ty, Max = 0, tmp;
    if(dp[x][y] == -1){
        for(int i = 1;i <= k;++i)
            for(int j = 0;j < 4;++j){
                tx = x + dir[j][0]*i;
                ty = y + dir[j][1]*i;
                if(tx >= 0 && tx < n && ty >= 0 && ty < n && a[tx][ty] > a[x][y]){
                    tmp = dfs(tx, ty);
                    Max = max(Max, tmp);
                }
            }
        dp[x][y] = Max + a[x][y];
    }
    return dp[x][y];
}
int main()
{
    while(~scanf("%d %d", &n, &k) && (n != -1)){
        memset(dp, -1, sizeof(dp));
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                scanf("%d", &a[i][j]);
        printf("%d\n", dfs(0, 0));
    }
    return 0;   
}
