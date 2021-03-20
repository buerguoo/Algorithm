/*
Author:buerguoo
Time:438ms
memory:392kB

Data:2021-03-20 18:02:20
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
const int MAXN = 110;
const int MAXM = 10100;
//zkw费用流
int dis[MAXN], cur[MAXN];
bool vis[MAXN];
int head[MAXN], tol;
int ss, tt, N, F[MAXN], Q[MAXN];
struct Edge{
    int to, next, cost, cap, flow;
    Edge(int _t=0, int _n=0, int _cost=0, int _cap=0, int _f=0): to(_t), next(_n), 
        cost(_cost), cap(_cap), flow(_f){}

};
Edge E[MAXM];
void init()
{
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w, int cost)
{
    E[tol] = Edge(v, head[u], cost, w, 0);
    head[u] = tol++;
    E[tol] = Edge(u, head[v], -cost, 0, 0);
    head[v] = tol++;
}
int aug(int u, int flow){
    if(u == tt) return flow;
    vis[u] = true;
    for(int i = cur[u];i != -1;i = E[i].next){
        int v = E[i].to;
        if(!vis[v] && E[i].cap > E[i].flow && dis[u] == dis[v] + E[i].cost){
            int tp = aug(v, min(flow, E[i].cap-E[i].flow));
            E[i].flow += tp;
            E[i^1].flow -= tp;
            cur[u] = i;
            if(tp) return tp;
        }
    }
    return 0;
}
bool modify_lable()
{
    int d = INF;
    for(int u = 0;u < N;++u)
        if(vis[u])
            for(int i = head[u];i != -1;i = E[i].next){
                int v = E[i].to;
                if(!vis[v] && E[i].cap > E[i].flow){
                    d = min(d, dis[v]+E[i].cost-dis[u]);
                }
            }
    if(d == INF) return false;
    for(int i = 0;i < N;++i)
        if(vis[i]){
            dis[i] += d;
            vis[i] = false;
        }
    
    return true;
}
pair<int, int> zkw(int s, int t, int n){
    ss = s, tt = t, N = n;
    int maxflow = 0, maxcost = 0;
    for(int i = 0;i < n;++i) dis[i] = 0;
    while(1){
        for(int i = 0;i < n;++i) cur[i] = head[i];
        while(1){
            for(int i = 0;i < n;++i) vis[i] = false;
            int tmp = aug(s, INF);
            if(tmp == 0) break;
            maxflow += tmp;
            maxcost += tmp * dis[ss];
        }
        if(!modify_lable()) break;
    }
    return make_pair(maxflow, maxcost);
}
int supply[MAXN][MAXN], shopkeepers[MAXN][MAXN];
int main()
{
    int n, m, k, res;
    bool flag;
    while(~scanf("%d %d %d", &n, &m, &k) && (n || m || k)){
        memset(F, 0, sizeof(F));
        memset(Q, 0, sizeof(Q));
        int s = 0, t = m+n+1;
        flag = false;
        res = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < k;++j){
                scanf("%d", &shopkeepers[i][j]);
                F[j] += shopkeepers[i][j];
            }
        for(int i = 0;i < m;++i)
            for(int j = 0;j < k;++j){
                scanf("%d", &supply[i][j]);
                Q[j] += supply[i][j];
            }
        int cost = 0;
        for(int p = 0;p < k;++p){
            init();
            for(int i = 0;i < m;++i)    addEdge(s, i+1, supply[i][p], 0);
            for(int i = 0;i < n;++i)
                for(int j = 0;j < m;++j){
                    scanf("%d", &cost);
                    addEdge(j+1, i+m+1, supply[j][p], cost);
                }
            for(int j = 0;j < n;++j)
                addEdge(j+m+1, t, shopkeepers[j][p], 0);
            pair<int, int> tp = zkw(s, t, m+n+2);
            if(tp.first < F[p] || Q[p] < F[p]) flag = true;
            res += tp.second;
        }
        if(flag) printf("-1\n");
        else printf("%d\n", res);
    }
    return 0;
}