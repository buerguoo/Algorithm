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
int G[MAXN][MAXN];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 
int sap(int s, int t, int nodenum)
{
    memset(dis, 0, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    memset(gap, 0, sizeof(gap));
    int u = pre[s] = s;
    int maxflow = 0, aug = -1;
    gap[0] = nodenum;
    while(dis[s] < nodenum){
        loop:
            for(int v = cur[u];v < nodenum;++v)
                if(G[u][v] && dis[u] == dis[v] + 1){
                    if(aug == -1 || aug > G[u][v]) aug = G[u][v];
                    pre[v] = u;
                    u = cur[u] = v;
                    if(v == t){
                        maxflow += aug;
                        for(u = pre[u];v != s;v = u, u = pre[u]){
                            G[u][v] -= aug;
                            G[v][u] += aug;
                        }
                        aug = -1;
                    }
                    goto loop;
                }
        int mindis = nodenum - 1;
        for(int v = 0;v < nodenum;++v)
            if(G[u][v] && mindis > dis[v]){
                mindis = dis[v];
                cur[u] = v;
            }
        if(--gap[dis[u]] == 0) break;
        gap[dis[u] = mindis+1]++;
        u = pre[u];
    }
    return maxflow;
}
char p[25][25], l[25][25];
int id[25][25], pnum, lnum;
bool judge(int i, int j, int n, int m)
{
    if(i >= 0 && i < n && j >= 0 && j < m) return true;
    
    return false;
}
int main()
{
    int T, n, d, m, kase = 0;
    scanf("%d", &T);
    while(kase < T){
        scanf("%d %d", &n, &d);
        for(int i = 0;i < n;++i)
            scanf("%s", p[i]);
        for(int i = 0;i < n;++i)
            scanf("%s", l[i]);
        m = strlen(p[0]);
        pnum = lnum = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j){
                if(l[i][j] == 'L') lnum++;
                if(p[i][j] - '0') id[i][j] = pnum++; 
            }
        memset(G, 0, sizeof(G));
        int s = 2*pnum, t = 2*pnum+1, N = 2*pnum+2;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j){
                int num = p[i][j];
                if(num){
                    if(l[i][j] == 'L') G[s][id[i][j]] = 1;
                    G[id[i][j]][id[i][j]+pnum] = num;
                    bool flag = false;
                    for(int xd = -d;xd <= d;++xd){
                        for(int yd = abs(xd)-d;yd <= d-abs(xd);++yd){
                            if(judge(i+xd, j+yd, n, m) && p[i+xd][j+yd]-'0')
                                G[pnum+id[i+xd][j+yd]][id[i+xd][j+yd]] = num;
                            if(!judge(i+xd, j+yd, n, m)) flag = true;
                        }
                        if(flag) G[pnum+id[i][j]][t] = num;
                    }
                }
            }
        int left=lnum-sap(s,t,N);//求出最大流 
		if(left==0) printf("Case #%d: no lizard was left behind.\n",++kase);
		else if(left==1) printf("Case #%d: 1 lizard was left behind.\n",++kase);
		else printf("Case #%d: %d lizards were left behind.\n",++kase,left);
    }
    return 0;
}