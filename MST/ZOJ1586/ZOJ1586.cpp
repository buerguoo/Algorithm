#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
int cost[MAXN][MAXN];
int lowcost[MAXN];
bool vis[MAXN];
int ada[MAXN];
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowcost[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i)
    {
        int minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && minc > lowcost[j]){
                minc = lowcost[j];
                p = j;
            }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j] > cost[p][j])
                lowcost[j] = cost[p][j];
    }

    return ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for(int i = 0;i < n;++i)    scanf("%d", &ada[i]);
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j){
                scanf("%d", &cost[i][j]);
            }
        for(int i = 0;i < n;++i)
            for(int j = i+1;j < n;++j)
                cost[j][i] = cost[i][j] = cost[i][j]+ada[i]+ada[j];

        printf("%d\n", prim(n));
    }
    
    return 0;
}