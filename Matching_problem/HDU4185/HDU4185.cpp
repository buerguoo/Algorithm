/*
Author:buerguoo
Time:3568kB
memory:15ms

Data:2021-03-03 21:41:58
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
const int MAXN = 610;
char m[MAXN][MAXN];
int M[MAXN][MAXN];
bool g[MAXN][MAXN], used[MAXN];
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1} };
int linker[MAXN];
int N;
bool dfs(int u){
    for(int v = 0;v < N;++v){
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
    int kase = 0, Case, tol;
    scanf("%d", &Case);
    while(kase++ < Case){
        scanf("%d", &N);
        memset(M, -1, sizeof(M));
        memset(g, false, sizeof(g));
        for(int i = 0;i < N;++i)
            scanf("%s", m[i]);
        tol = 0;
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)
                if(m[i][j] == '#')  M[i][j] = tol++;
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)
                if(m[i][j] == '#')
                for(int k=0; k<4; k++)/// 上下左右建立关系；
                {
                    int x = i+dir[k][0];
                    int y = j+dir[k][1];
                    if(x>=0 && y>=0 && x<N && y<N && m[x][y]=='#')
                    {
                        int p=M[x][y];
                        int q=M[i][j];
                        g[p][q] = g[q][p] = true;///建图；
                    }
                }
        N = tol;
        printf("Case %d: %d\n", kase, hungry()/2);
    }
    return 0;
}
