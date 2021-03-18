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
//最小费用最大流,使用spfa
//TLE
const int INF = 0x3f3f3f3f;
const int MAXN = 110;
const int MAXM = 110;
int dis[MAXN], vis[MAXN], pre[MAXN];
int head[MAXN], tol;
char mp[MAXN][MAXN];
int N;
struct Edge
{
    int to, next, flow, cap, cost;
}E[MAXM];
struct Point{
    int x, y;
}H[MAXN], M[MAXN];
void addEdge(int u, int v, int w, int cost){
    E[tol].to = v; E[tol].cap = w; E[tol].flow = 0; E[tol].cost = cost;
    E[tol].next = head[u]; head[u] = tol++;
    E[tol].to = u; E[tol].cap = 0; E[tol].flow = 0; E[tol].cost = -cost;
    E[tol].next = head[v]; head[v] = tol++;
}
void init()
{
    tol  = 2;
    memset(head, -1, sizeof(head));
}
bool spfa(int s, int t){
   queue<int> q;
   for(int i = 0;i < N;++i){
       dis[i] = INF;
       vis[i] = false;
       pre[i] = -1;
   }
   vis[s] = true;
   dis[s] = 0;
   q.push(s);
   while(!q.empty()){
       int u = q.front();
       q.pop();
       for(int i = head[u];i != -1;i = E[i].next){
           int v = E[i].to;
           if(E[i].cap > E[i].flow && dis[v] > dis[u] + E[i].cost){
               dis[v] = dis[u] + E[i].cost;
               pre[v] = i;
               if(!vis[v]){
                   vis[v] = true;
                   q.push(v);
               }
           }
       }
   }
   if(pre[t] == -1) return false;
   return true;
}
int minCostMaxFlow(int s, int t, int &cost)
{
    int maxflow = 0;
    while(spfa(s, t)){
        int tp = INF;
        for(int i = pre[t];i != -1;i = pre[E[i^1].to])
            tp = min(tp, E[i].cap-E[i].flow);
        for(int i = pre[t];i != -1;i = pre[E[i^1].to]){
            E[i].flow += tp;
            E[i^1].flow -= tp;
            cost += tp*E[i].cost;
        }
        maxflow += tp;
    }
    return maxflow;
}
int dist(Point a, Point b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}
int main()
{
    int n, m, c1, c2;
    while(~scanf("%d %d", &n, &m) && (n || m)){
        init();
        for(int i = 0;i < n;++i)
            scanf("%s", mp[i]);
        c1 = 0;
        c2 = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j){
                if(mp[i][j] == 'H'){
                    H[c1].x = i; H[c1++].y = j;
                }else if(mp[i][j] == 'm'){
                    M[c2].x = i; M[c2++].y = j;
                }
            }
        N = c1;
        int s = 0, t = 2*N+1;
        for(int i = 0;i < c1;++i)
            for(int j = 0;j < c2;++j)
                addEdge(i+1, N+j+1, 1, dist(H[i], M[j]));  
        for(int i = 0;i < N;++i) addEdge(s, i+1, 1, 0);
        for(int i = 0;i < N;++i) addEdge(N+1+i, t, 1, 0);
        N = 2*N+2;
        int cost = 0;
        minCostMaxFlow(s, t, cost);
        printf("%d\n", cost);
    }
    return 0;
}