/*
Author:buerguoo
Time:16ms
memory:108kB

Data:2021-03-15 21:30:35s
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
const int MAXN = 55;
const int MAXP = 15;
const int INF = 0x3f3f3f3f;
const int MAXM = 100010;
int input[MAXP][MAXN], output[MAXP][MAXN], w[MAXN];
int head[MAXN], tol;
int dep[MAXN], cur[MAXN], sta[MAXN], Q[MAXN];
struct Edge{
    int to, next, flow, cap;
}E[MAXM];
void init(){
    tol = 2;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w, int rw = 0){
    E[tol].to = v; E[tol].cap = w; E[tol].flow = 0;
    E[tol].next = head[u]; head[u] = tol++;

    E[tol].to = u; E[tol].cap = rw; E[tol].flow = 0;
    E[tol].next = head[v]; head[v] = tol++;
}
bool bfs(int s, int t, int n){
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    int front = 0, tail = 0;
    Q[tail++] = s;
    while (front < tail)
    {
        int u = Q[front++];
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(dep[v] == -1 && E[i].cap > E[i].flow){
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                Q[tail++] = v;
            }
        }
    }
    return false;
}
int dinic(int s, int t, int n){
    int maxflow = 0;
    while(bfs(s, t, n)){
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
            }else if(cur[u] != -1 && dep[u] + 1 == dep[E[cur[u]].to]&& 
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
void solve(int s, int t, int n){
    int res = 0;
    int maxflow = dinic(s, t, n);
    for(int i = 1;i < n;++i)
        for(int j = head[i];j != -1;j = E[j].next)
            if(E[j].flow > 0 && E[j].to > 0 && E[j].to < n-1)
                res++;
    printf("%d %d\n", maxflow, res);
    for(int i = 1;i < n;++i)
        for(int j = head[i];j != -1;j = E[j].next)
            if(E[j].flow > 0 && E[j].to > 0 && E[j].to < n-1)
                printf("%d %d %d\n", i, E[j].to, E[j].flow);
}
int main()
{
    int P, N;
    int s, t;
    init();
    scanf("%d %d", &P, &N);
    for(int i = 1;i <= N;++i){
        scanf("%d", &w[i]);
        for(int j = 1;j <= P;++j)
            scanf("%d", &input[i][j]);
        for(int j = 1;j <= P;++j)
            scanf("%d", &output[i][j]);
    }
    s = 0, t = N+1;
    for(int i = 1;i <= N;++i){
        bool flag1 = true, flag2 = true;
        for(int j = 1;j <= P;++j){
            if(input[i][j] == 1) flag1 = false;
            if(output[i][j] == 0) flag2 = false;
        }
        if(flag1) addEdge(s, i, w[i]);
        if(flag2) addEdge(i, t, w[i]);
        for(int j = 1;j <= N;++j){
            bool flag = false;
            for(int k = 1;k <= P;++k){
                if(input[i][k] + output[j][k] == 1)
                    flag = true;
            }
            if(!flag) addEdge(j, i, min(w[j], w[i]));
        }
    }
    solve(s, t, N+2);

    return 0;
}