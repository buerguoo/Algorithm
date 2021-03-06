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
        for(int i = 0;i <= n+1;++i){
            dp[i][0] = dp[i][1] = INF;
            for(int j = i+1;j <= n+1;++j) if(P[i].h - P[j].h <= H)
            {
                if(P[j].a <= P[i].a && P[j].b >= P[i].a){
                    dis = P[i].a - P[j].a + P[i].h - P[j].h;
                    if(dis > INF) dis = P[i].h - P[j].h;
                    if(dp[j][0] > dp[i][0] + dis){
                        dp[j][0] = dp[i][0] + dis;
                        break;
                    }
                }
            }
            for(int j = i+1;j <= n+1;++j) if(P[i].h - P[j].h <= H){
                if(P[j].a <= P[i].b && P[j].b >= P[i].b){
                    dis = P[j].b - P[i].b + P[i].h - P[j].h;
                    if(dis > INF) dis = P[i].h - P[j].h;
                    if(dp[j][1] > dp[i][1] + dis){
                        dp[j][1] = dp[i][1] + dis;
                        break;
                    }
                }
            }
        }
        printf("%d\n", min(dp[n+1][0], dp[n+1][1]));
    }
    return 0;
}
