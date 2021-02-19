/*
Author:buerguoo
Time:795ms
memory:4356KB

Data:2021-02-19 20:29:17
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
const int MAXN = 2000;
const int MAXM = 1000000+3000;
int DFN[MAXN], Low[MAXN], Stack[MAXN], head[MAXN], match[MAXN], flag[MAXN], Belong[MAXN], ans[MAXN];
bool Instack[MAXN], vis[MAXN];
int Index, top, scc, tol, maxn, N, M;
struct Edge{
    int to, next;
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v, E[tol].next = head[u], head[u] = tol++;
}
void init()
{
    memset(head, -1, sizeof(head));
    tol = 0;
}
bool dfs(int u)
{
    int v;
    for(int i = head[u];i != -1;i = E[i].next) 
    {
        v = E[i].to;
        if(!vis[v])
        {
            vis[v] = true;
            if(match[v]==0 || dfs(match[v])){
                match[v] = u;
                flag[u] = v;
                return true;
            }
        }
    }
    return false;
}
void xiong()
{
    memset(match, 0, sizeof(match));
    memset(flag, 0, sizeof(flag));
    for(int i = 1;i <= maxn;i++){
        memset(vis, false, sizeof(vis));
        dfs(i);
    }
}
void Tarjan(int u)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = E[i].next){
        v = E[i].to;
        if(!DFN[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }else if(Instack[v] && Low[u] > DFN[v]) Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u]){
        scc++;
        do{
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
        }while(v != u);
    }
}
void solve()
{
    int v;
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    Index = scc = top = 0;
    for(int i = 1;i <= maxn;++i)
        if(!DFN[i])
            Tarjan(i);
    for(int u = 1;u <= N;++u){
            int count = 0;
            for(int i = head[u];i != -1;i = E[i].next)
            {
                v = E[i].to;
                if(Belong[u] == Belong[v]){
                    if(v - maxn > M)
                        continue;
                    ans[count++] = v-maxn;
                }
            }
            sort(ans, ans+count);
            printf("%d", count);
            for(int i = 0;i < count;++i)
                printf(" %d", ans[i]);
            printf("\n");
        }
}
int main()
{
    int T, Case = 0;
    int n, v;
    scanf("%d", &T);
    while(T--){
        init();
        scanf("%d %d", &N, &M);
        maxn = max(N, M);
        for(int i = 1;i <= N;++i){
            scanf("%d", &n);
            while(n--){
                scanf("%d", &v);
                addEdge(i, v+maxn);
            }
        }

        xiong();

        int all = 2*maxn;
        for(int i = 1;i <= maxn;++i){
            if(!flag[i]){
                all++;
                for(int j = 1;j <= maxn;++j)
                    addEdge(j, all);
                flag[i] = all;
                match[all] = i;
            }
        }
        for(int i = maxn+1;i <= maxn*2;++i){
            if(!match[i]){
                all++;
                for(int j = maxn+1;j <= 2*maxn;++j)
                    addEdge(all, j);
                flag[all] = i;
                match[i] = all;
            }
        }
        for(int i = 1;i <= all;++i)
            if(flag[i])
                addEdge(flag[i], i);
        
        printf("Case #%d:\n", ++Case);
        solve();
    }
    return 0;
}