/*
Author:buerguoo
Time:187ms
memory:2932kB

Data:2021-03-04 19:34:11
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
const int MAXN = 1100;
bool g[MAXN][MAXN], used[MAXN];
int linker[MAXN];
char like[MAXN][5], unlike[MAXN][5];
int N, M, P;
bool dfs(int u){
    for(int i = 0;i < P;++i){
        if(g[u][i] && !used[i]){
            used[i] = true;
            if(linker[i] == -1 || dfs(linker[i])){
                linker[i] = u;
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
    for(int u = 0;u < P;++u){
        memset(used, false, sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
int main()
{
    while(~scanf("%d %d %d", &N, &M, &P)){
        memset(g, false, sizeof(g));
        for(int i = 0;i < P;++i)
            scanf("%s%s", like[i], unlike[i]);
        for(int i = 0;i < P;++i)
            for(int j = i+1;j < P;++j)
                if(strcmp(like[i], unlike[j])==0 || strcmp(like[j], unlike[i])==0)
                    g[i][j] = g[j][i] = true;
        printf("%d\n", P-hungry()/2);
    }
    return 0;
}

