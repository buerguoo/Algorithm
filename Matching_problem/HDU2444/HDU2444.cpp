/*
Author:buerguoo
Time:46ms
memory:1784kB

Data:2021-02-28 20:02:38
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
const int MAXN = 210;
bool g[MAXN][MAXN], used[MAXN];
int linker[MAXN], N;
int color[MAXN];
//判断是否是二分图
bool tocol(int u, int c){
    color[u] = c;
    for(int v = 1;v <= N;++v)   if(g[u][v])
    {
        if(color[v] == c) return false;
        if(!color[v] && !tocol(v, -c)) return false;
    }
    return true;
}
bool yes_no(){
    memset(color, 0, sizeof(color));
    for(int u = 1;u <= N;++u) if(!color[u]){
        if(!tocol(u, 1)) return false;
    }
    return true;
}
bool dfs(int u){
    for(int v = 1;v <= N;++v){
        if(g[u][v] && !used[v]){
            used[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungry(){
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 1;u <= N;++u){
        memset(used, false, sizeof(used));
        if(dfs(u))  res++;
    }
    return res;
}
int main()
{
    int m;
    int u, v;
    while(~scanf("%d %d",&N, &m)){
        memset(g, false, sizeof(g));
        while(m--){
            scanf("%d %d", &u, &v);
            g[u][v] = true;
        }
        if(!yes_no()) printf("No\n");
        else printf("%d\n", hungry());
    }

    return 0;
}
