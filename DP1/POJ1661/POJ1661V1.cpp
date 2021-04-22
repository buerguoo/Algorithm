/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:16ms
memory:124Kb

Data:2021-04-22 22:37:43
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
int dp[MAXN][2];
struct platform{
    int a, b, h;
    bool operator<(const platform &a)const{
        return h < a.h;
    }
}P[MAXN];
int main()
{
    int n, x, y, H;
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d %d", &n, &x, &y, &H);
        memset(dp, 0, sizeof(dp));
        for(int i = 1;i <= n;++i)   scanf("%d %d %d", &P[i].a, &P[i].b, &P[i].h);
        P[n+1].a = P[n+1].b = x;
        P[n+1].h = y;
        sort(P+1, P+n+1);
        for(int i = 1;i <= n+1;++i){
            dp[i][0] = dp[i][1] = INF;
            P[0].a = P[i].a, P[0].b = P[i].b, P[0].h = 0;
            for(int j = i-1;j >= 0;--j) if(P[i].h - P[j].h <= H)
            {
                if(P[j].a <= P[i].a && P[j].b >= P[i].a){
                    dp[i][0] = P[i].h - P[j].h + min(dp[j][0]+P[i].a-P[j].a, dp[j][1]+P[j].b-P[i].a);
                    break;
                }
            }
            for(int j = i-1;j >= 0;--j) if(P[i].h - P[j].h <= H){
                if(P[j].a <= P[i].b && P[j].b >= P[i].b){
                    dp[i][1] = P[i].h - P[j].h + min(dp[j][0]+P[i].b-P[j].a, dp[j][1]+P[j].b-P[i].b);
                    break;
                }
            }
        }
        printf("%d\n", min(dp[n+1][0], dp[n+1][1]));
    }
    return 0;
}