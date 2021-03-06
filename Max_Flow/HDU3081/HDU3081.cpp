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
    int  Case;
    int n, m, f;
    int u, v;
    scanf("%d", &Case);
    while(Case--){
        memset(maze, 0, sizeof(maze));
        memset(F, -1, sizeof(F));
        scanf("%d %d %d", &n, &m, &f);
        int s = 0, t = 2 * n + 1;
        for(int i = 1;i <= n;++i){
            maze[s][i] = n;
            maze[i][s] = -n;
            maze[i+n][t] = n;
            maze[t][i+n] = -n;
        }
        while(m--){
            scanf("%d %d", &u, &v);
            maze[u][n+v] = 1;
            maze[v+n][u] = -1;
        }
        while(f--){
            scanf("%d %d", &u, &v);
            Union(u, v);
            //maze[u][v] = 1;
            //maze[v][u] = -1;
        }
        
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(find(i) == find(j))
                    for(int k = n+1;k <= 2*n;++k){
                        if(maze[i][k] == 1){
                            maze[j][k] = 1;
                            maze[k][j] = -1;
                        }
                }
        sap(s, t, 2*n+2);

        int ans = INF;
        for(int i = 1;i <= n;++i)
            if(ans > n-maze[s][i]) ans = n - maze[s][i];
        printf("%d\n", ans);
    }
    return 0;
}