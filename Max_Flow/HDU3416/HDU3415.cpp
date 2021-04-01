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
int dis[MAXN], pre[MAXN], vis[MAXN];
int head[MAXN], tol;
struct Edge{
    int to, next, flow, cost, cap;
}E[MAXM];
void init()
{
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w, int c)
{
    E[tol].to = v; E[tol].next = head[u]; E[tol].cap = w;
    E[tol].cost = c; E[tol].flow = 0; head[u] = tol++;
    E[tol].to = u; E[tol].next = head[v]; E[tol].cap = 0;
    E[tol].cost = -c; E[tol].flow = 0; head[v] = tol++;
}
bool spfa(int s, int t, int N)
{
    for(int i = 1;i <= N;++i){
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    queue<int> Q;
    dis[s] = 0;
    vis[s] = true;
    Q.push(s);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(E[i].cap > E[i].flow && dis[u] + E[i].cost < dis[v]){
                dis[v] = E[i].cost + dis[u];
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1) return false;
    return true;
}
int maxMatch(int s, int t, int N)
{
    int maxflow = 0;
    while(spfa(s, t, N)){
        int Min = INF;
        for(int i = pre[t];i != -1;i = pre[E[i^1].to])
            Min = min(Min, E[i].cap - E[i].flow);
        for(int i = pre[t];i != -1;i = pre[E[i^1].to]){
            E[i].flow += Min;
            E[i^1].flow -= Min;
        }
        maxflow += Min;
    }
    return maxflow;
}
int main()
{
    int T;
    int n, m, w, u, v;
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d %d", &n, &m);
        while(m--){
            scanf("%d %d %d", &u, &v, &w);
            if(u != v)
                addEdge(u, v, 1, w);
        }
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%d\n", maxMatch(s, t, n));
    }
    return 0;
}