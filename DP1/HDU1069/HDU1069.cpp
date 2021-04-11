/*
Time limit:1000ms
Memory limit:32768Kb

Author:buerguoo
Time:15MS
memory:1740kB

Data:2021-04-11 22:36:54
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
const int MAXN = 130;
const int MAXM = 100010;
int dp[MAXN];
struct Cuboid{
    int l, w, h;
    Cuboid(int _l=0, int _w=0, int _h=0):l(_l), w(_w), h(_h){}
    bool operator<(const Cuboid &a){
        if(a.w - w == 0) return l < a.l;
        else return w < a.w;
    }
}cub[MAXN];
int main()
{
    int n, Case = 0;
    int l, w, h;
    while(~scanf("%d", &n) && n){
        for(int i = 1;i <= n;++i){
            scanf("%d %d %d", &l, &w, &h);
            cub[i] = Cuboid(l, w, h);
            cub[n+i] = Cuboid(l, h, w);
            cub[2*n+i] = Cuboid(w, l, h);
            cub[3*n+i] = Cuboid(w, h, l);
            cub[4*n+i] = Cuboid(h, l, w);
            cub[5*n+i] = Cuboid(h, w, l);
        }
        sort(cub+1, cub+6*n+1);
        dp[0] = 0;
        for(int i = 1;i <= 6*n;++i){
            dp[i] = cub[i].h;
            for(int j = 1;j < i;++j)
                if(cub[j].l < cub[i].l && cub[j].w < cub[i].w)
                    dp[i] = max(dp[i], dp[j]+cub[i].h);
        }
                    
        int Max = 0;
        for(int i = 1;i <= 6*n;++i)
            Max = max(Max, dp[i]);
        printf("Case %d: maximum height = %d\n", ++Case, Max);
    }
    return 0;
}