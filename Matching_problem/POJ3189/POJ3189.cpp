/*
Author:buerguoo
Time:47ms
memory:4148kB

Data:2021-03-09 17:12:00
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
const int MAXM = 30;
bool used[MAXN];
int num[MAXN], linker[MAXN][MAXN], vlink[MAXN], g[MAXN][MAXN];
int uN, vN, lim;
bool dfs(int u, int l, int r){
    int v;
    for(int i = l;i <= r;++i){
        v = g[u][i];
        if(!used[v])
        {
            used[v] = true;
            if(vlink[v] < num[v]){
                linker[v][vlink[v]++] = u;
                return true;
            }
            for(int i = 0;i < vlink[v];++i){
                if(dfs(linker[v][i], l, r)){
                    linker[v][i] = u;
                    return true;
                }
            }
        }
    }
    return false;
}
bool MaxMatch(int l, int r)
{
    memset(vlink, 0, sizeof(vlink));
    for(int i = 1;i <= uN;++i){
        memset(used, false, sizeof(used));
        if(!dfs(i, l, r)) return false;
    }
    return true;
}
bool check()
{
    for(int i = 1;i <= vN-lim+1;++i)
        if(MaxMatch(i, i+lim-1)) return true;
    
    return false;
}
int main()
{
    scanf("%d %d", &uN, &vN);
    for(int i = 1;i <= uN;i++)
        for(int j = 1;j <= vN;++j)
            scanf("%d", &g[i][j]);
    for(int i = 1;i <= vN;++i)
        scanf("%d", &num[i]);
    int left = 0, right = vN;
    while(left < right){
        lim = (left+right)/2;
        if(check()) right = lim;
        else left = lim + 1; 
    }
    printf("%d\n", left);
    return 0;
}