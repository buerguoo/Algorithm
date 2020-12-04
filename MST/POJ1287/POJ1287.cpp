#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
const int MAXN = 55;
const int INF = 0x3f3f3f3f;
int cost[MAXN][MAXN];
int lowcost[MAXN];
bool vis[MAXN];
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 1;i <= n;++i)    lowcost[i] = cost[1][i];
    vis[1] = true;
    for(int i = 1;i < n;++i){
        int minc = INF;
        int p = -1;
        for(int j = 1;j <= n;++j){
            if(!vis[j] && minc>lowcost[j]){
                minc = lowcost[j];
                p = j;
            }
        }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 1;j <= n;++j){
            if(!vis[j] && lowcost[j]>cost[p][j])
                lowcost[j] = cost[p][j];
        }
    }
    return ans;
}
int main()
{
    int P, R;
    while (scanf("%d%d", &P, &R) && P)
    {
        for(int i = 0;i <= P;++i)
            for(int j = 0;j <= P;++j)
                cost[i][j] = INF;
        int a, b, d;
        for(int i = 0;i < R;++i){
            scanf("%d%d%d", &a, &b, &d);
            cost[a][b] = cost[b][a] = min(cost[a][b], d);
        }
        printf("%d\n", prim(P));
    }
    
    return 0;
}