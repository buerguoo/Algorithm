/*
Author:buerguoo
Time:16ms
memory:128KB

Data:2021-01-17 19:19:06
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
#define FILL(a, b)  memset(a, b, sizeof(a))
typedef long long ll;
const int MAXN = 105;
const int MAXM = MAXN*MAXN;
const int INF = 0x3f3f3f3f;
int Index, scc, top, tol;
int DFN[MAXN], Low[MAXN], Belong[MAXN], Stack[MAXN], head[MAXN];
bool Instactk[MAXN];
int cd[MAXN], rd[MAXN];
struct Edge{
    int to, next;
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v;
    E[tol].next = head[u];
    head[u] = tol++;
}
void Tarjan(int u)
{
    int v;
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instactk[u] = true;
    for(int i = head[u];i != -1;i = E[i].next)
    {
        v = E[i].to;
        if(!DFN[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }
        else if(Instactk[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u]){
        scc++;
        do{
            v = Stack[--top];
            Instactk[v] = false;
            Belong[v] = scc;
        }
        while(v != u);
    }
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instactk, false, sizeof(Instactk));
    scc = Index = top = 0;
    for(int i = 1;i <= N;++i) if(!DFN[i])
        Tarjan(i);
}
void init(){
    memset(head, -1, sizeof(head));
    tol = 0;
}
int main()
{
    int N, v;
    scanf("%d", &N);
    init();
    for(int i = 1;i <= N;++i)
    {
        while(scanf("%d", &v) && v)
            addEdge(i, v);
    }
    solve(N);
    int ans1 = 0, ans2 = 0;
    for(int u = 1;u <= N;++u){
        for(int i = head[u];i != -1;i = E[i].next){
            v = E[i].to;
            if(Belong[u] != Belong[v]){
                cd[Belong[u]]++;
                rd[Belong[v]]++;
            }
        }
    }
    for(int i = 1;i <= scc;++i) if(cd[i] == 0)
        ans1++;
    for(int i = 1;i <= scc;++i) if(rd[i] == 0)
        ans2++;
    if(scc == 1)    printf("1\n0\n");
    else printf("%d\n%d\n", ans2, max(ans1, ans2));
    return 0;
}