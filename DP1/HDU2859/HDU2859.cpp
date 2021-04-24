/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:
memory:

Data:
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
const int MAXN = 1010;
const int MAXM = 100010;
int dp[MAXN][MAXN];
char a[MAXN][MAXN];
int n;
bool match(int x, int y, int m)
{
    for(int i = 1;i <= m;++i)
        if(a[x][y-i] != a[x+i][y])
            return false;
    return true;
}
int main()
{
    while(~scanf("%d", &n) && n){
        for(int i = 0;i < n;++i)    scanf("%s", &a[i]);
        memset(dp, 0, sizeof(dp));
        for(int i = 0;i < n;++i) dp[n-1][i] = 1;
        for(int i = 0;i < n;++i) dp[i][0] = 1;
        int Max = 1;
        for(int i = n-2;i >= 0;--i)
            for(int j = 1;j < n;++j){
                if(match(i, j, dp[i+1][j-1]))
                    dp[i][j] = dp[i+1][j-1] + 1;
                else dp[i][j] = 1;
                Max = max(Max, dp[i][j]);
            }
        printf("%d\n", Max);
    }
    return 0;
}