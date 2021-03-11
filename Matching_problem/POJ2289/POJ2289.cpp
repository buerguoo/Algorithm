/*
Author:buerguoo
Time:266MS
memory:2908kb

Data:2021-03-05 17:55:04
*/
#include <iostream>
#include <cstring>
#include<string.h>
#include<stdio.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 1010*2;
const int MAXM = 510*2;
bool g[MAXN][MAXM], used[MAXM];
int linker[MAXM][MAXN], vlink[MAXM];
char name[20];
int N, M, lim;
bool dfs(int u){
    for(int v = 0;v < M;++v){
        if(g[u][v] && !used[v]){
            used[v] = true;
            if(vlink[v] < lim){
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
bool hungary()
{
    memset(vlink, 0, sizeof(vlink));
    for(int u = 0;u < N;++u){
        memset(used, false, sizeof(used));
        if(!dfs(u)) return false;
    }
    return true;
}
int main()
{
    char c;
    int u;
    while(~scanf("%d %d", &N, &M) && (N||M)){
        getchar();
        memset(g, false, sizeof(g));
        for(int i = 0;i < N;++i){
            scanf("%s", name);
            while(true){
                scanf("%d%c", &u, &c);
                g[i][u] = true;
                if(c == '\n') break;
            }
        }
        int left = 0, right = N;
        while(left < right){
            lim = (left+right)/2;
            if(hungary()) right = lim;
            else left = lim+1;
        }
        printf("%d\n", left);
    }
    return 0;
}