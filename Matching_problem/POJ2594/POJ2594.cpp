/*
Author:buerguoo
Time:344ms
memory:348KB

Data:2021-03-04 16:59:26
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
const int MAXN = 510;
int linker[MAXN];
bool used[MAXN], g[MAXN][MAXN];
int N;
void folyd()
{
    for(int i = 0;i < N;++i)
        for(int j = 0;j < N;++j)
            if(g[i][j])
                for(int k = 0;k < N;++k)
                    if(g[j][k])
                        g[i][k] = true;
}
bool dfs(int u){
    for(int v = 0;v < N;++v){
        if(!used[v] && g[u][v]){
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
    while(~scanf("%d %d", &N, &m) && (N || m)){
        memset(g, false, sizeof(g));
        while(m--){
            scanf("%d %d", &u, &v);
            g[u-1][v-1] = true;
        }
        folyd();
        printf("%d\n", N-hungry());
    }
    return 0;
}