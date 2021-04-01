/*
Time limit:1000ms
Memory limit:32768Kb

Author:buerguoo
Time:TLE
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
const int MAXN = 210;
const int MAXM = 10010;
int head[MAXN], tol;
int dep[MAXN], pre[MAXN], cur[MAXN], gap[MAXN], sta[MAXN];
int F[MAXN], G[MAXN];
struct Edge{
    int to, next, flow, cap;
}E[MAXM];
void init()
{
    tol = 2;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w, int rw = 0)
{
    E[tol].to = v; E[tol].next = head[u]; E[tol].flow = 0;
    E[tol].cap = w; head[u] = tol++;
    E[tol].to = u; E[tol].next = head[v]; E[tol].flow = 0;
    E[tol].cap = rw; head[v] = tol++;
}
int find(int x){
    if(F[x] == -1) return x;
    return F[x] = find(F[x]);
}
void Union(int x1, int x2)
{
    int f1 = find(x1);
    int f2 = find(x2);
    if(f1 != f2)
        F[f1] = f2;
}
/*
int sap(int start, int end, int n)
{
    memset(dep, 0, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    memcpy(cur, head, sizeof(cur));
    gap[0] = n;
    int u = start, maxflow = 0;
    pre[u] = -1;
    while(dep[start] < n){
        if(u == end){
            int Min = INF;
            for(int i = pre[u];i != -1;i = pre[E[i^1].to])
                Min = min(Min, E[i].cap - E[i].flow);
            for(int i = pre[u];i != -1;i = pre[E[i^1].to]){
                E[i].flow += Min;
                E[i^1].flow -= Min;
            }
            maxflow += Min;
            u = start;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u];i != -1;i = E[i].next){
            v = E[i].to;
            if(E[i].cap > E[i].flow && dep[u] == dep[v] + 1){
                flag = true;
                pre[v] = cur[u] = i;
                break;
            }
        }
        if(flag){
            u = v;
            continue;
        }
        int Mindis = n;
        for(int i = head[u];i != -1;i = E[i].next)
        if(E[i].cap > E[i].flow && Mindis > dep[E[i].to]){
            Mindis = dep[E[i].to];
            cur[u] = i;
        }
        if(!(--gap[dep[u]])) return maxflow;
        gap[dep[u] = Mindis+1]++;
        if(u != start) u = E[pre[u]^1].to;
    }   
    return maxflow;
}
*/
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
int mp[125][125];
void build(int k, int n, int s, int t)
{
    init();
    for(int i = 1;i <= n;++i){
        addEdge(s, i, k);
        addEdge(i+n, t, k);
    }
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            if(mp[i][j]) addEdge(i, j+n, 1);
}
int main()
{
    int Case;
    int n, m, f;
    int u, v;
    scanf("%d", &Case);
    while(Case--){
        memset(mp, 0, sizeof(mp));
        memset(F, -1, sizeof(F));
        scanf("%d %d %d", &n, &m, &f);
        int s = 0, t = 2 * n + 1;
        while(m--){
            scanf("%d %d", &u, &v);
            mp[u][v] = 1;
        }
        while(f--){
            scanf("%d %d", &u, &v);
            Union(u, v);
        } 
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(find(i) == find(j))
                    for(int k = 1;k <= n;++k)
                        if(mp[i][k])
                            mp[j][k] = 1;
        int l = 0, h = n, mid, ans;
        while(l <= h){
            mid = (l + h) / 2;
            build(mid, n, s, t);            
            if(mid*n <= dinic(s, t, 2*n+2)){
                ans = mid;   
                l = mid+1;
            }
            else h = mid-1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
