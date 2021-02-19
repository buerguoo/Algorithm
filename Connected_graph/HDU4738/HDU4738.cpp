/*
Author:buerguoo
Time:109ms
memory:6012KB

Data:2021-02-19 21:54:59
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
const int MAXN = 1010;
const int MAXM = MAXN*MAXN;
const int INF = 0x3f3f3f;
int DFN[MAXN], Low[MAXN], Stack[MAXN], head[MAXN];
bool Instack[MAXN];
int Index, top, tol, ans;
struct Edge{
    int to, next, w;
}E[MAXM];
void addEdge(int u, int v, int w)
{
    E[tol].to = v;
    E[tol].next = head[u];
    E[tol].w = w;
    head[u] = tol++;
}
void init()
{
    memset(head, -1, sizeof(head));
    tol = 0;
}
void Tarjan(int u, int pre)
{
    int v, w;
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    int pre_cnt = 0;
    for(int i = head[u];i != -1;i = E[i].next){
        v = E[i].to;
        w = E[i].w;
        if(v == pre && pre_cnt == 0) {pre_cnt++; continue;} 
        if(!DFN[v]){
            Tarjan(v, u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            if(Low[v] > DFN[u]){
                ans = min(ans, w);
            }
        }else if(Low[u] > DFN[v]) Low[u] = DFN[v];
    }
    Instack[u] = false;
    --top;
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    ans = INF;
    Index = top = 0;
    int k = 0;
    for(int i = 1;i <= N;++i)
        if(!DFN[i]){
            Tarjan(i, i);
            k++;
        }   
    if(k > 1) {printf("0\n"); return ;}
    else if(ans == INF) ans = -1;
    else if(ans == 0) ans = 1;
    printf("%d\n", ans);
}
int main()
{
    int N, M;
    int u, v, w;
    while(~scanf("%d %d", &N, &M) && N){
        init();
        while(M--){
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        solve(N);
    }
    return 0;
}