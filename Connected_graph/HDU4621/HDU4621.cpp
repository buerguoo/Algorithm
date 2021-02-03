/*
Author:buerguoo
Time:1201ms
memory:25272kB

Data:2021-02-03 21:43:35
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
const int MAXN = 200100;
const int MAXM = 1000000;
//并查集缩点+树的直径
int head[MAXN], DFN[MAXN], Low[MAXN], F[MAXN], dis[MAXN];
int Index, bridge, tol;
bool vis[MAXN];
struct Edge{
    int to, next;
}E[MAXM*2+100];
void addEdge(int u, int v){
    E[tol].to = v;
    E[tol].next = head[u], head[u] = tol++;
}
int find(int x)
{
    if(F[x] == -1) return x;
    return F[x] = find(F[x]);
}
void Union(int a, int b)
{
    int x1 = find(a);
    int x2 = find(b);
    if(x1 != x2)
        F[x2] = x1;
}
void Tarjan(int u, int pre)
{
    DFN[u] = Low[u] = ++Index;
    int v;
    int pre_cnt = 0; //处理重边
    for(int i = head[u];i != -1;i = E[i].next){
        v = E[i].to;
        if(v == pre && pre_cnt == 0){pre_cnt++; continue;}
        if(!DFN[v]){
            Tarjan(v, u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            if(Low[v] > DFN[u]) bridge++;
            else Union(u, v);
        }else if(Low[u] > DFN[v]) Low[u] = DFN[v];
    }
}
void init()
{
    memset(head, -1, sizeof(head));
    tol = 0;
}
void bfs(int u)
{
    queue<int> Q;
    while(!Q.empty())   Q.pop();
    Q.push(u);
    vis[u] = true;
    dis[u] = 0;
    while(!Q.empty()){
        int q = Q.front();
        Q.pop();
        for(int i = head[q];i != -1;i = E[i].next){
            int v = E[i].to;
            if(!vis[v]){
                if(find(q) == find(v))  dis[v] = dis[q];
                else dis[v] = dis[q] + 1;
                vis[v] = true;
                Q.push(v);
            }
        }
    }
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(F, -1, sizeof(F));
    Index = bridge = 0;
    memset(dis, 0, sizeof(dis));
    memset(vis, false, sizeof(vis));
    Tarjan(1, 0);
    int MAX = 0, pos = 1;
    bfs(1);
    for(int i = 1;i <= N;++i)
        if(MAX < dis[i]){
            MAX = dis[i];
            pos = i;
        }
    MAX = 0;
    memset(dis, 0, sizeof(dis));
    memset(vis, false, sizeof(vis));
    bfs(pos);
    for(int i = 1;i <= N;++i)
        if(MAX < dis[i])
            MAX = dis[i];
    printf("%d\n", bridge-MAX);
}
int main()
{
    int N, M;
    int u, v;
    while(~scanf("%d %d", &N, &M) && N){
        init();
        while (M--)
        {
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        solve(N);
    }
    return 0;
}