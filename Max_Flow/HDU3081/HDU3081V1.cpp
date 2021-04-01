/*
Time limit:1000ms
Memory limit:32768Kb

Author:buerguoo
Time:WA
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
const int INF = 0x3f3f3f3f;
const int MAXN = 210;
int maze[MAXN][MAXN];
int mp[MAXN][MAXN];
int gap[MAXN], pre[MAXN], cur[MAXN], dis[MAXN];
int F[MAXN];
int sap(int s, int t, int nodenum)
{
    memset(dis, 0, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    memset(gap, 0, sizeof(gap));
    gap[0] = nodenum;
    int u = pre[s] = s;
    int maxflow = 0, aug = -1;
    while(dis[s] < nodenum){
        loop:
            for(int v = cur[u];v < nodenum;v++){
                if(maze[u][v] && dis[u] == dis[v] + 1){
                    if(aug == -1 || aug > maze[u][v]) aug = maze[u][v];
                    pre[v] = u;
                    u = cur[u] = v;
                    if(v == t){
                        maxflow += aug;
                        for(u = pre[u]; v != s;v = u, u = pre[u]){
                            maze[u][v] -= aug;
                            maze[v][u] += aug;
                        }
                        aug = -1;
                    }
                    goto loop;
                }
            }
        int mindis = nodenum - 1;
        for(int v = 0;v < nodenum;++v)
            if(maze[u][v] && mindis > dis[v]){
                mindis = dis[v];
                cur[u] = v;
            }
        if(!(--gap[dis[u]])) break;
        gap[dis[u] = mindis+1]++;
        u = pre[u];
    }
    return maxflow;
}
int find(int x)
{
    if(F[x] == -1) return x;
    return F[x] = find(F[x]);
}
void Union(int x1, int x2)
{
    int f1 = find(x1);
    int f2 = find(x2);
    if(f1 != f2)
        F[f2] = f1;
}
int main()
{
    int Case;
    int n, m, f;
    int u, v;
    scanf("%d", &Case);
    while(Case--){
        memset(mp, 0, sizeof(mp));
        memset(F, -1, sizeof(F));
        scanf("%d %d %d", &n, &m, &f);
        int s = 0, t = 2 * n + 1;
        while(m--){
            scanf("%d %d", &u, &v);
            mp[u][n+v] = 1;
            mp[v+n][u] = -1;
        }
        while(f--){
            scanf("%d %d", &u, &v);
            Union(u, v);
        } 
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(find(i) == find(j))
                    for(int k = n+1;k <= 2*n;++k)
                        if(mp[i][k] == 1){
                            mp[j][k] = 1;
                            mp[k][j] = -1;
                        }
        int l = 0, h = n, mid, ans;
        while(l <= h){
            mid = (l + h) >> 1;
            memcpy(maze, mp, sizeof(maze));
            for(int i = 1;i <= n;++i){
                maze[s][i] = mid;
                maze[i][s] = -mid;
                maze[i+n][t] = mid;
                maze[t][i+n] = -mid;
            }
            if(mid*n == sap(s, t, 2*n+2)){
                ans = mid;   
                l = mid+1;
            }
            else h = mid-1;
        }
        printf("%d\n", ans);
    }
    return 0;
}