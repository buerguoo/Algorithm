/*
Time limit:
Memory limit:

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
const int INF = 0x3f3f3f3f;
const int MAXN = 210;
int maze[MAXN][MAXN];
int gap[MAXN], pre[MAXN], cur[MAXN], dis[MAXN];
int sap(int s, int t, int nodenum)
{
    memset(gap, 0, sizeof(gap));
    memset(dis, 0, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    gap[0] = nodenum;
    int u = pre[s] = s, aug = -1, maxflow = 0;
    while(dis[s] < nodenum){
        loop:
            for(int v = cur[u];v < nodenum;++v)
                if(maze[u][v] && dis[u] == dis[v] + 1){
                    if(aug == -1 || aug > maze[u][v]) aug = maze[u][v];
                    pre[v] = u;
                    u = cur[u] = v;
                    if(v == t){
                        maxflow += aug;
                        for(int v = pre[u];v != s;v = u, u = pre[u]){
                            maze[u][v] -= aug;
                            maze[v][u] += aug;
                        }
                        aug = -1;
                    }
                    goto loop;
                }
        int tp = nodenum - 1;
        for(int v = 0;v < nodenum;++v)
            if(maze[u][v] && tp > dis[v]){
                tp = dis[v];
                cur[u] = v;
            }
        if((--gap[dis[u]]) == 0) break;
        gap[dis[u] = tp + 1]++;
        u = pre[u];
    }
    return maxflow;
}
int main()
{
    int  Case;
    int n, m, f;
    int u, v;
    scanf("%d", &Case);
    while(Case--){
        memset(maze, 0, sizeof(maze));
        scanf("%d %d %d", &n, &m, &f);
        int s = 0, t = 2 * n + 1;
        for(int i = 1;i <= n;++i){
            maze[s][i] = 2*n;
            maze[i][s] = -2*n;
            maze[i+n][t] = 2*n;
            maze[t][i+n] = -2*n;
        }
        while(m--){
            scanf("%d %d", &u, &v);
            maze[u][n+v] = 1;
            maze[v+n][u] = -1;
        }
        while(f--){
            scanf("%d %d", &u, &v);
            maze[u][v] = 1;
            maze[v][u] = -1;
        }
        
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                for(int k = n+1;k <= 2*n;++k){
                    if(maze[i][j] && maze[j][k]){
                        maze[i][k] = 1;
                        maze[k][i] = -1;
                    }
                }
        sap(s, t, 2*n+2);

        int ans = INF;
        for(int i = 1;i <= n;++i)
            if(ans > 2*n-maze[s][i]) ans = 2*n - maze[s][i];
        printf("%d\n", ans);
    }
    return 0;
}