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
const int MAXN = 10010;
const int MAXM = 100010;
int dis[MAXN], cur[MAXN], pre[MAXN], gap[MAXN];
int maze[MAXN][MAXN];
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
int main()
{
    int n, m;
    char p[8];
    while(~scanf("%d %d", &n, &m)){
        
    }
    return 0;
}