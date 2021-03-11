/*
Author:buerguoo
Time:204ms
memory:1008KB

Data:2021-03-06 23:53:27
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
const int MAXN = 350;
const int MAXM = 350;
const int INF = 0x3f3f3f3f;
int linker[MAXM][MAXN], vlink[MAXM], m[MAXN][MAXN];
bool g[MAXN][MAXM], used[MAXM];
int K, C, M, lim;
bool dfs(int u){
    for(int v = 0;v < K;++v){
        if(g[u][v] && !used[v]){
            used[v] = true;
            if(vlink[v] < M){
                linker[v][vlink[v]++] = u;
                return true;
            }
            for(int i = 0;i < vlink[v];++i){
                if(dfs(linker[v][i])){
                    linker[v][i] = u;
                    return true;
                }
            }
        }
    }
    return false;
}
bool MaxMatch()
{
    memset(g, false, sizeof(g));
    for(int i = 0;i < K;++i)
        for(int j = K;j < K+C;++j)
            if(m[i][j] <= lim)
                g[i][j] = g[j][i] = true;
    memset(vlink, 0, sizeof(vlink));
    memset(linker, 0, sizeof(linker));

    for(int u = K;u < K+C;++u){
        memset(used, false, sizeof(used));
        if(!dfs(u)) return false;
    }
    return true;
}
void floyd()
{
    for(int k = 0;k < K+C;++k)
        for(int i = 0;i < K+C;++i)
            for(int j = 0;j < K+C;++j)
                if(m[i][j] > m[i][k]+m[k][j])
                    m[i][j] = m[i][k]+m[k][j];
}
int main()
{
    scanf("%d %d %d", &K, &C, &M);
        for(int i = 0;i < K+C;++i)
            for(int j = 0;j < K+C;++j)
                scanf("%d", &m[i][j]);
        for(int i = 0;i < K+C;++i)
            for(int j = 0;j < K+C;++j)
                    if(i != j && !m[i][j]) m[i][j] = INF;
        floyd();
        int left = 0, right = INF;
        while(left < right){
            lim = (left+right)/2;
            if(MaxMatch()) right = lim;
            else left = lim+1;
        }
        printf("%d\n", left);
    return 0;
}