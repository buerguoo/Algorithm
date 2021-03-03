/*
Author:buerguoo
Time:TLE
memory:
匈牙利超时了
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
const int MAXN = 3030;
bool g[MAXN][MAXN], used[MAXN];
int linker[MAXN], si[MAXN];
int vN, uN;
struct Point{
    int x, y;
}guests[MAXN], umbrellas[MAXN];
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
double dis(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main()
{
    int kase = 0, Case, t;
    scanf("%d", &Case);
    while(kase++ < Case){
        memset(g, false, sizeof(g));
        scanf("%d", &t);
        scanf("%d", &uN);
        for(int i = 1;i <= uN;++i)
            scanf("%d %d %d", &guests[i].x, &guests[i].y, &si[i]);
        scanf("%d", &vN);
        for(int i = 1;i <= vN;++i)
            scanf("%d %d", &umbrellas[i].x, &umbrellas[i].y);
        for(int i = 1;i <= uN;++i)
            for(int j = 1;j <= vN;++j)
                if(dis(guests[i], umbrellas[j]) <= si[i]*t)
                    g[i][j] = true;
        printf("Scenario #%d:\n%d\n", kase, hungry());
    }
    return 0;
}