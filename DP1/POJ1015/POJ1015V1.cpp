/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:110MS
memory:1268Kb

Data:2021-04-17 00:24:01
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
const int MAXN = 205;
const int MAXM = 805;
int dp[25][MAXM], sub[MAXN], add[MAXN];
vector<int> path[25][MAXM];
int main()
{
    int n, m, p, d;
    int Case = 0;
    while(~scanf("%d %d", &n, &m) && (n || m)){
        memset(dp, -1, sizeof(dp));
        for(int i = 0;i < 25;++i)
            for(int j = 0;j < MAXM;++j)
                path[i][j].clear();
        for(int i = 1;i <= n;++i){
            scanf("%d %d", &p, &d);
            sub[i] = p - d;
            add[i] = p + d;
        }
        int fix = 20*m;
        dp[0][fix] = 0;
        for(int i = 1;i <= n;++i)
            for(int j = m-1;j >= 0;--j){
                for(int k = 0;k < 2*fix;++k)
                    if(dp[j][k] >= 0)
                        if(dp[j][k]+add[i] > dp[j+1][k+sub[i]]){
                            dp[j+1][k+sub[i]] = dp[j][k] + add[i];
                            path[j+1][k+sub[i]] = path[j][k];
                            path[j+1][k+sub[i]].push_back(i);
                        }
            }
        int k;
        for(int i = 0;i <= fix;++i)
            if(dp[m][fix+i] >= 0 || dp[m][fix-i]>=0){
                k = i;
                break;
            }
        int S = dp[m][fix+k]>dp[m][fix-k]?fix+k:fix-k;
        int A = dp[m][S];
        int P = (A + S - fix) / 2, D = (A - S + fix) / 2;
        printf("Jury #%d\n", ++Case);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", P, D);

        for(int i = 0;i < m;++i)
            printf(" %d", path[m][S][i]);
        printf("\n\n");
    }
    return 0;
}