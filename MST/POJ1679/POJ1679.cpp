/*
Author:buerguoo
Time:16ms
memory:684KB

Data:2020-11-19 15:27:39
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
int Maxc[MAXN][MAXN];
bool used[MAXN][MAXN];
int pre[MAXN];
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    memset(used, false, sizeof(used));
    memset(Maxc, 0, sizeof(Maxc));
    for(int i = 0;i < n;++i){
        lowc[i] = cost[0][i];
        pre[i] = 0;
    }
    vis[0] = true;
    pre[0] = -1;
    for(int i = 1;i < n;++i){
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
        used[p][pre[p]] = used[pre[p]][p] = true;
        for(int j = 0;j < n;++j){
            if(vis[j] && j != p)
                Maxc[p][j] = Maxc[j][p] = max(Maxc[pre[p]][j], lowc[p]);
            if(!vis[j] && lowc[j] > cost[p][j]){
                lowc[j] = cost[p][j];
                pre[j] = p;
            }
        }
    }

    return ans;
}
int ans;
int umst(int n)
{
    int Min = INF;
    for(int i = 0;i < n;++i)
        for(int j = i+1;j < n;++j)
            if(!used[i][j] && cost[i][j]!=INF)
                Min = min(Min, ans-cost[i][j]+Maxc[i][j]);
    if(Min == INF)  return -1;

    return Min;
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
         for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                if(i==j)cost[i][j]=0;
                else cost[i][j]=INF;
            }
        for(int i = 0;i < m;++i){
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            cost[x-1][y-1] = cost[y-1][x-1] = w;
        }
        ans = prim(n);
        if(ans == -1)   printf("Not Unique!\n");
        else if(ans == umst(n)) printf("Not Unique!\n");
        else printf("%d\n", ans);
    }
    return 0;
}