/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:
memory:

Data:
*/
//待续... 我好弱...
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
int dp[MAXN];
bool vis[MAXN];
struct platform{
    int a, b, h;
    int pos;
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
        memset(vis, false, sizeof(vis));
        for(int i = 1;i <= n;++i)   scanf("%d %d %d", &P[i].a, &P[i].b, &P[i].h);
        P[0].a = P[0].b = x;
        P[0].h = y; P[0].pos = x;
        P[n+1].a = -INF, P[n+1].b = INF, P[n+1].h = 0;
        int dis = 0;
        sort(P+1, P+n);
        for(int i = 1;i <= n+1;++i){
            dp[i] = INF;
            for(int j = 0;j < i;++j) if(P[j].h - P[i].h <= H && !vis[j])
            {
                if(P[i].a <= P[j].a && P[i].b >= P[j].a){
                    dis = P[j].pos-P[j].a+P[j].h-P[i].h;
                    printf("1 %d\n", dis);
                    if(dp[i] > dp[j]+dis){
                        dp[i] = dp[j] + dis;
                        P[i].pos = P[j].a;
                        vis[i] = true;
                    }
                }
                if(P[i].a <= P[j].b && P[i].b >= P[j].b){
                    dis = -P[j].pos+P[j].b+P[j].h-P[i].h;
                    printf("2 %d\n", dis);
                    if(dp[i] > dp[j]+dis){
                        dp[i] = dp[j] + dis;
                        P[i].pos = P[j].b;
                        vis[i] = true;
                    }
                }
            }
         }   
        printf("%d\n", dp[n+1]);
    }
    return 0;
}
