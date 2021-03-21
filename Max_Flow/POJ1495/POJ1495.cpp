/*
Author:buerguoo
Time:110ms
memory:420kB

Data:2021-03-21 23:12:08
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
const int MAXM = 20100;
int dep[MAXN], sta[MAXN], cur[MAXN];
int head[MAXN], tol;
int Q[MAXN];
struct Edge{
    int to, next, cap, flow;
    Edge(int _t = 0, int _n = 0, int _c = 0, int _f = 0):
        to(_t), next(_n), cap(_c), flow(_f){}
}E[MAXM];
void init(){
    tol = 2;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w, int rw=0){
    E[tol] = Edge(v, head[u], w, 0);
    head[u] = tol++;
    E[tol] = Edge(u, head[v], rw, 0);
    head[v] = tol++;
}
bool bfs(int s, int t)
{
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    int front = 0, tail = 0;
    Q[tail++] = s;
    while(front < tail){
        int u = Q[front++];
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(dep[v] == -1 && E[i].cap > E[i].flow){
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                //printf("%d\n", v);
                Q[tail++] = v;
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
        int u = s, tail = 0;
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
            }else if(dep[u] != -1 && dep[u] + 1 == dep[E[cur[u]].to] && 
                E[cur[u]].cap > E[cur[u]].flow){
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
    int n, np, nc, m;
    while(~scanf("%d %d %d %d", &n, &np, &nc, &m)){
        int u, v, w;
        init();
        int s = 0, t = n + 1;
        while(m--){
            while(getchar() != '(');
            scanf("%d,%d)%d", &u, &v, &w);
            if(u == v) continue;
            u++; v++;
            addEdge(u, v, w);
        }
        while(np--){
            while(getchar() != '(');
            scanf("%d)%d", &u, &w);
            u++;
            addEdge(s, u, w);
            //addEdge(u, u+n, w);
        }
        while(nc--){
            while(getchar() != '(');
            scanf("%d)%d", &u, &w);
            u++;
            addEdge(u, t, w);
           // addEdge(u, u+n, w);
        }
        printf("%d\n", dinic(s, t, n+2));
    }
    return 0;
}