/*
Author:buerguoo
Time:16ms
memory:156kB

Data:2021-03-16 21:55:57
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 510;
const int MAXM = 5100;
int head[MAXN], tol;
int dep[MAXN], sta[MAXN], cur[MAXN];
int G[MAXN];
struct Edge
{
    int to, next, flow, cap;
}E[MAXM];
void addEdge(int u, int v, int w, int rw = 0){
    E[tol].to = v; E[tol].cap = w; E[tol].flow = 0;
    E[tol].next = head[u]; head[u] = tol++;
    E[tol].to = u; E[tol].cap = rw; E[tol].flow = 0;
    E[tol].next = head[v]; head[v] = tol++;
}
void init()
{
    tol  = 2;
    memset(head, -1, sizeof(head));
}
bool bfs(int s, int t, int n){
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    int front = 0, tail = 0;
    G[tail++] = s;
    while(front < tail){
        int u = G[front++];
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(dep[v] == -1 && E[i].cap > E[i].flow)
            {
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                G[tail++] = v;
            }
        }
    }
    return false;
}
int dinic(int s, int t, int n){
    int maxflow = 0;
    while(bfs(s, t, n)){
        int u = s, tail = 0;
        for(int i = 0;i < n;++i) cur[i] = head[i];
        while(cur[s] != -1){
            if(u == t){
                int tp = INF;
                for(int i = tail-1;i >= 0;--i)
                    tp = min(tp, E[sta[i]].cap-E[sta[i]].flow);
                maxflow += tp;
                for(int i = tail-1;i >= 0;--i){
                    E[sta[i]].flow += tp;
                    E[sta[i]^1].flow -= tp;
                    if(E[sta[i]].cap - E[sta[i]].flow == 0)
                        tail = i;
                }
                u = E[sta[tail]^1].to;
            }else if(cur[u] != -1 && E[cur[u]].cap > E[cur[u]].flow &&
                dep[u] + 1 == dep[E[cur[u]].to]){
                    sta[tail++] = cur[u];
                    u = E[cur[u]].to;
            }else{
                while(u != s && cur[u] == -1)
                    u = E[sta[--tail]^1].to;
                cur[u] = E[cur[u]].next;
            }
        }
    }
    return maxflow;
}
int main()
{
    int N, F, D;
    while(~scanf("%d %d %d", &N, &F, &D)){
        init();
        int s = 0, t = 2*N+2+F+D;
        for(int i = 1;i <= F;++i)   addEdge(s, i, 1);
        for(int i = F+2*N+1;i < t;++i)  addEdge(i, t-1, 1);
        for(int i = F+1;i <= F+N;++i)   addEdge(i, i+N, 1);
        int n, m, f, d;
        for(int i = 1;i <= N;++i){
            scanf("%d %d", &n, &m);
            while(n--){
                scanf("%d", &f);
                addEdge(f, i+F, 1);
            }
            while(m--){
                scanf("%d", &d);
                addEdge(F+N+i, F+2*N+d, 1);
            }
        }
        printf("%d\n", dinic(s, t-1, t));
    }
    return 0;
}
