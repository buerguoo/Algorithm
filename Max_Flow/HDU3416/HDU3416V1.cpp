/*
Time limit:1000ms
Memory limit:32768KB

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
const int MAXN = 1010;
const int MAXM = 100010;
int d[2][MAXN], vis[MAXN];
int head[MAXN], tol, tt, h[MAXN];
int gap[MAXN], dep[MAXN], cur[MAXN], pre[MAXN];
int N;
struct Edge{
    int to, next, flow, cap;
    Edge(){}
    Edge(int _t, int _n, int _f, int _c):to(_t), next(_n), flow(_f), cap(_c){}
}E[MAXM], e[MAXM];
void init()
{
    tol = 2;
    tt = 0;
    memset(head, -1, sizeof(head));
    memset(h, -1, sizeof(h));
}
void addEdge(int u, int v, int w, int tag, int rw = 0)
{
    if(!tag){
        e[tt] = Edge(v, h[u], 0, w);
        h[u] = tt++;
    }else{
        E[tol] = Edge(v, head[u], 0, w);
        head[u] = tol++;
        E[tol] = Edge(u, head[v], 0, rw);
        head[v] = tol++;
    }
    
}
void spfa(int s, int t, int k)
{
    for(int i = 1;i <= N;++i){
        vis[i] = false;
        d[k][i] = INF;
    }
    queue<int> Q;
    d[k][s] = 0;
    Q.push(s);
    vis[s] = true;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = h[u];i != -1;i = e[i].next)
        {
            int v = e[i].to;
            if(d[k][v] > d[k][u] + e[i].cap){
                d[k][v] = d[k][u] + e[i].cap;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
}

int sap(int s, int t, int nodenum)
{
    int maxflow = 0;
    memset(gap, 0, sizeof(gap));
    memset(dep, 0, sizeof(dep));
    memcpy(cur, head, sizeof(cur));
    gap[0] = nodenum;
    int u = s;
    pre[u] = -1;
    while(dep[s] < nodenum){
        if(u == t){
            int Min = INF;
            for(int i = pre[u];i != -1;i = pre[E[i^1].to])
                Min = min(Min, E[i].cap - E[i].flow);
            maxflow += Min;
            for(int i = pre[u];i != -1;i = pre[E[i^1].to]){
                E[i].flow += Min;
                E[i^1].flow -= Min;
            }
            u = s;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u];i != -1;i = E[i].next){
            v = E[i].to;
            if(E[i].cap > E[i].flow && dep[v] + 1 == dep[u]){
                pre[v] = cur[u] = i;
                flag = true;
                break;
            }
        }
        if(flag){
            u = v;
            continue;
        }
        int Mindis = nodenum;
        for(int i = head[u];i != -1;i = E[i].next)
            if(E[i].cap > E[i].flow && Mindis > dep[E[i].to])
            {
                Mindis = dep[E[i].to];
                cur[u] = i;
            }
        if(!(--gap[dep[u]])) return maxflow;
        gap[dep[u] = Mindis + 1]++;
        if(u != s) u = E[pre[u]^1].to;
    }
    return maxflow;
}
int t1[MAXN], t2[MAXN], t3[MAXN];
int main()
{
    int T;
    int n, m, w, u, v;
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d %d", &n, &m);
        N = n;
        for(int i = 0;i < m;++i){
            scanf("%d %d %d", &t1[i], &t2[i], &t3[i]);
            addEdge(t1[i], t2[i], t3[i], 0);
        }
        int s, t;
        scanf("%d %d", &s, &t);
        spfa(s, t, 0);
        init();
        for(int i = 0;i < m;++i) addEdge(t2[i], t1[i], t3[i], 0);
        spfa(t, s, 1);
        for(int i = 0;i < m;++i)
            if(d[0][t1[i]] + d[1][t2[i]] + t3[i] == d[0][t])
                addEdge(t1[i], t2[i], 1, 1);
        printf("%d\n", sap(s, t, n));
    }
    return 0;
}