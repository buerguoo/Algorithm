/*
Author:buerguoo
Time:171ms
memory:1792KB

Data:2020-11-19 16:47:13
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
const int MAXN = 105;
const int INF = 0x3f3f3f3f;
int cost[MAXN][MAXN];
int lowc[MAXN];
bool vis[MAXN];
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowc[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i)
    {
        int minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowc[j] < minc){
                minc = lowc[j];
                p = j;
            }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowc[j] > cost[p][j])
                lowc[j] = cost[p][j];
    }

    return ans;
}
int main()
{
    int N;
    while (scanf("%d", &N) && N)
    {
        int u, v, w;
        for(int i = 0;i < N*(N-1)/2;++i){
            scanf("%d%d%d", &u, &v, &w);
            cost[u-1][v-1] = cost[v-1][u-1] = w;
        }
        printf("%d\n", prim(N));
    }
    
    return 0;
}