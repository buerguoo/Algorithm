/*
Author:buerguoo
Time:15ms
memory:1736KB

Data:2021-02-27 17:42:34
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
const int MAXN = 20;
bool g[MAXN][MAXN], used[MAXN];
int linker[MAXN];
int xid[7][7], yid[7][7];
char a[7][7];
int uN, vN;
bool dfs(int u){
    for(int v = 1;v <= vN;v++){
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
    for(int u = 1;u <= uN;++u){
        memset(used, false, sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
int main()
{
    int N;
    while(~scanf("%d", &N) && N){
        for(int i = 1;i <= N;++i)
            scanf("%s", a[i]+1);
        vN = uN = 0;
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j){
                if(a[i][j] == '.'){
                    if(j == 1 || a[i][j-1]=='X') uN++;
                    xid[i][j] = uN;
                }
                if(a[j][i] == '.'){
                    if(j == 1 || a[j-1][i]=='X') vN++;
                    yid[j][i] = vN;
                }
            }
        memset(g, false, sizeof(false));
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                if(a[i][j] != 'X')
                    g[xid[i][j]][yid[i][j]] = true;
        printf("%d\n", hungry());
    }
    return 0;
}