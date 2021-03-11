/*
Author:buerguoo
Time:499ms
memory:2112KB

Data:2021-03-10 13:27:42
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
const int MAXN = 310;
const int MAXM = 310;
const int INF = 0x3f3f3f3f;
int g[MAXN][MAXM], lx[MAXN], ly[MAXM];
bool visx[MAXN], visy[MAXM];
int slack[MAXM], linker[MAXM];
int xN, yN;
bool dfs(int u)
{
    visx[u] = true;
    for(int y = 0;y < yN;y++){
        if(visy[y]) continue;
        int tmp = lx[u] + ly[y] - g[u][y];
        if(tmp == 0){
            visy[y] = true;
            if(linker[y] == -1 || dfs(linker[y])){
                linker[y] = u;
                return true;
            }
        } 
        else if(tmp < slack[y])
            slack[y] = tmp;
    }
    return false;
}
int KM()
{
    memset(linker, -1, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    for(int i = 0;i < xN;++i){
        lx[i] = -INF;
        for(int j = 0;j < yN;++j)
            if(lx[i] < g[i][j])
                lx[i] = g[i][j];
    }
    for(int x = 0;x < xN;++x)
    {
        for(int j = 0;j < yN;++j)
            slack[j] = INF;
        while(true){
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(dfs(x)) break;
            int d = INF;
            for(int j = 0;j < yN;++j)
                if(!visy[j] && d > slack[j])
                    d = slack[j];
            for(int i = 0;i < xN;++i)
                if(visx[i])
                    lx[i] -= d;
            for(int j = 0;j < yN;++j){
                if(visy[j]) ly[j] += d;
                else slack[j] -= d;
            }
       }
    }
    int res = 0;
    for(int i = 0;i < yN;++i)
        if(linker[i] != -1)
            res += g[linker[i]][i];
    return res;
}
int main()
{
    int N;
    while(~scanf("%d", &N)){
        xN = yN = N;
        for(int i = 0;i < xN;++i)
            for(int j = 0;j < yN;++j)
                scanf("%d", &g[i][j]);
        printf("%d\n", KM());
    }
    return 0;
}