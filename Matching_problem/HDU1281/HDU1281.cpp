/*
Author:buerguoo
Time:31ms
memory:1752KB

Data:2021-02-28 20:57:58
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
const int MAXN = 110;
bool g[MAXN][MAXN], used[MAXN];
int linker[MAXN], x[MAXN*MAXN], y[MAXN*MAXN];
int vN, uN;
bool dfs(int u)
{
    for(int v = 1;v <= vN;++v){
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
    for(int u = 1;u <= uN;++u){
        memset(used, false, sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
int main()
{
    int Case = 0;
    int k;
    while(~scanf("%d %d %d", &uN, &vN, &k)){
        memset(g, false, sizeof(g));
        for(int i = 0;i < k;++i){
            scanf("%d %d", &x[i], &y[i]);
            g[x[i]][y[i]] = true;
        }
        int ans = hungry();
        int imo = 0, temp;
        for(int i = 0;i < k;++i){
            g[x[i]][y[i]] = false;
            temp = hungry();
            if(temp < ans) imo++;
            g[x[i]][y[i]] = true;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n", ++Case, imo, ans);
    }

    return 0;
}
