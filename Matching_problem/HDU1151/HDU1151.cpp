/*
Author:buerguoo
Time:15ms
memory:1744KB

Data:2021-03-04 16:11:21
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
const int MAXN = 125;
const int MAXM = 500;
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
    int u, v, m;
    int C;
    scanf("%d", &C);
    while(C--){
        scanf("%d", &N);
        init();
        scanf("%d", &m);
        while(m--){
            scanf("%d %d", &u, &v);
            addEdge(u-1, v-1);
        }
        printf("%d\n", N-hungry());
    }
    return 0;
}