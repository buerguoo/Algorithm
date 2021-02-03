/*
Author:buerguoo
Time:
memory:176kB

Data:2021-02-03 19:30:56
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
const int MAXN = 5010;
const int MAXM = 10010*2;
//含桥图，变为双连通图
//把双连通子图收缩为一棵树，需要加的边为(left+1)/2
int head[MAXN], DFN[MAXN], Low[MAXN], Belong[MAXN], du[MAXN], Stack[MAXN];
int bridge, Index, top, block, tol;
bool Instack[MAXN];
struct Edge{
    int to, next;
    bool cut;
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v, E[tol].cut = false;
    E[tol].next = head[u], head[u] = tol++;
}
void Tarjan(int u, int pre)
{
    int v;
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    int pre_cnt = 0;
    for(int i = head[u];i != -1;i = E[i].next)
    {
        v = E[i].to;
        if(v == pre && pre_cnt == 0){pre_cnt++; continue;}
        if(!DFN[v]){
            Tarjan(v, u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            //桥
            if(Low[v] > DFN[u]){
                bridge++;
                E[i].cut = true;
                E[i^1].cut = true;
            }
        }
        else if(Instack[v] && Low[u] > DFN[v])  Low[u] = DFN[v];
    }
    if(DFN[u] == Low[u]){
        block++;
        do{
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = block;
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
    memset(Instack, false, sizeof(Instack));
    top = Index = 0;
    bridge = 0;
    Tarjan(1, 0);
    int ans = 0;
    memset(du, 0, sizeof(du));
    for(int i = 1;i <= N;++i)
        for(int j = head[i];j != -1;j = E[j].next)
            if(E[j].cut)
                du[Belong[i]]++;
    for(int i = 1;i <= block;++i)
        if(du[i] == 1)
            ans++;
    printf("%d\n", (ans+1)/2);
}
int main()
{
    int N, M;
    int u, v;
    while(~scanf("%d %d", &N, &M)){
        init();
        while(M--){
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        solve(N);
    }
    return 0;
}