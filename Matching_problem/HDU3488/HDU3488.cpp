/*
Author:buerguoo
Time:124ms
memory:1900kB

Data:2021-03-11 11:59:58
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
const int MAXM = 30100;
const int INF = 0x3f3f3f3f;
int linker[MAXN], lx[MAXN], ly[MAXN], slack[MAXN], g[MAXN][MAXN];
bool visx[MAXN], visy[MAXN];
int  N;
bool dfs(int u)
{
    visx[u] = true;
    for(int v = 0;v < N;++v){
        if(visy[v] || g[u][v] == -INF) continue;
        int tmp = lx[u] + ly[v] - g[u][v];
        if(tmp == 0){
            visy[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                return true;
            }
        } 
        else if(tmp < slack[v])
            slack[v] = tmp;
    }

    return false;
}
int KM()
{
    memset(linker, -1, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    for(int i = 0;i < N;++i){
        lx[i] = -INF;
        for(int j = 0;j < N;j++){
            if(lx[i] < g[i][j])
                lx[i] = g[i][j];
        }
    }
    for(int i = 0;i < N;++i){
        for(int j = 0;j < N;++j)
            slack[j] = INF;
        while(true){
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(dfs(i)) break;
            int d = INF;
            for(int j = 0;j < N;++j)
                if(!visy[j] && d > slack[j])
                    d = slack[j];
            for(int j = 0;j < N;++j)
                if(visx[j])
                    lx[j] -= d;
            for(int j = 0;j < N;++j){
                if(visy[j]) ly[j] += d;
                else slack[j] -= d;
            }
        }
    }
    int res = 0;
    for(int i = 0;i < N;++i)
        if(linker[i] != -1)
            res += g[linker[i]][i];
    
    return res;
}
int main()
{
    int K, M, u = 0,  v = 0, w = 0;
    scanf("%d", &K);
    while(K--){
        scanf("%d %d", &N, &M);
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)
                g[i][j] = -INF;
        while(M--){
            scanf("%d %d %d", &u, &v, &w);
            g[u-1][v-1] = max(-w, g[u-1][v-1]);
        }
        printf("%d\n", -KM());
    }
    return 0;
}