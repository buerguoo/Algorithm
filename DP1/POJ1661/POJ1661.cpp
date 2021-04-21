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
//WA 艹
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 100010;
int dp[MAXN][2];
struct platform{
    int a, b, h;
    bool operator<(const platform &a)const{
        return h > a.h;
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
        P[0].a = P[0].b = x;
        P[0].h = y;
        P[n+1].a = -INF, P[n+1].b = INF, P[n+1].h = 0;
        int dis = 0;
        sort(P+1, P+n);
        for(int i = 1;i <= n+1;++i){
            dp[i][0] = dp[i][1] = INF;
            for(int j = i-1;j >= 0;--j) if(P[j].h - P[i].h <= H)
            {
                if(P[i].a <= P[j].a && P[i].b >= P[j].a){
                    dis = P[j].a - P[i].a + P[j].h - P[i].h;
                    if(dis > INF) dis = P[j].h - P[i].h;
                    if(dp[i][0] > dp[j][0] + dis){
                        dp[i][0] = dp[j][0] + dis;
                        break;
                    }
                }
            }
            for(int j = i-1;j >= 0;--j) if(P[j].h - P[i].h <= H){
                if(P[i].a <= P[j].b && P[i].b >= P[j].b){
                    dis = P[i].b - P[j].b + P[j].h - P[i].h;
                    if(dis > INF) dis = P[j].h - P[i].h;
                    if(dp[i][1] > dp[j][1] + dis){
                        dp[i][1] = dp[j][1] + dis;
                        break;
                    }
                }
            }
        }
        printf("%d %d\n", dp[n+1][0], dp[n+1][1]);
        printf("%d\n", min(dp[n+1][0], dp[n+1][1]));
    }
    return 0;
}
