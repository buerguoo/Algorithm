/*
Author:buerguoo
Time:
memory:

Data:
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
int g[MAXN][MAXN];
bool used[MAXN];
int linker[MAXN], N, ansx[MAXN*MAXN], ansy[MAXN*MAXN], x[MAXN];
//最大匹配
bool dfs(int u){
    for(int v = 1;v <= N;++v){
        if(g[u][v] && !used[v]){
            used[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                x[u] = v;
                return true;
            }
        }
    }
    return false;
}
void hungry(){
    int ans = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 1;u <= N;++u){
        memset(used, false, sizeof(used));
        if(dfs(u)) ans++;
    }
    if(ans < N){
        printf("-1\n");
        return ;
    }
    int res = 0;
    //交换 
    for(int i = 1;i <= N;++i){
        if(x[i] == i) continue;
        else res++;
        for(int j = i+1;j <= N;++j){
            if(x[j] == i){
                ansx[res] = i;
                ansy[res++] = x[i];
                x[j] = x[i];
                break;
            }
        }
    }
    printf("%d\n",res);
    for(int i = 0;i < res;++i)
        printf("C %d %d\n", ansx[i], ansy[i]);
}
int main()
{
    while(~scanf("%d", &N)){
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                scanf("%d", &g[i][j]);
        hungry();
    }
    return 0;
}

