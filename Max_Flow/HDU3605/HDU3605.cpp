/*
Time limit:2000ms
Memory limit:65536KB

Author:buerguoo
Time:1310ms
memory:3396Kb

Data:2021-03-30 23:11:02
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
int head[MAXN], tol;
int dep[MAXN], cur[MAXN], sta[MAXN];
int G[MAXN];
int state[1030];
struct Edge{
    int to, next, flow, cap;
    Edge(int _t=0, int _n=0, int _f=0, int _c=0):to(_t), next(_n), flow(_f), cap(_c){}
}E[MAXM];
void init()
{
    tol = 2;
    memset(head, -1, sizeof(head));
    memset(state, 0, sizeof(state));
}
void addEdge(int u, int v, int w, int rw = 0)
{
    E[tol] = Edge(v, head[u], 0, w);
    head[u] = tol++;
    E[tol] = Edge(u, head[v], 0, rw);
    head[v] = tol++;
}
bool bfs(int s, int t)
{
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    int front = 0, tail = 0;
    G[tail++] = s;
    while(front < tail){
        int u = G[front++];
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(dep[v] == -1 && E[i].cap > E[i].flow){
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                G[tail++] = v;
            }
        }
    }
    return false;
}
int dinic(int s, int t, int n)
{
    int maxflow = 0;
    while(bfs(s, t)){
        for(int i = 0;i < n;++i) cur[i] = head[i];
        int tail = 0, u = s;
        while(cur[s] != -1)
        {
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
            }else if(cur[u] != -1 && dep[u] + 1 == dep[E[cur[u]].to] 
            && E[cur[u]].cap > E[cur[u]].flow){
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
    int n, m, c;
    while(~scanf("%d %d", &n, &m)){
        init();
        int s = 0, t = n + m + 1;
        for(int i = 0;i < n;++i){
            int tp = 0;
            for(int j = 0;j < m;++j){
                scanf("%d", &c);
                if(c == 1) tp |= (1<<j);
            }
            state[tp]++;
        }
        int sz = 0;
        for(int i = 0;i < (1<<(m));++i){
            int len = state[i];
            if(len == 0) continue;
            addEdge(s, ++sz, len);
        }
        t = sz + m + 1;
        int tp = 0;
        for(int i = 0;i < (1<<(m));++i){
            int len = state[i];
            if(len == 0) continue;
            ++tp;
            for(int j = 0;j < m;++j)
                if(i&(1<<j))    addEdge(tp, sz+j+1, len);
        }
        for(int i = 1;i <= m;++i){
            scanf("%d", &c);
            addEdge(i+sz, t, c);
        }
        int res = dinic(s, t, sz+m+2);
        if(res < n) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}