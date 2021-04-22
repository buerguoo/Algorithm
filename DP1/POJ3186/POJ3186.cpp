/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:110ms
memory:15936Kb

Data:2021-04-22 23:16:26
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
const int MAXN = 2010;
const int MAXM = 100010;
int dp[MAXN][MAXN];
int a[MAXN];
int main()
{
    int n;
    while(~scanf("%d", &n)){
        for(int i = 1;i <= n;++i){
            scanf("%d", &a[i]);
        }
        memset(dp, 0, sizeof(dp));
        for(int i = n-1;i >= 1;--i)
            for(int j = i;j <= n;++j)
                dp[i][j] = max(dp[i+1][j]+a[i]*(n-j+i), dp[i][j-1]+a[j]*(n-j+i));
        printf("%d\n", dp[1][n]);
    }
    return 0;
}