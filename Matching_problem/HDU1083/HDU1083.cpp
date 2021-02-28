/*
Author:buerguoo
Time:280ms
memory:1772KB

Data:2021-02-28 20:06:58
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
const int MAXM = 310;
bool g[MAXN][MAXM];
bool used[MAXM];
int linker[MAXM];
int vN, uN;
bool dfs(int u){
    for(int v = 1;v <= vN;++v){
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
    for(int u = 1;u <= uN;++u){
        memset(used, false, sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
int main()
{
    int m, n, v;
    scanf("%d", &m);
    while(m--){
        memset(g, false, sizeof(g));
        scanf("%d %d", &uN, &vN);
        for(int u = 1;u <= uN;++u){
            scanf("%d", &n);
            while (n--)
            {
                scanf("%d", &v);
                g[u][v] = true;
            }
        }
        int ans = hungry();
        if(ans == uN) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}