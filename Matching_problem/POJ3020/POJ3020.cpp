/*
Author:buerguoo
Time:264KB
memory:16ms

Data:2021-03-04 12:54:48
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
const int MAXN = 410;
char m[45][15];
int M[45][15];
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
int hungry(){
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
    int kase = 0, Case;
    int h, w;
    scanf("%d", &Case);
    while(kase++ < Case){
        memset(g, false, sizeof(g));
        memset(M, -1, sizeof(M));
        N = 0;
        scanf("%d %d", &h, &w);
        for(int i = 0;i < h;++i)
            scanf("%s", m[i]);
        for(int i = 0;i < h;++i)
            for(int j = 0;j < w;++j)
                if(m[i][j] == '*') M[i][j] = N++;  
        for(int i = 0;i < h;++i)
            for(int j = 0;j < w;++j)
                if(m[i][j] == '*')
                for(int k=0; k<4; k++)/// 上下左右建立关系；
                {
                    int x = i+dir[k][0];
                    int y = j+dir[k][1];
                    if(x>=0 && y>=0 && x<h && y<w && m[x][y]=='*')
                    {
                        int p=M[x][y];
                        int q=M[i][j];
                        g[p][q] = g[q][p] = true;///建图；
                    }
                }
        int ans = hungry();
        printf("%d\n", N-ans+ans/2);
    }
    return 0;
}
