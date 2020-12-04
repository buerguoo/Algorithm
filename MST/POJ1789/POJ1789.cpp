#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
const int MAXN = 2005;
const int INF = 0x3f3f3f3f;
int cost[MAXN][MAXN];
int lowcost[MAXN];
bool vis[MAXN];
char trucks[MAXN][10];
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowcost[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i){
        int minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j] < minc){
                minc = lowcost[j];
                p = j;
            }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j]>cost[p][j])
                lowcost[j] = cost[p][j];
    }
    return ans;
}
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        memset(trucks, 0, sizeof(trucks));
        memset(cost, 0,  sizeof(cost));
        for(int i = 0;i < n;++i)
            scanf("%s", &trucks[i]);
        for(int i = 0;i < n;++i)
            for(int j = i+1;j < n;++j)
                for(int k = 0;k < 7;++k)
                    if(trucks[i][k] != trucks[j][k])
                        cost[i][j] = ++cost[j][i];
        
        printf("The highest possible quality is 1/%d.\n", prim(n));
    }
    
    return 0;
}