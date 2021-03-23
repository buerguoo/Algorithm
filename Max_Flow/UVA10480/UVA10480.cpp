    /*
    Time limit:3000ms
    Memory limit:

    Author:buerguoo
    Time:
    memory:

    Data:2021-03-23 19:12:46
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
    const int MAXN = 60;
    const int MAXM = 1010;
    int head[MAXN], tol;
    int dep[MAXN], cur[MAXN], sta[MAXN];
    int G[MAXN];
    bool vis[MAXN];
    struct Edge{
        int to, next, cap, flow;
        Edge(int _t=0, int _n=0, int _c=0, int _f=0):to(_t), next(_n), cap(_c), flow(_f){}
    }E[MAXM];
    void init()
    {
        tol = 2;
        memset(head, -1, sizeof(head));
        memset(vis, false, sizeof(vis));
    }
    void addEdge(int u, int v, int w, int rw = 0){
        E[tol] = Edge(v, head[u], w, 0);
        head[u] = tol++;
        //E[tol] = Edge(u, head[v], rw, 0);
        //head[v] = tol++;
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
            for(int i = 1;i <= n;++i) cur[i] = head[i];
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
                }else if(cur[u] != -1 && dep[u] + 1 == dep[E[cur[u]].to] && 
                E[cur[u]].cap > E[cur[u]].flow){
                    sta[tail++] = cur[u];
                    u = E[cur[u]].to;
                }else {
                    while(u != s && cur[u] == -1)
                        u = E[sta[--tail]^1].to;
                    cur[u] = E[cur[u]].next;
                }
            }
        }
        return maxflow;
    }
    void dfs(int u)
    {
        vis[u] = true;
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(vis[v] || E[i].cap <= E[i].flow) continue;
            dfs(v);
        }
    }
    void solve(int s, int t, int n)
    {
        dinic(s, t, n);
        dfs(s);
        for(int u = 1;u <= n;++u)
            for(int i = head[u];i != -1;i = E[i].next)  if(i % 2)
            {
                int v = E[i].to;
                if((!vis[u] && vis[v]) || (vis[u] && !vis[v]))
                    printf("%d %d\n", u, v);
            }
        printf("\n");
    }
    int main()
    {
        int n, m, u, v, w;
        while(~scanf("%d %d", &n, &m) && (n || m)){
            init();
            while(m--){
                scanf("%d %d %d", &u, &v, &w);
                addEdge(u, v, w);
                addEdge(v, u, w);
            }
            solve(1, 2, n);
        }
        return 0;
    }