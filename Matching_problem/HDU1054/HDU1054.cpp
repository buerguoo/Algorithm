/*
Author:buerguoo
Time:234ms
memory:1796KB

Data:2021-03-04 15:29:25
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
const int MAXN = 1510;
const int MAXM = 2250000;
int linker[MAXN], head[MAXN];
bool used[MAXN];
int tol, N;
struct Edge{
    int to, next;
}E[MAXM];
void init(){
    memset(head, -1, sizeof(head));
    tol = 0;
}
void addEdge(int u, int v){
    E[tol].to = v;
    E[tol].next = head[u];
    head[u] = tol++;
}
bool dfs(int u){
    int v;
    for(int i = head[u];i != -1;i = E[i].next){
        v = E[i].to;
        if(!used[v]){
            used[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungry()
{
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 0;u < N;++u){
        memset(used, false, sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
int main()
{
    int u, v, n;
    while(~scanf("%d", &N)){
        init();
        for(int i = 0;i < N;++i){
            scanf("%d:(%d)", &u, &n);
            while(n--){
                scanf("%d", &v);
                addEdge(u, v);
                addEdge(v, u);
            }
        }
        printf("%d\n", hungry()/2);
    }
    return 0;
}