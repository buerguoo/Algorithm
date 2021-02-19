/*
Author:buerguoo
Time:
memory:

Data:
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
const int MAXN = 10010;
const int MAXM = 100010;
int DFN[MAXN], Low[MAXN], head[MAXN], Belong[MAXN], ru[MAXN], chu[MAXN], Stack[MAXN], num[MAXN];
bool Instack[MAXN];
int Index, top, tol, scc, m;
struct Edge{
    int to, next;
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v, E[tol].next = head[u];
    head[u] = tol++;
}
void Tarjan(int u)
{
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    int v;
    for(int i = head[u];i != -1;i = E[i].next){
        v = E[i].to;
        if(!DFN[v]){
            Tarjan(v);
            Low[u] = min(Low[u], Low[v]);
        }else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(DFN[u] == Low[u]){
        scc++;
        do{
            v = Stack[--top];
            Instack[v] = false;
            num[scc]++;
            Belong[v] = scc;
        }while(v != u);
    }
}
void init()
{
    memset(head, -1, sizeof(head));
    tol = 0;
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false ,sizeof(Instack));
    memset(num, 0, sizeof(num));
    Index = top = scc = 0;
    for(int i = 1;i <= N;++i)
        if(!DFN[i])
            Tarjan(i);
}
int main()
{
    int Case;
    int n;
    int u, v;
    scanf("%d", &Case);
    for(int cas = 1;cas <= Case;++cas){
        scanf("%d %d", &n, &m);
        init();
        for(int i = 0;i < m;++i){
            scanf("%d %d", &u, &v);
            addEdge(u, v);
        }
        solve(n);
        if(scc == 1){
            printf("Case %d: -1\n", cas);
            continue;
        }
        memset(ru, 0, sizeof(ru));
        memset(chu, 0, sizeof(chu));
        int ans = -1, v;
        for(int i = 1;i <= n;++i)
            for(int j = head[i];j != -1;j = E[j].next){
                v = E[j].to;
                if(Belong[v] != Belong[i]){
                    chu[Belong[i]]++;
                    ru[Belong[v]]++;
                }
            }
        for(int i = 1;i <= scc;++i)
            if(!ru[i] || !chu[i])
                ans = max(ans, n*(n-1)-m-num[i]*(n-num[i]));
        printf("Case %d: %d\n", cas, ans);
    }
    return 0;
}