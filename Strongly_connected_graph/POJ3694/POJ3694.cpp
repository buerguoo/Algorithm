/*
Author:buerguoo
Time:454ms
memory:8764kB

Data:2021-01-31 19:33:37
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
const int MAXN = 100100;
const int MAXM = 200100*2;
int head[MAXN], DFN[MAXN], Low[MAXN], Stack[MAXN], pren[MAXN];
bool Insatck[MAXN];
int Index, bridge, tol, top;    
int F[MAXN];
struct Edge{
    int to, next;
    bool cut;
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v, E[tol].cut = false;
    E[tol].next = head[u], head[u] = tol++;
}
void init()
{
    memset(F, -1, sizeof(F));
    memset(head, -1, sizeof(head));
    tol = 0;
    //pren[1] = 1;
}
int find(int x)
{
    if(F[x] == -1) return x;
    return F[x] = find(F[x]);
}
bool Union(int a, int b)
{
    int x1 = find(a);
    int x2 = find(b);
    if(x1 == x2) return false;
    F[x2] = x1;
    return true;
}
void Tarjan(int u, int pre)
{
    DFN[u] = Low[u] = Index++;
    Stack[top++] = u;
    Insatck[u] = true;
    int v;
    for(int i = head[u];i != -1;i = E[i].next){
        v = E[i].to;
        if(v == pre) continue;
        if(!DFN[v]){
            pren[v] = u;
            Tarjan(v, u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            //ге
            if(Low[v] > DFN[u]){
                bridge++;
                E[i].cut = true;
                E[i^1].cut = true;
            }
            else{
                Union(u, v);
            }
        }
        else if(Low[u] > DFN[v]) Low[u] = DFN[v];
    }
    Insatck[u] = false;
    top--;
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Insatck, false, sizeof(Insatck));
    Index = top = 0;
    bridge = 0;
    for(int i = 1;i <= N;i++)
        if(!DFN[i])
            Tarjan(i, i);
}

int LCA(int u, int v)
{
    if(find(u) == find(v)) return bridge;
    if(DFN[u] > DFN[v]) swap(u, v);
    while(DFN[v] > DFN[u]){
        if(Union(pren[v], v))
            bridge--;
        v = pren[v];
    }
    while(u != v){
        if(Union(pren[u], u))
            bridge--;
        u = pren[u];
    }

    return bridge;
}
int main()
{
    int N, M, Q;
    int u, v;
    int Case = 0;
    while(~scanf("%d %d", &N, &M) && N){
        init();
        while(M--){
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        solve(N);
        scanf("%d", &Q);
        printf("Case %d:\n", ++Case);
        for(int i = 0;i < Q;++i){
            scanf("%d %d", &u, &v);
            printf("%d\n", LCA(u, v));
        }
    }
    return 0;
}