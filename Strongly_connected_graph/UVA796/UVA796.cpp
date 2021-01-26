/*
Author:buerguoo
Time:
memory:

Data:2021-01-26 18:42:39
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
int DFN[MAXN], Low[MAXN], Stack[MAXN], head[MAXN];
bool InStack[MAXN], cut[MAXN];
int add_block[MAXN];
int top, Index, bridge, tol;
struct Edge{
    int to, next;
    bool cut;//ÅÐ¶ÏÊÇ·ñÊÇÇÅ
}E[MAXM];
void addEdge(int u, int v){
    E[tol].to = v, E[tol].cut = false;
    E[tol].next = head[u], head[u] = tol++;
}
void Tarjan(int u, int pre){
    DFN[u] = Low[u] = ++Index;
    InStack[u] = true;
    Stack[top++] = u;
    int son = 0, v;
    for(int i = head[u];i != -1;i = E[i].next){ 
        v = E[i].to;
        if(v == pre) continue;
        if(!DFN[v]){
            son++;
            Tarjan(v, u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            //ÇÅ
            if(DFN[u] < Low[v]){
                bridge++;
                E[i].cut = true;
                E[i^1].cut = true;
            }
            //¸îµã
            if(u != pre && DFN[u] <= Low[v]){
                cut[u] = true;
                add_block[u]++;
            }
        }
        else if(Low[u] > DFN[v]) Low[u] = DFN[v];
    }
    if(u == pre && son > 1) cut[u] = true;
    if(u == pre) add_block[u] = son-1;

    InStack[u] = false;
    --top;
}
void init(){
    memset(head, -1, sizeof(head));
    tol = 0;
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(InStack, false, sizeof(InStack));
    memset(cut, false, sizeof(cut));
    memset(add_block, 0, sizeof(add_block));
    top = Index = 0;
    bridge = 0;
    for(int i = 1;i <= N;++i)
        if(!DFN[i])
            Tarjan(i, i);
    printf("%d critical links\n",bridge);
    vector<pair<int, int>> ans;
    for(int u = 1;u <= N;++u)
        for(int i = head[u];i != -1;i = E[i].next)
            if(E[i].cut && E[i].to > u)
                ans.push_back(make_pair(u, E[i].to));
    sort(ans.begin(), ans.end());
    for(int i = 0;i < ans.size();++i)
        printf("%d - %d\n",ans[i].first-1,ans[i].second-1);
    printf("\n");
}
int main()
{
    int N;
    int u, k, v;
    while(~scanf("%d", &N)){
        init();
        for(int i = 0;i < N;++i){
            scanf("%d (%d)", &u, &k);
            u++;
            while(k--){
                scanf("%d", &v);
                v++;
                if(v <= u) continue;
                addEdge(u, v);
                addEdge(v, u);
            }
        }
        solve(N);
    }
    return 0;
}